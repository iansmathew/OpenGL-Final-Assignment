#pragma once

#include "ModelBase.h"

class ModelPyramid : public ModelBase
{
public:
	ModelPyramid(int, int);
	~ModelPyramid();


public:
	/*
	Sets up the buffers and textures of the objects.
	All unique model data is defined within this function.
	Override this function in derived classes using the following template
	*/
	virtual void init(GLuint program) override;
};

