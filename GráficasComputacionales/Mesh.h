#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <glm/glm.hpp>


class Mesh {
private:
	GLuint _vertexArrayObject;
	GLuint _positionsVertexBufferObject;
	GLuint _colorsVertexBufferObject;
	GLuint _vertexCount;
	void SetAttributeData(GLuint buffer, const GLsizeiptr size, const void* data, GLenum usage, GLuint locationIndex, const GLint components);

public:
	Mesh();
	~Mesh();
	void CreateMesh(GLint vertexCount);
	void Draw(GLenum primitive);
	void SetPositionAttribute(std::vector<glm::vec2> positions, GLenum usage, GLuint locationIndex);
	void SetPositionAttribute(std::vector<glm::vec3> positions, GLenum usage, GLuint locationIndex);
	void SetColorAttribute(std::vector<glm::vec3> colors, GLenum usage, GLuint locationIndex);
	void SetColorAttribute(std::vector<glm::vec4> colors, GLenum usage, GLuint locationIndex);
};