// File:	TopOpeBRepTool_box.hxx
// Created:	Tue Apr  1 11:22:56 1997
// Author:	Jean Yves LEBEY
//		<jyl@bistrox.paris1.matra-dtv.fr>

#include <TopOpeBRepTool_box.hxx>

#include <TopOpeBRepTool_HBoxTool.hxx>
#include <Bnd_Box.hxx>

Standard_EXPORT void FBOX_Prepare() 
{
  Handle(TopOpeBRepTool_HBoxTool) hbt = FBOX_GetHBoxTool();
  hbt->Clear();
#ifdef DEB
  if (TopOpeBRepTool_GettraceBOX()) {
    cout<<endl<<"TOOLBOX : Prepare"<<endl;
  }
#endif
}

Standard_EXPORT Handle(TopOpeBRepTool_HBoxTool) FBOX_GetHBoxTool()
{
  static Handle(TopOpeBRepTool_HBoxTool) GLOBAL_TOOLBOX_hboxtool;
  if (GLOBAL_TOOLBOX_hboxtool.IsNull()) {
    GLOBAL_TOOLBOX_hboxtool = new TopOpeBRepTool_HBoxTool();
  }
  return GLOBAL_TOOLBOX_hboxtool;
}

Standard_EXPORT const Bnd_Box& FBOX_Box(const TopoDS_Shape& S)
{
  Handle(TopOpeBRepTool_HBoxTool) hbt = FBOX_GetHBoxTool();
#ifdef DEB
  if (TopOpeBRepTool_GettraceBOX()) {
    Standard_Integer i = hbt->Index(S);
    Standard_Integer n = hbt->Extent();
    cout<<"TOOLBOX : "<<i<<"/"<<n<<endl;
  }
#endif
  return hbt->Box(S);
}
