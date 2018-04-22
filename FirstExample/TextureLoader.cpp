#include "TextureLoader.h"

TextureLoader::TextureLoader()
{
}


TextureLoader::~TextureLoader()
{
	delete image;
}

void TextureLoader::init()
{
	glGenTextures((int)Textures::NUM_VALUES, textureBuffer);

	load(Textures::BRICK, "../Media/Textures/brick.png");
	load(Textures::COOBLESTONE, "../Media/Textures/cobblestone.png");
	load(Textures::GOLD, "../Media/Textures/gold.png");
	load(Textures::GRASS, "../Media/Textures/rockyGrass.png");
	load(Textures::SILVER, "../Media/Textures/silver.png");
	load(Textures::STONE, "../Media/Textures/stone.png");
	load(Textures::WOOD, "../Media/Textures/wood.png");

}

void TextureLoader::loadTexture(const GLuint program, Textures::ID Texture)
{
	glActiveTexture(GL_TEXTURE0 + (int)Texture);
	glBindTexture(GL_TEXTURE_2D, textureBuffer[(int)Texture]);
	glUniform1i(glGetUniformLocation(program, "texture0"), (int)Texture);
}

void TextureLoader::load(Textures::ID id, const char* texturePath)
{
	image = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGB);

	glActiveTexture(GL_TEXTURE0 + (int)id);
	glBindTexture(GL_TEXTURE_2D, textureBuffer[(int)id]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}


