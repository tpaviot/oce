// Created on: 1994-10-13
// Created by: Marc LEGAY
// Copyright (c) 1994-1999 Matra Datavision
// Copyright (c) 1999-2012 OPEN CASCADE SAS
//
// The content of this file is subject to the Open CASCADE Technology Public
// License Version 6.5 (the "License"). You may not use the content of this file
// except in compliance with the License. Please obtain a copy of the License
// at http://www.opencascade.org and read it completely before using this file.
//
// The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
// main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.
//
// The Original Code and all software distributed under the License is
// distributed on an "AS IS" basis, without warranty of any kind, and the
// Initial Developer hereby disclaims all such warranties, including without
// limitation, any warranties of merchantability, fitness for a particular
// purpose or non-infringement. Please see the License for the specific terms
// and conditions governing the rights and limitations under the License.



#include <RWStl.ixx>
#include <OSD_Protection.hxx>
#include <OSD_File.hxx>
#include <Message_ProgressSentry.hxx>
#include <TCollection_AsciiString.hxx>
#include <Standard_NoMoreObject.hxx>
#include <Standard_TypeMismatch.hxx>
#include <Precision.hxx>
#include <StlMesh_MeshExplorer.hxx>
#include <OSD.hxx>
#include <OSD_Host.hxx>
#include <gp_XYZ.hxx>
#include <gp.hxx>
#include <stdio.h>
#include <gp_Vec.hxx>


// constants
static const int HEADER_SIZE           =  84;
static const int SIZEOF_STL_FACET      =  50;
static const int STL_MIN_FILE_SIZE     = 284;
static const int ASCII_LINES_PER_FACET =   7;
static const int IND_THRESHOLD         = 1000; // increment the indicator every 1k triangles

//=======================================================================
//function : WriteInteger
//purpose  : writing a Little Endian 32 bits integer
//=======================================================================

inline static void WriteInteger(OSD_File& ofile,const Standard_Integer value)
{
  union {
    Standard_Integer i;// don't be afraid, this is just an unsigned int
    char c[4];
  } bidargum;

  bidargum.i = value;

  Standard_Integer entier;

  entier  =  bidargum.c[0] & 0xFF;
  entier |= (bidargum.c[1] & 0xFF) << 0x08;
  entier |= (bidargum.c[2] & 0xFF) << 0x10;
  entier |= (bidargum.c[3] & 0xFF) << 0x18;

  ofile.Write((char *)&entier,sizeof(bidargum.c));
}

//=======================================================================
//function : WriteDouble2Float
//purpose  : writing a Little Endian 32 bits float
//=======================================================================

inline static void WriteDouble2Float(OSD_File& ofile,Standard_Real value)
{
  union {
    Standard_ShortReal f;
    char c[4];
  } bidargum;

  bidargum.f = (Standard_ShortReal)value;

  Standard_Integer entier;

  entier  =  bidargum.c[0] & 0xFF;
  entier |= (bidargum.c[1] & 0xFF) << 0x08;
  entier |= (bidargum.c[2] & 0xFF) << 0x10;
  entier |= (bidargum.c[3] & 0xFF) << 0x18;

  ofile.Write((char *)&entier,sizeof(bidargum.c));
}


//=======================================================================
//function : readFloat2Double
//purpose  : reading a Little Endian 32 bits float
//=======================================================================

inline static Standard_Real ReadFloat2Double(OSD_File &aFile)
{
  union {
    Standard_Boolean i; // don't be afraid, this is just an unsigned int
    Standard_ShortReal f;
  }bidargum;

  char c[4];
  Standard_Address adr;
  adr = (Standard_Address)c;
  Standard_Integer lread;
  aFile.Read(adr,4,lread);
  bidargum.i  =  c[0] & 0xFF;
  bidargum.i |=  (c[1] & 0xFF) << 0x08;
  bidargum.i |=  (c[2] & 0xFF) << 0x10;
  bidargum.i |=  (c[3] & 0xFF) << 0x18;

  return (Standard_Real)(bidargum.f);
}



//=======================================================================
//function : WriteBinary
//purpose  : write a binary STL file in Little Endian format
//=======================================================================

