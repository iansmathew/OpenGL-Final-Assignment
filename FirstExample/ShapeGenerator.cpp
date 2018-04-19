#include "ShapeGenerator.h"



ShapeGenerator::ShapeGenerator()
{
}


ShapeGenerator::~ShapeGenerator()
{
}

void ShapeGenerator::init(const GLuint program)
{
	cube = new ModelBase(program,		"../Media/Model/Cube.obj",			"../Media/Textures/brick.png");
	cone = new ModelBase(program,		"../Media/Model/Cone.obj",			"../Media/Textures/brick.png");
	cutCone	= new ModelBase(program,	"../Media/Model/CutCone.obj",		"../Media/Textures/brick.png");
	diamond	= new ModelBase(program,	"../Media/Model/Diamond.obj",		"../Media/Textures/brick.png");
	frustum	= new ModelBase(program,	"../Media/Model/Frustum.obj",		"../Media/Textures/brick.png");
	halfHexagon	= new ModelBase(program,"../Media/Model/HalfHexagon.obj",	"../Media/Textures/brick.png");
	hexagon	= new ModelBase(program,	"../Media/Model/Hexagon.obj",		"../Media/Textures/brick.png");
	prism = new ModelBase(program,		"../Media/Model/Prism.obj",			"../Media/Textures/brick.png");
	pyramid	= new ModelBase(program,	"../Media/Model/Pyramid.obj",		"../Media/Textures/brick.png");
	torus = new ModelBase(program,		"../Media/Model/Torus.obj",			"../Media/Textures/brick.png");
	wedge = new ModelBase(program,		"../Media/Model/Wedge.obj",			"../Media/Textures/brick.png");
}




