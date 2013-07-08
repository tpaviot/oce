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

/***********************************************************************
 
     FONCTION :
     ----------
        Classe V3d_View :
 
     HISTORIQUE DES MODIFICATIONS   :
     --------------------------------
      16-08-98 : CAL ; S3892. Ajout grilles 3d.
      16-09-98 : BGN ; Points d'entree du Triedre (S3819, Phase 1)
      21-09-98 : CAL ; Activation de l'echo que si CSF_GraphicEcho est definie.
      22-09-98 : BGN ; S3989 (anciennement S3819)
                       TypeOfTriedron* from Aspect (pas V3d)
      02.15.100 : JR : Clutter
      28/05/02 :  VSV: ZBUFFER mode of Trihedron

************************************************************************/

#define IMP240100       //GG
//			-> In Compute() method call MyViewer->ShowGridEcho()


/*----------------------------------------------------------------------*/
/*
 * Includes
 */
#include <V3d_View.jxx>

#include <TColStd_Array2OfReal.hxx>

#include <gp_Dir2d.hxx>

#include <Aspect.hxx>

#include <V3d_RectangularGrid.hxx>
#include <V3d_CircularGrid.hxx>

// For the echo of the chosen point
#include <Visual3d_TransientManager.hxx>

/*----------------------------------------------------------------------*/
/*
 * Constant
 */

#define MYEPSILON1 0.0001		// Comparison with 0.0
#define MYEPSILON2 M_PI / 180.	// Delta between 2 angles

/*----------------------------------------------------------------------*/

void V3d_View::SetGrid (const gp_Ax3& aPlane, const Handle(Aspect_Grid)& aGrid)
{
	MyPlane	= aPlane;
	MyGrid	= aGrid;

	Standard_Real xl, yl, zl;
	Standard_Real xdx, xdy, xdz;
	Standard_Real ydx, ydy, ydz;
	Standard_Real dx, dy, dz;
	aPlane.Location ().Coord (xl, yl, zl);
	aPlane.XDirection ().Coord (xdx, xdy, xdz);
	aPlane.YDirection ().Coord (ydx, ydy, ydz);
	aPlane.Direction ().Coord (dx, dy, dz);

	Standard_Real CosAlpha = Cos (MyGrid->RotationAngle ());
	Standard_Real SinAlpha = Sin (MyGrid->RotationAngle ());

	TColStd_Array2OfReal Trsf1 (1, 4, 1, 4);
	Trsf1 (4, 4) = 1.0;
	Trsf1 (4, 1) = Trsf1 (4, 2) = Trsf1 (4, 3) = 0.0;
	// Translation
	Trsf1 (1, 4) = xl,
	Trsf1 (2, 4) = yl,
	Trsf1 (3, 4) = zl;
	// Transformation change of marker
	Trsf1 (1, 1) = xdx,
	Trsf1 (2, 1) = xdy,
	Trsf1 (3, 1) = xdz,
	Trsf1 (1, 2) = ydx,
	Trsf1 (2, 2) = ydy,
	Trsf1 (3, 2) = ydz,
	Trsf1 (1, 3) = dx,
	Trsf1 (2, 3) = dy,
	Trsf1 (3, 3) = dz;

	TColStd_Array2OfReal Trsf2 (1, 4, 1, 4);
	Trsf2 (4, 4) = 1.0;
	Trsf2 (4, 1) = Trsf2 (4, 2) = Trsf2 (4, 3) = 0.0;
	// Translation of the origin
	Trsf2 (1, 4) = -MyGrid->XOrigin (),
	Trsf2 (2, 4) = -MyGrid->YOrigin (),
	Trsf2 (3, 4) = 0.0;
	// Rotation Alpha around axis -Z
	Trsf2 (1, 1) = CosAlpha,
	Trsf2 (2, 1) = -SinAlpha,
	Trsf2 (3, 1) = 0.0,
	Trsf2 (1, 2) = SinAlpha,
	Trsf2 (2, 2) = CosAlpha,
	Trsf2 (3, 2) = 0.0,
	Trsf2 (1, 3) = 0.0,
	Trsf2 (2, 3) = 0.0,
	Trsf2 (3, 3) = 1.0;

	Standard_Real valuetrsf;
	Standard_Real valueoldtrsf;
	Standard_Real valuenewtrsf;
	Standard_Integer i, j, k;
	// Calculation of the product of matrices
	for (i=1; i<=4; i++)
	    for (j=1; j<=4; j++) {
		MyTrsf (i, j) = 0.0;
		for (k=1; k<=4; k++) {
		    valueoldtrsf = Trsf1 (i, k);
		    valuetrsf	 = Trsf2 (k, j);
		    valuenewtrsf = MyTrsf (i, j) + valueoldtrsf * valuetrsf;
		    MyTrsf (i, j) = valuenewtrsf;
		}
	   }
}

