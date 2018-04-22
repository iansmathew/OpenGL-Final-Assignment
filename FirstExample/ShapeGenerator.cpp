#include "ShapeGenerator.h"



ShapeGenerator::ShapeGenerator()
{
}


ShapeGenerator::~ShapeGenerator()
{
}

void ShapeGenerator::init(const GLuint program)
{
	cube = new ModelBase(program,		"../Media/Model/Cube.obj");
	cone = new ModelBase(program,		"../Media/Model/HexCone.obj");
	cutCone	= new ModelBase(program,	"../Media/Model/HexCone_NoTop.obj");
	diamond	= new ModelBase(program,	"../Media/Model/Diamond.obj");
	frustum	= new ModelBase(program,	"../Media/Model/Frustum.obj");
	halfHexagon	= new ModelBase(program,"../Media/Model/HalfHexagon.obj");
	hexagon	= new ModelBase(program,	"../Media/Model/Hexagon.obj");
	prism = new ModelBase(program,		"../Media/Model/Prism.obj");
	pyramid	= new ModelBase(program,	"../Media/Model/Pyramid.obj");
	torus = new ModelBase(program,		"../Media/Model/Torus.obj");
	wedge = new ModelBase(program,		"../Media/Model/Wedge.obj");
	plane = new ModelBase(program,		"../Media/Model/Plane.obj");

}




