#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <IL/il.h>
#include <glm/glm.hpp>

class Texture2D
{

private:
	GLuint _textureId;
	ILuint imageID;

public:
	Texture2D();
	~Texture2D();
	void LoadTexture(std::string path);
	void Bind();
	void Unbind();
};