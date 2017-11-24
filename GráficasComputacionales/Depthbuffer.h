#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

class DepthBuffer {

private:
	GLuint _framebuffer;
	GLuint _depthmap;
	GLsizei _resolution;

public:
	DepthBuffer();
	~DepthBuffer();
	void Create(int resolution);
	void Bind();
	void Unbind();
	void BindDepthMap();
	void UnbindDepthMap();
};