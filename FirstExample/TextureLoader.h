#pragma once
#include <vector>
#include <fstream>


#include "vgl.h"
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "SOIL.h"

namespace Textures {
	enum ID
	{
		BRICK,
		COOBLESTONE,
		GOLD,
		GRASS,
		SILVER,
		WOOD,
		STONE,
		NUM_VALUES
	};

}

class TextureLoader
{
public:
	TextureLoader();
	~TextureLoader();
	void init();
	void loadTexture(const GLuint program, Textures::ID Texture);

protected:

	int width;
	int height;
	unsigned char* image;

	GLuint textureBuffer[(int)Textures::NUM_VALUES];

	void load(Textures::ID id, const char * texturePath);

};
