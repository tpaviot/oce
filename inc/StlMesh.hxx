// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _StlMesh_HeaderFile
#define _StlMesh_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Handle_StlMesh_Mesh_HeaderFile
#include <Handle_StlMesh_Mesh.hxx>
#endif
class StlMesh_Mesh;
class StlMesh_Mesh;
class StlMesh_MeshExplorer;
class StlMesh_MeshDomain;
class StlMesh_MeshTriangle;
class StlMesh_SequenceOfMeshDomain;
class StlMesh_SequenceOfMeshTriangle;
class StlMesh_SequenceOfMesh;
class StlMesh_SequenceNodeOfSequenceOfMeshDomain;
class StlMesh_SequenceNodeOfSequenceOfMeshTriangle;
class StlMesh_SequenceNodeOfSequenceOfMesh;


//! Implements a  basic  mesh data-structure  for  the <br>
//!          needs of the application fast prototyping. <br>
//! <br>
class StlMesh  {
public:

  DEFINE_STANDARD_ALLOC

  //! Make a merge of two Mesh and returns a new Mesh. <br>
//!          Very useful if you want to merge partMesh and CheckSurfaceMesh <br>
//!          for example <br>
  Standard_EXPORT   static  Handle_StlMesh_Mesh Merge(const Handle(StlMesh_Mesh)& mesh1,const Handle(StlMesh_Mesh)& mesh2) ;





protected:





private:




friend class StlMesh_Mesh;
friend class StlMesh_MeshExplorer;
friend class StlMesh_MeshDomain;
friend class StlMesh_MeshTriangle;
friend class StlMesh_SequenceOfMeshDomain;
friend class StlMesh_SequenceOfMeshTriangle;
friend class StlMesh_SequenceOfMesh;
friend class StlMesh_SequenceNodeOfSequenceOfMeshDomain;
friend class StlMesh_SequenceNodeOfSequenceOfMeshTriangle;
friend class StlMesh_SequenceNodeOfSequenceOfMesh;

};





// other Inline functions and methods (like "C++: function call" methods)


#endif
