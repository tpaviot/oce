// File:	AIS_ExclusionFilter.cxx
// Created:	Fri Nov 28 14:20:52 1997
// Author:	Robert COUBLANC
//		<rob@robox.paris1.matra-dtv.fr>


#include <AIS_ExclusionFilter.ixx>
#include <TColStd_ListOfInteger.hxx>
#include <TColStd_ListIteratorOfListOfInteger.hxx>
#include <TColStd_DataMapIteratorOfDataMapOfIntegerListOfInteger.hxx>
#include <AIS_InteractiveObject.hxx>

//=======================================================================
//function : AIS_ExclusionFilter
//purpose  : Constructors
//=======================================================================

AIS_ExclusionFilter::AIS_ExclusionFilter(const Standard_Boolean ExclusionFlagOn):
myIsExclusionFlagOn(ExclusionFlagOn)
{
}

AIS_ExclusionFilter::AIS_ExclusionFilter(const AIS_KindOfInteractive TypeToExclude,
					 const Standard_Boolean ExclusionFlagOn):
myIsExclusionFlagOn(ExclusionFlagOn)
{
  TColStd_ListOfInteger L;
  myStoredTypes.Bind((Standard_Integer)TypeToExclude,L);
}

AIS_ExclusionFilter::AIS_ExclusionFilter(const AIS_KindOfInteractive TypeToExclude,
					 const Standard_Integer SignatureInType,
					 const Standard_Boolean ExclusionFlagOn):
myIsExclusionFlagOn(ExclusionFlagOn)
{
  TColStd_ListOfInteger L;
  L.Append(SignatureInType);
  myStoredTypes.Bind((Standard_Integer)TypeToExclude,L);
}

//=======================================================================
//function : Add
//purpose  : 
//=======================================================================
Standard_Boolean AIS_ExclusionFilter::Add(const AIS_KindOfInteractive TypeToExclude) 
{
  if(IsStored(TypeToExclude)) 
    return Standard_False;
  TColStd_ListOfInteger L;
  myStoredTypes.Bind((Standard_Integer)TypeToExclude,L);
  return Standard_True;
}

Standard_Boolean AIS_ExclusionFilter::Add(const AIS_KindOfInteractive TypeToExclude,
					  const Standard_Integer SignatureInType) 
{
  if(!IsStored(TypeToExclude)){
    TColStd_ListOfInteger L;
    L.Append(SignatureInType);
    myStoredTypes.Bind((Standard_Integer)TypeToExclude,L);
    return Standard_True;
  }

  myStoredTypes((Standard_Integer)TypeToExclude).Append(SignatureInType);
  return Standard_True;
}

//=======================================================================
//function : Remove
//purpose  : 
//=======================================================================

Standard_Boolean AIS_ExclusionFilter::Remove(const AIS_KindOfInteractive TypeToExclude) 
{
  if(!IsStored(TypeToExclude)) return Standard_False;
  myStoredTypes((Standard_Integer)TypeToExclude).Clear();
  myStoredTypes.UnBind((Standard_Integer)TypeToExclude);
  return Standard_True;
}

Standard_Boolean AIS_ExclusionFilter::Remove(const AIS_KindOfInteractive TypeToExclude,
					     const Standard_Integer SignatureInType) 
{
  if(!IsStored(TypeToExclude)) return Standard_False;
  TColStd_ListOfInteger& LL = myStoredTypes.ChangeFind((Standard_Integer)TypeToExclude);
  for(TColStd_ListIteratorOfListOfInteger it(LL);it.More();it.Next()){
    if(it.Value()==SignatureInType){
      LL.Remove(it);
      return Standard_True;
    }
  }
  return Standard_False;
}


//=======================================================================
//function : Clear
//purpose  : 
//=======================================================================

void  AIS_ExclusionFilter::Clear()
{
  TColStd_DataMapIteratorOfDataMapOfIntegerListOfInteger Mit(myStoredTypes);
  for(;Mit.More();Mit.Next())
    myStoredTypes.ChangeFind(Mit.Key()).Clear();
  myStoredTypes.Clear();
}

//=======================================================================
//function : IsStored
//purpose  : 
//=======================================================================

Standard_Boolean AIS_ExclusionFilter::IsStored(const AIS_KindOfInteractive aType) const
{
  return myStoredTypes.IsBound(Standard_Integer(aType));
}

//=======================================================================
//function : IsSignatureIn
//purpose  : 
//=======================================================================
Standard_Boolean AIS_ExclusionFilter::IsSignatureIn(const AIS_KindOfInteractive aType,
						    const Standard_Integer SignatureInType) const
{
  if(!myStoredTypes.IsBound(aType)) return Standard_False;
  for(TColStd_ListIteratorOfListOfInteger Lit(myStoredTypes((Standard_Integer)aType));
      Lit.More();
      Lit.Next()){
    if(Lit.Value()==SignatureInType)
      return Standard_True;
  }
  return Standard_False;
}

//=======================================================================
//function : ListOfStoredTypes
//purpose  : 
//=======================================================================

void AIS_ExclusionFilter::ListOfStoredTypes(TColStd_ListOfInteger& TheList) const
{
  TheList.Clear();
  TColStd_DataMapIteratorOfDataMapOfIntegerListOfInteger MIT(myStoredTypes);
  for(;MIT.More();MIT.Next())
    TheList.Append(MIT.Key());
}

//=======================================================================
//function : ListOfSignature
//purpose  : 
//=======================================================================

void AIS_ExclusionFilter::ListOfSignature(const AIS_KindOfInteractive aType,TColStd_ListOfInteger& TheStoredList) const
{
  TheStoredList.Clear();
  if(IsStored(aType))
    for(TColStd_ListIteratorOfListOfInteger it(myStoredTypes(aType));it.More();it.Next())
      TheStoredList.Append(it.Value());
}

//=======================================================================
//function : IsOk
//purpose  : 
//=======================================================================

Standard_Boolean AIS_ExclusionFilter::IsOk(const Handle(SelectMgr_EntityOwner)& EO) const
{
  if(myStoredTypes.IsEmpty())
    return myIsExclusionFlagOn;

  if(EO.IsNull()) 
    return Standard_False;
  Handle(AIS_InteractiveObject) IO = Handle(AIS_InteractiveObject)::DownCast(EO->Selectable());
  if(IO.IsNull()) 
    return Standard_False;

  // type of AIS is not in the map...
  if(!myStoredTypes.IsBound(IO->Type()))
    return myIsExclusionFlagOn ;
  // type of AIS is not in the map and there is no signature indicated
  if(myStoredTypes(IO->Type()).IsEmpty())
    return !myIsExclusionFlagOn ;
  // one or several signatures are indicated...
  if(IsSignatureIn(IO->Type(),IO->Signature()))
    return !myIsExclusionFlagOn;
  
  return myIsExclusionFlagOn;
}







