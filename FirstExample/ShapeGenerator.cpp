#include "ShapeGenerator.h"



ShapeGenerator::ShapeGenerator()
{
}


ShapeGenerator::~ShapeGenerator()
{
}

void ShapeGenerator::init(const GLuint program)
{
	cube = new ModelBase(program, "../Media/Model/Cube.obj", "../Media/Textures/rubiksTexture.png");
	cone = new ModelBase(program, "../Media/Model/Cone.obj", "../Media/Textures/rubiksTexture.png");
	cutCone	= new ModelBase(program, "../Media/Model/CutCone.obj", "../Media/Textures/rubiksTexture.png");
	diamond	= new ModelBase(program, "../Media/Model/Diamond.obj", "../Media/Textures/rubiksTexture.png");
	frustum	= new ModelBase(program, "../Media/Model/Frustum.obj", "../Media/Textures/rubiksTexture.png");
	halfHexagon	= new ModelBase(program, "../Media/Model/HalfHexagon.obj", "../Media/Textures/rubiksTexture.png");
	hexagon	= new ModelBase(program, "../Media/Model/Hexagon.obj", "../Media/Textures/rubiksTexture.png");
	prism = new ModelBase(program, "../Media/Model/Prism.obj", "../Media/Textures/rubiksTexture.png");
	pyramid	= new ModelBase(program, "../Media/Model/Pyramid.obj", "../Media/Textures/rubiksTexture.png");
	torus = new ModelBase(program, "../Media/Model/Torus.obj", "../Media/Textures/rubiksTexture.png");
	wedge = new ModelBase(program, "../Media/Model/Wedge.obj", "../Media/Textures/rubiksTexture.png");
}




