
#include <BRepGProp_EdgeTool.ixx>
#include <GeomAdaptor_Curve.hxx>
#include <Geom_Curve.hxx>
#include <Geom_BezierCurve.hxx>
#include <Geom_BSplineCurve.hxx>

Standard_Real  BRepGProp_EdgeTool::FirstParameter(const BRepAdaptor_Curve& C)
{
  return C.FirstParameter();
}

Standard_Real  BRepGProp_EdgeTool::LastParameter(const BRepAdaptor_Curve& C)
{
  return C.LastParameter();
}

Standard_Integer  BRepGProp_EdgeTool::IntegrationOrder(const BRepAdaptor_Curve& BAC)
{
  switch (BAC.GetType()) {

  case GeomAbs_Line :
    return 2;

  case GeomAbs_Parabola :
    return 5;

  case GeomAbs_BezierCurve :
    {
    const GeomAdaptor_Curve& GAC = BAC.Curve();
    const Handle(Geom_Curve)& GC = GAC.Curve();
    const Handle(Geom_BezierCurve)& GBZC = (*((Handle(Geom_BezierCurve)*)&GC));
    Standard_Integer n = 2*(GBZC->NbPoles()) - 1;
    return n; 
    }
    break;
  case GeomAbs_BSplineCurve :
    {
    const GeomAdaptor_Curve& GAC = BAC.Curve();
    const Handle(Geom_Curve)& GC = GAC.Curve();
    const Handle(Geom_BSplineCurve)& GBSC = (*((Handle(Geom_BSplineCurve)*)&GC));
    Standard_Integer n = 2*(GBSC->NbPoles()) - 1;
    return n; 
    }
    break;
    
    default :
      break;
  }
  //POP WE should return something : -> Default
  return 10;
}

gp_Pnt  BRepGProp_EdgeTool::Value(const BRepAdaptor_Curve& C, const Standard_Real U)
{
  return C.Value(U);
}

void  BRepGProp_EdgeTool::D1(const BRepAdaptor_Curve& C, 
	 const Standard_Real U, gp_Pnt& P, gp_Vec& V1)
{
  C.D1(U,P,V1);
}

// modified by NIZHNY-MKK  Thu Jun  9 12:15:15 2005.BEGIN
Standard_Integer BRepGProp_EdgeTool::NbIntervals(const BRepAdaptor_Curve& C,const GeomAbs_Shape S) 
{
  BRepAdaptor_Curve* pC = (BRepAdaptor_Curve*) &C; // at the moment actually NbIntervals() does not modify the 
                                                   // object "C". So it is safe to do such a cast.
  return pC->NbIntervals(S);
}

void BRepGProp_EdgeTool::Intervals(const BRepAdaptor_Curve& C,TColStd_Array1OfReal& T,const GeomAbs_Shape S) 
{
  BRepAdaptor_Curve* pC = (BRepAdaptor_Curve*) &C; // at the moment actually Intervals() does not modify the
                                                   // object "C". So it is safe to do such a cast.
  pC->Intervals(T, S);
}
// modified by NIZHNY-MKK  Thu Jun  9 12:15:18 2005.END
