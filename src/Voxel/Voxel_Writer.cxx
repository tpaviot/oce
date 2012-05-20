// Created on: 2008-08-28
// Created by: Vladislav ROMASHKO
// Copyright (c) 2008-2012 OPEN CASCADE SAS
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


#include <Voxel_Writer.ixx>
#include <Voxel_TypeDef.hxx>

#include <Precision.hxx>
#include <TCollection_AsciiString.hxx>

#include <stdio.h>

Voxel_Writer::Voxel_Writer():myFormat(Voxel_VFF_ASCII),myBoolVoxels(0),myColorVoxels(0),myFloatVoxels(0)
{

}

void Voxel_Writer::SetFormat(const Voxel_VoxelFileFormat format)
{
  myFormat = format;
}

void Voxel_Writer::SetVoxels(const Voxel_BoolDS& voxels)
{
  myBoolVoxels  = (Standard_Address) &voxels;
  myColorVoxels = 0;
  myFloatVoxels = 0;
}

void Voxel_Writer::SetVoxels(const Voxel_ColorDS& voxels)
{
  myBoolVoxels  = 0;
  myColorVoxels = (Standard_Address) &voxels;
  myFloatVoxels = 0;
}

void Voxel_Writer::SetVoxels(const Voxel_FloatDS& voxels)
{
  myBoolVoxels  = 0;
  myColorVoxels = 0;
  myFloatVoxels = (Standard_Address) &voxels;
}

Standard_Boolean Voxel_Writer::Write(const TCollection_ExtendedString& file) const
{
  switch (myFormat)
  {
    case Voxel_VFF_ASCII:
    {
      if (myBoolVoxels)
	return WriteBoolAsciiVoxels(file);
      else if (myColorVoxels)
	return WriteColorAsciiVoxels(file);
      else if (myFloatVoxels)
	return WriteFloatAsciiVoxels(file);
    }
    case Voxel_VFF_BINARY:
    {
      if (myBoolVoxels)
	return WriteBoolBinaryVoxels(file);
      else if (myColorVoxels)
	return WriteColorBinaryVoxels(file);
      else if (myFloatVoxels)
	return WriteFloatBinaryVoxels(file);
    }
  }

  // No voxels or no format description is found:
  return Standard_False;
}

Standard_Boolean Voxel_Writer::WriteBoolAsciiVoxels(const TCollection_ExtendedString& file) const
{
  Voxel_BoolDS* ds = (Voxel_BoolDS*) myBoolVoxels;
  if (!ds->myData)
    return Standard_False;

  // Open file for writing
  FILE* f = fopen(TCollection_AsciiString(file, '?').ToCString(), "w+");
  if (!f)
    return Standard_False;

  // Header: file format, type of voxels
  fprintf(f, VOXELS);
  fprintf(f, " ");
  fprintf(f, ASCII);
  fprintf(f, " ");
  fprintf(f, BOOL);
  fprintf(f, "\n");
  
  // Location, size, number of splits
  fprintf(f, "%g %g %g\n", ds->GetX(), ds->GetY(), ds->GetZ());
  fprintf(f, "%g %g %g\n", ds->GetXLen(), ds->GetYLen(), ds->GetZLen());
  fprintf(f, "%d %d %d\n", ds->GetNbX(), ds->GetNbY(), ds->GetNbZ());

  // Data
  // Copied from Voxel_BoolDS.cxx:
  Standard_Integer nb_bytes = RealToInt(ceil(ds->GetNbX() * ds->GetNbY() * ds->GetNbZ() / 8.0));
  Standard_Integer nb_slices = RealToInt(ceil(nb_bytes / 8.0));
  // myData[0 .. nb_slices - 1][0 .. 7]
  if (nb_slices)
  {
    Standard_Integer i1 = 0, i2 = 0;
    for (i1 = 0; i1 < nb_slices; i1++)
    {
      if (((Standard_Byte**)ds->myData)[i1])
      {
	Standard_Boolean has_value = Standard_False;
	fprintf(f, "%d ", i1); // index of slice
	for (i2 = 0; i2 < 8; i2++)
	{
	  Standard_Byte value = ((Standard_Byte*)((Standard_Byte**)ds->myData)[i1])[i2];
	  if (value)
	  {
	    has_value = Standard_True;
	    fprintf(f, "%d %d\n", i2, value);
	  }
	}
	if (!has_value)
	{
	  fprintf(f, "0 0\n");
	}
      }
    }
  }

  fclose(f);
  return Standard_True;
}

