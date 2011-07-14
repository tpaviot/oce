#include <TopoDS_Shape.hxx>
#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
#include <BRepGProp.hxx>
#include <GProp_GProps.hxx>
#include <iostream>

int main(int argc, char **argv){
    TopoDS_Shape shape;
    BRep_Builder builder;
    GProp_GProps prop;

    if (argc < 2)
    {
        std::cerr << "Usage: computeSurface file.brep" << std::endl;
        exit(1);
    }
    BRepTools::Read(shape, argv[1], builder);
    BRepGProp::SurfaceProperties(shape, prop);
    std::cout << "Total surface of all shapes: " << prop.Mass() << std::endl;
    return 0;
}