void V3d_View::SetGridActivity (const Standard_Boolean AFlag)
{
	if (AFlag) MyGrid->Activate ();
	else MyGrid->Deactivate ();
}

void V3d_View::SetGridGraphicValues (const Handle(Aspect_Grid)& )
{
}

Graphic3d_Vertex V3d_View::Compute (const Graphic3d_Vertex & AVertex) const
{
	Graphic3d_Vertex CurPoint, NewPoint;
	Standard_Real X1, Y1, Z1, X2, Y2, Z2;
	Standard_Real XPp, YPp;

	MyView->ViewOrientation ().ViewReferencePlane ().Coord (X1, Y1, Z1);
	MyPlane.Direction ().Coord (X2, Y2, Z2);

	gp_Dir VPN (X1, Y1, Z1);
	gp_Dir GPN (X2, Y2, Z2);

	AVertex.Coord (X1, Y1, Z1);
	Project (X1, Y1, Z1, XPp, YPp);

	// Casw when the plane of the grid and the plane of the view
	// are perpendicular to MYEPSILON2 close radians
	if (Abs (VPN.Angle (GPN) - M_PI / 2.) < MYEPSILON2) {
		NewPoint.SetCoord (X1, Y1, Z1);
#ifdef IMP240100
		MyViewer->ShowGridEcho(this,NewPoint);
#endif	//IMP240100
		return NewPoint;
	}

	Standard_Boolean IsRectangular = 
		MyGrid->IsKind (STANDARD_TYPE (Aspect_RectangularGrid));

	Graphic3d_Vertex P1;

	Standard_Real XO = 0.0, YO = 0.0;
	Standard_Real XOp, YOp;
	Standard_Real XAp, YAp;
	Standard_Real XBp, YBp;

	X1 = XO, Y1 = YO, Z1 = 0.0;
	// MyTrsf * Point to return to the plane of 3D grid
	P1.SetCoord (X1, Y1, Z1);
	CurPoint = V3d_View::TrsPoint (P1, MyTrsf);
	CurPoint.Coord (X2, Y2, Z2);
	Project (X2, Y2, Z2, XOp, YOp);
	XPp = XPp - XOp, YPp = YPp - YOp;

    if (IsRectangular) {
		Standard_Real XS, YS;
		Handle(Aspect_RectangularGrid) theGrid =
			*(Handle(Aspect_RectangularGrid) *) &MyGrid;
		XS = theGrid->XStep (), YS = theGrid->YStep ();

		X1 = XO + XS, Y1 = YO, Z1 = 0.0;
		// MyTrsf *  Point to return to the plane of 3D grid
		P1.SetCoord (X1, Y1, Z1);
		CurPoint = V3d_View::TrsPoint (P1, MyTrsf);
		CurPoint.Coord (X2, Y2, Z2);
		Project (X2, Y2, Z2, XAp, YAp);
		XAp = XAp - XOp, YAp = YAp - YOp;

		X1 = XO, Y1 = YO + YS, Z1 = 0.0;
		// MyTrsf *  Point to return to the plane of 3D grid
		P1.SetCoord (X1, Y1, Z1);
		CurPoint = V3d_View::TrsPoint (P1, MyTrsf);
		CurPoint.Coord (X2, Y2, Z2);
		Project (X2, Y2, Z2, XBp, YBp);
		XBp = XBp - XOp, YBp = YBp - YOp;

		Standard_Real Determin = XAp*YBp - XBp*YAp;

		Z1 = 0.0;
		if (Abs (Determin) > MYEPSILON1) {
			X1 = (YBp*XPp - XBp*YPp) / Determin;
			Y1 = (XAp*YPp - YAp*XPp) / Determin;
			X1 = (X1 > 0. ?
			Standard_Real (Standard_Integer (Abs (X1)+0.5)) * XS :
			- Standard_Real (Standard_Integer (Abs (X1)+0.5)) * XS);
			Y1 = (Y1 > 0. ?
			Standard_Real (Standard_Integer (Abs (Y1)+0.5)) * YS :
			- Standard_Real (Standard_Integer (Abs (Y1)+0.5)) * YS);
			// MyTrsf *  Point to return to the plane of 3D grid
			P1.SetCoord (X1, Y1, Z1);
			CurPoint = V3d_View::TrsPoint (P1, MyTrsf);
			CurPoint.Coord (X2, Y2, Z2);
		}
		else {
			//cout << "*****************" << endl;
			//cout << "Zero Determinant!" << endl;
			//cout << "*****************" << endl;
			AVertex.Coord (X2, Y2, Z2);
			CurPoint.SetCoord (X2, Y2, Z2);
		}
	} // IsRectangular
    else {
		Standard_Real RS;
		Standard_Integer DN;
		Standard_Real Alpha;
		Handle(Aspect_CircularGrid) theGrid =
			*(Handle(Aspect_CircularGrid) *) &MyGrid;
		RS = theGrid->RadiusStep ();
		DN = theGrid->DivisionNumber ();
		Alpha = M_PI / Standard_Real (DN);

		Standard_Real DistOP = Sqrt (XPp*XPp + YPp*YPp);

		Standard_Integer i, ICur=0;
		Standard_Real Angle, AngleCur;
		Standard_Real XCurp=0, YCurp=0;
		gp_Dir2d OP (XPp, YPp);
		AngleCur = 2 * M_PI;
		for (i=1; i<=DN*2; i++) {
			X1 = XO + Cos (Alpha * i) * RS,
			Y1 = YO + Sin (Alpha * i) * RS,
			Z1 = 0.0;
			// MyTrsf * Point to return to the plane of 3D grid
			P1.SetCoord (X1, Y1, Z1);
			CurPoint = V3d_View::TrsPoint (P1, MyTrsf);
			CurPoint.Coord (X2, Y2, Z2);
			Project (X2, Y2, Z2, XAp, YAp);
			XAp = XAp - XOp, YAp = YAp - YOp;
			gp_Dir2d OA (XAp, YAp);
			Angle = OP.Angle (OA);
			if (Abs (AngleCur) > Abs (Angle)) {
				ICur = i;
				AngleCur = Angle;
				XCurp = XAp, YCurp = YAp;
			}

		} // for (i=1; i<=DN*2; i++)

		Standard_Real DistOCur = Sqrt (XCurp*XCurp + YCurp*YCurp);

		// Determination of the circle of the grid closest to P
		Standard_Integer N = Standard_Integer (DistOP / DistOCur + 0.5);
		Standard_Real Radius = N * RS;

		X1 = Cos (Alpha * ICur) * Radius,
		Y1 = Sin (Alpha * ICur) * Radius,
		Z1 = 0.0;

		// MyTrsf * Point to return to the plane of 3D grid
		P1.SetCoord (X1, Y1, Z1);
		CurPoint = V3d_View::TrsPoint (P1, MyTrsf);
		CurPoint.Coord (X2, Y2, Z2);
	} // IsCircular

	NewPoint.SetCoord (CurPoint.X (), CurPoint.Y (), CurPoint.Z ());

#ifdef IMP240100
	MyViewer->ShowGridEcho(this,NewPoint);
#endif	//IMP240100
	return NewPoint;
}