Standard_Boolean Voxel_Writer::WriteColorAsciiVoxels(const TCollection_ExtendedString& file) const
{
  Voxel_ColorDS* ds = (Voxel_ColorDS*) myColorVoxels;
  if (!ds->myData)
    return Standard_False;

  // Open file for writing
  FILE* f = fopen(TCollection_AsciiString(file, '?').ToCString(), "w+");
  if (!f)
    return Standard_False;

  // Header: file format, type of voxels
  fprintf(f, VOXELS);
  fprintf(f, " ");
  fprintf(f, ASCII);
  fprintf(f, " ");
  fprintf(f, COLOR);
  fprintf(f, "\n");
  
  // Location, size, number of splits
  fprintf(f, "%g %g %g\n", ds->GetX(), ds->GetY(), ds->GetZ());
  fprintf(f, "%g %g %g\n", ds->GetXLen(), ds->GetYLen(), ds->GetZLen());
  fprintf(f, "%d %d %d\n", ds->GetNbX(), ds->GetNbY(), ds->GetNbZ());

  // Data
  // Copied from Voxel_ColorDS.cxx:
  Standard_Integer nb_bytes = RealToInt(ceil(ds->GetNbX() * ds->GetNbY() * ds->GetNbZ() / 2.0));
  Standard_Integer nb_slices = RealToInt(ceil(nb_bytes / 32.0));
  // myData[0 .. nb_slices - 1][0 .. 31]
  if (nb_slices)
  {
    Standard_Integer i1 = 0, i2 = 0;
    for (i1 = 0; i1 < nb_slices; i1++)
    {
      if (((Standard_Byte**)ds->myData)[i1])
      {
	Standard_Boolean has_value = Standard_False;
	fprintf(f, "%d ", i1); // index of slice
	for (i2 = 0; i2 < 32; i2++)
	{
	  Standard_Byte value = ((Standard_Byte*)((Standard_Byte**)ds->myData)[i1])[i2];
	  if (value)
	  {
	    has_value = Standard_True;
	    fprintf(f, "%d %d\n", i2, value);
	  }
	}
	if (!has_value)
	{
	  fprintf(f, "0 0\n");
	}
      }
    }
  }

  fclose(f);
  return Standard_True;
}

Standard_Boolean Voxel_Writer::WriteFloatAsciiVoxels(const TCollection_ExtendedString& file) const
{
  Voxel_FloatDS* ds = (Voxel_FloatDS*) myFloatVoxels;
  if (!ds->myData)
    return Standard_False;

  // Open file for writing
  FILE* f = fopen(TCollection_AsciiString(file, '?').ToCString(), "w+");
  if (!f)
    return Standard_False;

  // Header: file format, type of voxels
  fprintf(f, VOXELS);
  fprintf(f, " ");
  fprintf(f, ASCII);
  fprintf(f, " ");
  fprintf(f, FLOAT);
  fprintf(f, "\n");
  
  // Location, size, number of splits
  fprintf(f, "%g %g %g\n", ds->GetX(), ds->GetY(), ds->GetZ());
  fprintf(f, "%g %g %g\n", ds->GetXLen(), ds->GetYLen(), ds->GetZLen());
  fprintf(f, "%d %d %d\n", ds->GetNbX(), ds->GetNbY(), ds->GetNbZ());

  // Data
  // Copied from Voxel_FloatDS.cxx:
  Standard_Integer nb_floats = ds->GetNbX() * ds->GetNbY() * ds->GetNbZ();
  Standard_Integer nb_slices = RealToInt(ceil(nb_floats / 32.0)); // 32 values in 1 slice
  // myData[0 .. nb_slices - 1][0 .. 31]
  if (nb_slices)
  {
    Standard_Integer i1 = 0, i2 = 0;
    for (i1 = 0; i1 < nb_slices; i1++)
    {
      if (((Standard_ShortReal**)ds->myData)[i1])
      {
	Standard_Boolean has_value = Standard_False;
	fprintf(f, "%d ", i1); // index of slice
	for (i2 = 0; i2 < 32; i2++)
	{
	  Standard_ShortReal value = ((Standard_ShortReal*)((Standard_ShortReal**)ds->myData)[i1])[i2];
	  if (value)
	  {
	    has_value = Standard_True;
	    fprintf(f, "%d %g\n", i2, value);
	  }
	}
	if (!has_value)
	{
	  fprintf(f, "0 0\n");
	}
      }
    }
  }

  fclose(f);
  return Standard_True;
}