Standard_Boolean RWStl::WriteBinary (const Handle(StlMesh_Mesh)& theMesh,
                                     const OSD_Path& thePath,
                                     const Handle(Message_ProgressIndicator)& theProgInd)
{
  OSD_File aFile (thePath);
  aFile.Build (OSD_WriteOnly, OSD_Protection());

  Standard_Real x1, y1, z1;
  Standard_Real x2, y2, z2;
  Standard_Real x3, y3, z3;

  // writing 80 bytes of the trash?
  char sval[80];
  aFile.Write ((Standard_Address)sval,80);
  WriteInteger (aFile, theMesh->NbTriangles());

  int dum=0;
  StlMesh_MeshExplorer aMexp (theMesh);

  // create progress sentry for domains
  Standard_Integer aNbDomains = theMesh->NbDomains();
  Message_ProgressSentry aDPS (theProgInd, "Mesh domains", 0, aNbDomains, 1);
  for (Standard_Integer nbd = 1; nbd <= aNbDomains && aDPS.More(); nbd++, aDPS.Next())
  {
    // create progress sentry for triangles in domain
    Message_ProgressSentry aTPS (theProgInd, "Triangles", 0,
        theMesh->NbTriangles (nbd), IND_THRESHOLD);
    Standard_Integer aTriangleInd = 0;
    for (aMexp.InitTriangle (nbd); aMexp.MoreTriangle(); aMexp.NextTriangle())
    {
      aMexp.TriangleVertices (x1,y1,z1,x2,y2,z2,x3,y3,z3);
      //pgo	  aMexp.TriangleOrientation (x,y,z);
      gp_XYZ Vect12 ((x2-x1), (y2-y1), (z2-z1));
      gp_XYZ Vect13 ((x3-x1), (y3-y1), (z3-z1));
      gp_XYZ Vnorm = Vect12 ^ Vect13;
      Standard_Real Vmodul = Vnorm.Modulus ();
      if (Vmodul > gp::Resolution())
      {
        Vnorm.Divide(Vmodul);
      }
      else
      {
        // si Vnorm est quasi-nul, on le charge a 0 explicitement
        Vnorm.SetCoord (0., 0., 0.);
      }

      WriteDouble2Float (aFile, Vnorm.X());
      WriteDouble2Float (aFile, Vnorm.Y());
      WriteDouble2Float (aFile, Vnorm.Z());

      WriteDouble2Float (aFile, x1);
      WriteDouble2Float (aFile, y1);
      WriteDouble2Float (aFile, z1);

      WriteDouble2Float (aFile, x2);
      WriteDouble2Float (aFile, y2);
      WriteDouble2Float (aFile, z2);

      WriteDouble2Float (aFile, x3);
      WriteDouble2Float (aFile, y3);
      WriteDouble2Float (aFile, z3);

      aFile.Write (&dum, 2);

      // update progress only per 1k triangles
      if (++aTriangleInd % IND_THRESHOLD == 0)
      {
        if (!aTPS.More())
          break;
        aTPS.Next();
      }
    }
  }
  aFile.Close();
  Standard_Boolean isInterrupted = !aDPS.More();
  return !isInterrupted;
}
//=======================================================================
//function : WriteAscii
//purpose  : write an ASCII STL file
//=======================================================================

Standard_Boolean RWStl::WriteAscii (const Handle(StlMesh_Mesh)& theMesh,
                                    const OSD_Path& thePath,
                                    const Handle(Message_ProgressIndicator)& theProgInd)
{
  OSD_File theFile (thePath);
  theFile.Build(OSD_WriteOnly,OSD_Protection());
  TCollection_AsciiString buf ("solid\n");
  theFile.Write (buf,buf.Length());buf.Clear();

  Standard_Real x1, y1, z1;
  Standard_Real x2, y2, z2;
  Standard_Real x3, y3, z3;
  char sval[512];

  // create progress sentry for domains
  Standard_Integer aNbDomains = theMesh->NbDomains();
  Message_ProgressSentry aDPS (theProgInd, "Mesh domains", 0, aNbDomains, 1);
  StlMesh_MeshExplorer aMexp (theMesh);
  for (Standard_Integer nbd = 1; nbd <= aNbDomains && aDPS.More(); nbd++, aDPS.Next())
  {
    // create progress sentry for triangles in domain
    Message_ProgressSentry aTPS (theProgInd, "Triangles", 0,
        theMesh->NbTriangles (nbd), IND_THRESHOLD);
    Standard_Integer aTriangleInd = 0;
    for (aMexp.InitTriangle (nbd); aMexp.MoreTriangle(); aMexp.NextTriangle())
    {
      aMexp.TriangleVertices (x1,y1,z1,x2,y2,z2,x3,y3,z3);

//      Standard_Real x, y, z;
//      aMexp.TriangleOrientation (x,y,z);

      gp_XYZ Vect12 ((x2-x1), (y2-y1), (z2-z1));
      gp_XYZ Vect23 ((x3-x2), (y3-y2), (z3-z2));
      gp_XYZ Vnorm = Vect12 ^ Vect23;
      Standard_Real Vmodul = Vnorm.Modulus ();
      if (Vmodul > gp::Resolution())
      {
        Vnorm.Divide (Vmodul);
      }
      else
      {
        // si Vnorm est quasi-nul, on le charge a 0 explicitement
        Vnorm.SetCoord (0., 0., 0.);
      }
      Sprintf (sval,
          " facet normal % 12e % 12e % 12e\n"
          "   outer loop\n"
          "     vertex % 12e % 12e % 12e\n"
          "     vertex % 12e % 12e % 12e\n"
          "     vertex % 12e % 12e % 12e\n"
          "   endloop\n"
          " endfacet\n",
          Vnorm.X(), Vnorm.Y(), Vnorm.Z(),
          x1, y1, z1,
          x2, y2, z2,
          x3, y3, z3);
      buf += sval;
      theFile.Write (buf, buf.Length()); buf.Clear();

      // update progress only per 1k triangles
      if (++aTriangleInd % IND_THRESHOLD == 0)
      {
        if (!aTPS.More())
            break;
        aTPS.Next();
      }
    }
  }

  buf += "endsolid\n";
  theFile.Write (buf, buf.Length()); buf.Clear();
  theFile.Close();
  Standard_Boolean isInterrupted = !aDPS.More();
  return !isInterrupted;
}
//=======================================================================
//function : ReadFile
//Design   :
//Warning  :
//=======================================================================