// Triedron methods : the Triedron is a non-zoomable object.

void V3d_View::ZBufferTriedronSetup(const Quantity_NameOfColor XColor,
				    const Quantity_NameOfColor YColor,
				    const Quantity_NameOfColor ZColor,
				    const Standard_Real        SizeRatio,
				    const Standard_Real        AxisDiametr,
				    const Standard_Integer     NbFacettes)
{
  MyView->ZBufferTriedronSetup(XColor, YColor, ZColor, SizeRatio, AxisDiametr, NbFacettes);
}

void V3d_View::TriedronDisplay (const Aspect_TypeOfTriedronPosition APosition,
 const Quantity_NameOfColor AColor, const Standard_Real AScale, const V3d_TypeOfVisualization AMode )
{
	MyView->TriedronDisplay (APosition, AColor, AScale, (AMode == V3d_WIREFRAME));
}

void V3d_View::TriedronErase ( )
{
	MyView->TriedronErase ( );
}

void V3d_View::TriedronEcho (const Aspect_TypeOfTriedronEcho AType )
{
	MyView->TriedronEcho (AType);
}

void V3d_View::GetGraduatedTrihedron(/* Names of axes */
                                     TCollection_ExtendedString &xname,
                                     TCollection_ExtendedString &yname,
                                     TCollection_ExtendedString &zname,
                                     /* Draw names */
                                     Standard_Boolean& xdrawname, 
                                     Standard_Boolean& ydrawname, 
                                     Standard_Boolean& zdrawname,
                                     /* Draw values */
                                     Standard_Boolean& xdrawvalues, 
                                     Standard_Boolean& ydrawvalues, 
                                     Standard_Boolean& zdrawvalues,
                                     /* Draw grid */
                                     Standard_Boolean& drawgrid,
                                     /* Draw axes */
                                     Standard_Boolean& drawaxes,
                                     /* Number of splits along axes */
                                     Standard_Integer& nbx, 
                                     Standard_Integer& nby, 
                                     Standard_Integer& nbz,
                                     /* Offset for drawing values */
                                     Standard_Integer& xoffset, 
                                     Standard_Integer& yoffset, 
                                     Standard_Integer& zoffset,
                                     /* Offset for drawing names of axes */
                                     Standard_Integer& xaxisoffset, 
                                     Standard_Integer& yaxisoffset, 
                                     Standard_Integer& zaxisoffset,
                                     /* Draw tickmarks */
                                     Standard_Boolean& xdrawtickmarks, 
                                     Standard_Boolean& ydrawtickmarks, 
                                     Standard_Boolean& zdrawtickmarks,
                                     /* Length of tickmarks */
                                     Standard_Integer& xtickmarklength, 
                                     Standard_Integer& ytickmarklength, 
                                     Standard_Integer& ztickmarklength,
                                     /* Grid color */
                                     Quantity_Color& gridcolor,
                                     /* X name color */
                                     Quantity_Color& xnamecolor,
                                     /* Y name color */
                                     Quantity_Color& ynamecolor,
                                     /* Z name color */
                                     Quantity_Color& znamecolor,
                                     /* X color of axis and values */
                                     Quantity_Color& xcolor,
                                     /* Y color of axis and values */
                                     Quantity_Color& ycolor,
                                     /* Z color of axis and values */
                                     Quantity_Color& zcolor,
                                     /* Name of font for names of axes */
                                     TCollection_AsciiString &fontOfNames,
                                     /* Style of names of axes */
                                     Font_FontAspect& styleOfNames,
                                     /* Size of names of axes */
                                     Standard_Integer& sizeOfNames,
                                     /* Name of font for values */
                                     TCollection_AsciiString &fontOfValues,
                                     /* Style of values */
                                     Font_FontAspect& styleOfValues,
                                     /* Size of values */
                                     Standard_Integer& sizeOfValues) const
{
    MyView->GetGraduatedTrihedron(/* Names of axes */
                                  xname, 
                                  yname, 
                                  zname,
                                  /* Draw names */
                                  xdrawname, 
                                  ydrawname, 
                                  zdrawname,
                                  /* Draw values */
                                  xdrawvalues, 
                                  ydrawvalues, 
                                  zdrawvalues,
                                  /* Draw grid */
                                  drawgrid,
                                  /* Draw axes */
                                  drawaxes,
                                  /* Number of splits along axes */
                                  nbx, 
                                  nby, 
                                  nbz,
                                  /* Offset for drawing values */
                                  xoffset, 
                                  yoffset, 
                                  zoffset,
                                  /* Offset for drawing names of axes */
                                  xaxisoffset, 
                                  yaxisoffset, 
                                  zaxisoffset,
                                  /* Draw tickmarks */
                                  xdrawtickmarks, 
                                  ydrawtickmarks, 
                                  zdrawtickmarks,
                                  /* Length of tickmarks */
                                  xtickmarklength, 
                                  ytickmarklength, 
                                  ztickmarklength,
                                  /* Grid color */
                                  gridcolor,
                                  /* X name color */
                                  xnamecolor,
                                  /* Y name color */
                                  ynamecolor,
                                  /* Z name color */
                                  znamecolor,
                                  /* X color of axis and values */
                                  xcolor,
                                  /* Y color of axis and values */
                                  ycolor,
                                  /* Z color of axis and values */
                                  zcolor,
                                  /* Name of font for names of axes */
                                  fontOfNames,
                                  /* Style of names of axes */
                                  styleOfNames,
                                  /* Size of names of axes */
                                  sizeOfNames,
                                  /* Name of font for values */
                                  fontOfValues,
                                  /* Style of values */
                                  styleOfValues,
                                  /* Size of values */
                                  sizeOfValues);
}