Standard_Boolean Voxel_Writer::WriteBoolBinaryVoxels(const TCollection_ExtendedString& file) const
{
  Voxel_BoolDS* ds = (Voxel_BoolDS*) myBoolVoxels;
  if (!ds->myData)
    return Standard_False;

  // Open file for writing
  FILE* f = fopen(TCollection_AsciiString(file, '?').ToCString(), "wb");
  if (!f)
    return Standard_False;

  // Header: file format, type of voxels
  fprintf(f, VOXELS);
  fprintf(f, " ");
  fprintf(f, BINARY);
  fprintf(f, " ");
  fprintf(f, BOOL);
  fprintf(f, "\n");
  
  // Location, size, number of splits
  fwrite(&(ds->myX), sizeof(Standard_Real), 1, f);
  fwrite(&(ds->myY), sizeof(Standard_Real), 1, f);
  fwrite(&(ds->myZ), sizeof(Standard_Real), 1, f);
  fwrite(&(ds->myXLen), sizeof(Standard_Real), 1, f);
  fwrite(&(ds->myYLen), sizeof(Standard_Real), 1, f);
  fwrite(&(ds->myZLen), sizeof(Standard_Real), 1, f);
  fwrite(&(ds->myNbX), sizeof(Standard_Integer), 1, f);
  fwrite(&(ds->myNbY), sizeof(Standard_Integer), 1, f);
  fwrite(&(ds->myNbZ), sizeof(Standard_Integer), 1, f);

  // Data
  // Copied from Voxel_BoolDS.cxx:
  Standard_Integer nb_bytes = RealToInt(ceil(ds->GetNbX() * ds->GetNbY() * ds->GetNbZ() / 8.0));
  Standard_Integer nb_slices = RealToInt(ceil(nb_bytes / 8.0));
  // myData[0 .. nb_slices - 1][0 .. 7]
  if (nb_slices)
  {
    Standard_Integer i1 = 0, i2 = 0;
    for (i1 = 0; i1 < nb_slices; i1++)
    {
      if (((Standard_Byte**)ds->myData)[i1])
      {
	for (i2 = 0; i2 < 8; i2++)
	{
	  Standard_Byte value = ((Standard_Byte*)((Standard_Byte**)ds->myData)[i1])[i2];
	  if (value)
	  {
	    fwrite(&i1, sizeof(Standard_Integer), 1, f);
	    fwrite(&i2, sizeof(Standard_Integer), 1, f);
	    fwrite(&value, sizeof(Standard_Byte), 1, f);
	  }
	}
      }
    }
  }

  fclose(f);
  return Standard_True;
}