Handle_StlMesh_Mesh RWStl::ReadFile (const OSD_Path& thePath,
                                     const Handle(Message_ProgressIndicator)& theProgInd)
{
  OSD_File file (thePath);
  file.Open(OSD_ReadOnly,OSD_Protection(OSD_RWD,OSD_RWD,OSD_RWD,OSD_RWD));
  Standard_Boolean IsAscii;
  unsigned char str[128];
  Standard_Integer lread,i;
  Standard_Address ach;
  ach = (Standard_Address)str;

  // we skip the header which is in Ascii for both modes
  file.Read(ach,HEADER_SIZE,lread);

  // we read 128 characters to detect if we have a non-ascii char
  file.Read(ach,sizeof(str),lread);

  IsAscii = Standard_True;
  for (i = 0; i< lread && IsAscii; ++i) {
    if (str[i] > '~') {
      IsAscii = Standard_False;
    }
  }
#ifdef DEB
  cout << (IsAscii ? "ascii\n" : "binary\n");
#endif
  file.Close();

  return IsAscii ? RWStl::ReadAscii  (thePath, theProgInd)
                 : RWStl::ReadBinary (thePath, theProgInd);
}

//=======================================================================
//function : ReadBinary
//Design   :
//Warning  :
//=======================================================================

Handle_StlMesh_Mesh RWStl::ReadBinary (const OSD_Path& thePath,
                                       const Handle(Message_ProgressIndicator)& /*theProgInd*/)
{
  Standard_Integer NBFACET;
  Standard_Integer ifacet;
  Standard_Real fx,fy,fz,fx1,fy1,fz1,fx2,fy2,fz2,fx3,fy3,fz3;
  Standard_Integer i1,i2,i3,lread;
  char buftest[5];
  Standard_Address adr;
  adr = (Standard_Address)buftest;

  // Open the file
  OSD_File theFile (thePath);
  theFile.Open(OSD_ReadOnly,OSD_Protection(OSD_RWD,OSD_RWD,OSD_RWD,OSD_RWD));

  // the size of the file (minus the header size)
  // must be a multiple of SIZEOF_STL_FACET

  // compute file size
  Standard_Integer filesize = theFile.Size();

  if ( (filesize - HEADER_SIZE) % SIZEOF_STL_FACET !=0
	|| (filesize < STL_MIN_FILE_SIZE)) {
    Standard_NoMoreObject::Raise("RWStl::ReadBinary (wrong file size)");
  }

  // don't trust the number of triangles which is coded in the file
  // sometimes it is wrong, and with this technique we don't need to swap endians for integer
  NBFACET = ((filesize - HEADER_SIZE) / SIZEOF_STL_FACET);

  // skip the header
  theFile.Seek(HEADER_SIZE,OSD_FromBeginning);

  // create the StlMesh_Mesh object
  Handle(StlMesh_Mesh) ReadMesh = new StlMesh_Mesh ();
  ReadMesh->AddDomain ();

  for (ifacet=1; ifacet<=NBFACET; ++ifacet) {
    // read normal coordinates
    fx = ReadFloat2Double(theFile);
    fy = ReadFloat2Double(theFile);
    fz = ReadFloat2Double(theFile);

    // read vertex 1
    fx1 = ReadFloat2Double(theFile);
    fy1 = ReadFloat2Double(theFile);
    fz1 = ReadFloat2Double(theFile);

    // read vertex 2
    fx2 = ReadFloat2Double(theFile);
    fy2 = ReadFloat2Double(theFile);
    fz2 = ReadFloat2Double(theFile);

    // read vertex 3
    fx3 = ReadFloat2Double(theFile);
    fy3 = ReadFloat2Double(theFile);
    fz3 = ReadFloat2Double(theFile);

    i1 = ReadMesh->AddOnlyNewVertex (fx1,fy1,fz1);
    i2 = ReadMesh->AddOnlyNewVertex (fx2,fy2,fz2);
    i3 = ReadMesh->AddOnlyNewVertex (fx3,fy3,fz3);
    ReadMesh->AddTriangle (i1,i2,i3,fx,fy,fz);

    // skip extra bytes
    theFile.Read(adr,2,lread);
  }

  theFile.Close ();
  return ReadMesh;

}
//=======================================================================
//function : ReadAscii
//Design   :
//Warning  :
//=======================================================================