void V3d_View::GraduatedTrihedronDisplay(/* Names of axes */
                                         const TCollection_ExtendedString &xname, 
                                         const TCollection_ExtendedString &yname, 
                                         const TCollection_ExtendedString &zname,
                                         /* Draw names */
                                         const Standard_Boolean xdrawname, 
                                         const Standard_Boolean ydrawname, 
                                         const Standard_Boolean zdrawname,
                                         /* Draw values */
                                         const Standard_Boolean xdrawvalues, 
                                         const Standard_Boolean ydrawvalues, 
                                         const Standard_Boolean zdrawvalues,
                                         /* Draw grid */
                                         const Standard_Boolean drawgrid,
                                         /* Draw axes */
                                         const Standard_Boolean drawaxes,
                                         /* Number of splits along axes */
                                         const Standard_Integer nbx, 
                                         const Standard_Integer nby, 
                                         const Standard_Integer nbz,
                                         /* Offset for drawing values */
                                         const Standard_Integer xoffset, 
                                         const Standard_Integer yoffset, 
                                         const Standard_Integer zoffset,
                                         /* Offset for drawing names of axes */
                                         const Standard_Integer xaxisoffset, 
                                         const Standard_Integer yaxisoffset, 
                                         const Standard_Integer zaxisoffset,
                                         /* Draw tickmarks */
                                         const Standard_Boolean xdrawtickmarks, 
                                         const Standard_Boolean ydrawtickmarks, 
                                         const Standard_Boolean zdrawtickmarks,
                                         /* Length of tickmarks */
                                         const Standard_Integer xtickmarklength, 
                                         const Standard_Integer ytickmarklength, 
                                         const Standard_Integer ztickmarklength,
                                         /* Grid color */
                                         const Quantity_Color& gridcolor,
                                         /* X name color */
                                         const Quantity_Color& xnamecolor,
                                         /* Y name color */
                                         const Quantity_Color& ynamecolor,
                                         /* Z name color */
                                         const Quantity_Color& znamecolor,
                                         /* X color of axis and values */
                                         const Quantity_Color& xcolor,
                                         /* Y color of axis and values */
                                         const Quantity_Color& ycolor,
                                         /* Z color of axis and values */
                                         const Quantity_Color& zcolor,
                                         /* Name of font for names of axes */
                                         const TCollection_AsciiString &fontOfNames,
                                         /* Style of names of axes */
                                         const Font_FontAspect styleOfNames,
                                         /* Size of names of axes */
                                         const Standard_Integer sizeOfNames,
                                         /* Name of font for values */
                                         const TCollection_AsciiString &fontOfValues,
                                         /* Style of values */
                                         const Font_FontAspect styleOfValues,
                                         /* Size of values */
                                         const Standard_Integer sizeOfValues)
{
    MyView->GraduatedTrihedronDisplay(/* Names of axes */
                                      xname, 
                                      yname, 
                                      zname,
                                      /* Draw names */
                                      xdrawname, 
                                      ydrawname, 
                                      zdrawname,
                                      /* Draw values */
                                      xdrawvalues, 
                                      ydrawvalues, 
                                      zdrawvalues,
                                      /* Draw grid */
                                      drawgrid,
                                      /* Draw axes */
                                      drawaxes,
                                      /* Number of splits along axes */
                                      nbx, 
                                      nby, 
                                      nbz,
                                      /* Offset for drawing values */
                                      xoffset, 
                                      yoffset, 
                                      zoffset,
                                      /* Offset for drawing names of axes */
                                      xaxisoffset, 
                                      yaxisoffset, 
                                      zaxisoffset,
                                      /* Draw tickmarks */
                                      xdrawtickmarks, 
                                      ydrawtickmarks, 
                                      zdrawtickmarks,
                                      /* Length of tickmarks */
                                      xtickmarklength, 
                                      ytickmarklength, 
                                      ztickmarklength,
                                      /* Grid color */
                                      gridcolor,
                                      /* X name color */
                                      xnamecolor,
                                      /* Y name color */
                                      ynamecolor,
                                      /* Z name color */
                                      znamecolor,
                                      /* X color of axis and values */
                                      xcolor,
                                      /* Y color of axis and values */
                                      ycolor,
                                      /* Z color of axis and values */
                                      zcolor,
                                      /* Name of font for names of axes */
                                      fontOfNames,
                                      /* Style of names of axes */
                                      styleOfNames,
                                      /* Size of names of axes */
                                      sizeOfNames,
                                      /* Name of font for values */
                                      fontOfValues,
                                      /* Style of values */
                                      styleOfValues,
                                      /* Size of values */
                                      sizeOfValues);
}

void V3d_View::GraduatedTrihedronErase()
{
    MyView->GraduatedTrihedronErase();
}
