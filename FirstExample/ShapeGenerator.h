#pragma once
#include "ModelBase.h"

class ShapeGenerator
{
public:
	ShapeGenerator();
	~ShapeGenerator();

private:
	ModelBase* cube;
	ModelBase* cone;
	ModelBase* cutCone;
	ModelBase* diamond;
	ModelBase* frustum;
	ModelBase* halfHexagon;
	ModelBase* hexagon;
	ModelBase* prism;
	ModelBase* pyramid;
	ModelBase* torus;
	ModelBase* wedge;

public:
	void init(const GLuint program);

	void drawCube()	const { cube->draw(); }
	void drawCone()	const { cone->draw(); }
	void drawCutCone() const { cutCone->draw(); }
	void drawDiamond() const { diamond->draw(); }
	void drawFrustum() const { frustum->draw(); }
	void drawHalfHexagon() const { halfHexagon->draw(); }
	void drawHexagon() const { hexagon->draw(); }
	void drawPrism() const { prism->draw(); }
	void drawPyramid() const { pyramid->draw(); }
	void drawTorus() const { torus->draw(); }
	void drawWedge() const { wedge->draw(); }
};	