Handle_StlMesh_Mesh RWStl::ReadAscii (const OSD_Path& thePath,
                                      const Handle(Message_ProgressIndicator)& theProgInd)
{
  TCollection_AsciiString filename;
  long ipos;
  Standard_Integer nbLines = 0;
  Standard_Integer nbTris = 0;
  Standard_Integer iTri;
  Standard_Integer i1,i2,i3;
  Handle(StlMesh_Mesh) ReadMesh;

  thePath.SystemName (filename);

  // Open the file
  FILE* file = fopen(filename.ToCString(),"r");

  fseek(file,0L,SEEK_END);

  long filesize = ftell(file);

  fclose(file);
  file = fopen(filename.ToCString(),"r");

  // count the number of lines
  for (ipos = 0; ipos < filesize; ++ipos) {
	  if (getc(file) == '\n')
        nbLines++;
  }

  // compute number of triangles
  nbTris = (nbLines / ASCII_LINES_PER_FACET);

  // go back to the beginning of the file
//  fclose(file);
//  file = fopen(filename.ToCString(),"r");
  rewind(file);

  // skip header
  while (getc(file) != '\n') {}
#ifdef DEB
  cout << "start mesh\n";
#endif
  ReadMesh = new StlMesh_Mesh();
  ReadMesh->AddDomain();

  // main reading
  Message_ProgressSentry aPS (theProgInd, "Triangles", 0, (nbTris - 1) * 1.0 / IND_THRESHOLD, 1);
  for (iTri = 0; iTri < nbTris && aPS.More();)
  {
    char x[256]="", y[256]="", z[256]="";

    // reading the facet normal
    if (3 != fscanf(file,"%*s %*s %80s %80s %80s\n", x, y, z))
      break; // error should be properly reported
    gp_XYZ aN (Atof(x), Atof(y), Atof(z));

    // skip the keywords "outer loop"
    fscanf(file,"%*s %*s");

    // reading vertex
    if (3 != fscanf(file,"%*s %80s %80s %80s\n", x, y, z))
      break; // error should be properly reported
    gp_XYZ aV1 (Atof(x), Atof(y), Atof(z));
    if (3 != fscanf(file,"%*s %80s %80s %80s\n", x, y, z))
      break; // error should be properly reported
    gp_XYZ aV2 (Atof(x), Atof(y), Atof(z));
    if (3 != fscanf(file,"%*s %80s %80s %80s\n", x, y, z))
      break; // error should be properly reported
    gp_XYZ aV3 (Atof(x), Atof(y), Atof(z));

    // here the facet must be built and put in the mesh datastructure

    i1 = ReadMesh->AddOnlyNewVertex (aV1.X(), aV1.Y(), aV1.Z());
    i2 = ReadMesh->AddOnlyNewVertex (aV2.X(), aV2.Y(), aV2.Z());
    i3 = ReadMesh->AddOnlyNewVertex (aV3.X(), aV3.Y(), aV3.Z());
    ReadMesh->AddTriangle (i1, i2, i3, aN.X(), aN.Y(), aN.Z());

    // skip the keywords "endloop"
    fscanf(file,"%*s");

    // skip the keywords "endfacet"
    fscanf(file,"%*s");

    // update progress only per 1k triangles
    if (++iTri % IND_THRESHOLD == 0)
      aPS.Next();
  }
#ifdef DEB
  cout << "end mesh\n";
#endif
  fclose(file);
  return ReadMesh;
}