Standard_Boolean Voxel_Writer::WriteColorBinaryVoxels(const TCollection_ExtendedString& file) const
{
  Voxel_ColorDS* ds = (Voxel_ColorDS*) myColorVoxels;
  if (!ds->myData)
    return Standard_False;

  // Open file for writing
  FILE* f = fopen(TCollection_AsciiString(file, '?').ToCString(), "wb");
  if (!f)
    return Standard_False;

  // Header: file format, type of voxels
  fprintf(f, VOXELS);
  fprintf(f, " ");
  fprintf(f, BINARY);
  fprintf(f, " ");
  fprintf(f, COLOR);
  fprintf(f, "\n");
  
  // Location, size, number of splits
  fwrite(&(ds->myX), sizeof(Standard_Real), 1, f);
  fwrite(&(ds->myY), sizeof(Standard_Real), 1, f);
  fwrite(&(ds->myZ), sizeof(Standard_Real), 1, f);
  fwrite(&(ds->myXLen), sizeof(Standard_Real), 1, f);
  fwrite(&(ds->myYLen), sizeof(Standard_Real), 1, f);
  fwrite(&(ds->myZLen), sizeof(Standard_Real), 1, f);
  fwrite(&(ds->myNbX), sizeof(Standard_Integer), 1, f);
  fwrite(&(ds->myNbY), sizeof(Standard_Integer), 1, f);
  fwrite(&(ds->myNbZ), sizeof(Standard_Integer), 1, f);

  // Data
  // Copied from Voxel_ColorDS.cxx:
  Standard_Integer nb_bytes = RealToInt(ceil(ds->myNbX * ds->myNbY * ds->myNbZ / 2.0));
  Standard_Integer nb_slices = RealToInt(ceil(nb_bytes / 32.0));
  // myData[0 .. nb_slices - 1][0 .. 31]
  if (nb_slices)
  {
    Standard_Integer i1 = 0, i2 = 0;
    for (i1 = 0; i1 < nb_slices; i1++)
    {
      if (((Standard_Byte**)ds->myData)[i1])
      {
	for (i2 = 0; i2 < 32; i2++)
	{
	  Standard_Byte value = ((Standard_Byte*)((Standard_Byte**)ds->myData)[i1])[i2];
	  if (value)
	  {
	    fwrite(&i1, sizeof(Standard_Integer), 1, f);
	    fwrite(&i2, sizeof(Standard_Integer), 1, f);
	    fwrite(&value, sizeof(Standard_Byte), 1, f);
	  }
	}
      }
    }
  }

  fclose(f);
  return Standard_True;
}

Standard_Boolean Voxel_Writer::WriteFloatBinaryVoxels(const TCollection_ExtendedString& file) const
{
  Voxel_FloatDS* ds = (Voxel_FloatDS*) myFloatVoxels;
  if (!ds->myData)
    return Standard_False;

  // Open file for writing
  FILE* f = fopen(TCollection_AsciiString(file, '?').ToCString(), "wb");
  if (!f)
    return Standard_False;

  // Header: file format, type of voxels
  fprintf(f, VOXELS);
  fprintf(f, " ");
  fprintf(f, BINARY);
  fprintf(f, " ");
  fprintf(f, FLOAT);
  fprintf(f, "\n");
  
  // Location, size, number of splits
  fwrite(&(ds->myX), sizeof(Standard_Real), 1, f);
  fwrite(&(ds->myY), sizeof(Standard_Real), 1, f);
  fwrite(&(ds->myZ), sizeof(Standard_Real), 1, f);
  fwrite(&(ds->myXLen), sizeof(Standard_Real), 1, f);
  fwrite(&(ds->myYLen), sizeof(Standard_Real), 1, f);
  fwrite(&(ds->myZLen), sizeof(Standard_Real), 1, f);
  fwrite(&(ds->myNbX), sizeof(Standard_Integer), 1, f);
  fwrite(&(ds->myNbY), sizeof(Standard_Integer), 1, f);
  fwrite(&(ds->myNbZ), sizeof(Standard_Integer), 1, f);

  // Data
  // Copied from Voxel_FloatDS.cxx:
  Standard_Integer nb_floats = ds->myNbX * ds->myNbY * ds->myNbZ;
  Standard_Integer nb_slices = RealToInt(ceil(nb_floats / 32.0)); // 32 values in 1 slice
  // myData[0 .. nb_slices - 1][0 .. 31]
  if (nb_slices)
  {
    Standard_Integer i1 = 0, i2 = 0;
    Standard_Real small = Precision::Confusion() * Precision::Confusion();
    for (i1 = 0; i1 < nb_slices; i1++)
    {
      if (((Standard_ShortReal**)ds->myData)[i1])
      {
	for (i2 = 0; i2 < 32; i2++)
	{
	  Standard_ShortReal value = ((Standard_ShortReal*)((Standard_ShortReal**)ds->myData)[i1])[i2];
	  if (fabs(value) > small)
	  {
	    fwrite(&i1, sizeof(Standard_Integer), 1, f);
	    fwrite(&i2, sizeof(Standard_Integer), 1, f);
	    fwrite(&value, sizeof(Standard_ShortReal), 1, f);
	  }
	}
      }
    }
  }

  fclose(f);
  return Standard_True;
}
