#include "Mesh.h"
#include <iostream>

void Mesh::SetAttributeData(GLuint buffer, const GLsizeiptr size, const void * data, GLenum usage, GLuint locationIndex, const GLint components)
{
	if (buffer != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(_vertexArrayObject);
	glGenBuffers(1, &buffer);
	//Activamos el buffer de posiciones para poder utilizarlo
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//Creamos la memoria y la inicializamos con los datos del atributo de posiciones
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	//Activamos el atributo en la tarjeta de video
	glEnableVertexAttribArray(locationIndex); //Posición
											  //Configuraos los datos del atributo en la tarjeta de video
	glVertexAttribPointer(locationIndex, components, GL_FLOAT, GL_FALSE, 0, nullptr);
	//Ya no se utiliza este VBO, así que lo removemos
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::Mesh() {
	_vertexArrayObject = 0;
	_positionsVertexBufferObject = 0;
	_colorsVertexBufferObject = 0;
	_vertexCount = 0;
	_indicesBufferObject = 0;
	_indicesCount = 0;
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &_positionsVertexBufferObject);
	glDeleteBuffers(1, &_colorsVertexBufferObject);
	glDeleteVertexArrays(1, &_vertexArrayObject);
}

void Mesh::CreateMesh(GLint vertexCount) {
	_vertexCount = vertexCount;
	//Generamos un manager
	glGenVertexArrays(1, &_vertexArrayObject);
}

void Mesh::Draw(GLenum primitive) {
	//Utilizar el vao. A partir de este momento, todos los VBOs creados y 
	//configurados se van a asociar a este manager
	glBindVertexArray(_vertexArrayObject);
	if (_indicesCount > 0) {
		//std::cout << "Hola";
		glDrawElements(primitive, _indicesCount, GL_UNSIGNED_INT, nullptr);
	}
	else {
		//Función de dibujado sin índices
		glDrawArrays(primitive, 0, _vertexCount);
	}
	//Terminamos de utilizar el manager
	glBindVertexArray(0);
}



void Mesh::SetPositionAttribute(std::vector<glm::vec2> positions, GLenum usage, GLuint locationIndex) {
	if (positions.size() == 0 || positions.size() != _vertexCount)
		return;
	SetAttributeData(_positionsVertexBufferObject, sizeof(glm::vec2) * positions.size(), positions.data(), usage, locationIndex, 2);
}

void Mesh::SetPositionAttribute(std::vector<glm::vec3> positions, GLenum usage, GLuint locationIndex) {
	if (positions.size() == 0 || positions.size() != _vertexCount)
		return;
	SetAttributeData(_positionsVertexBufferObject, sizeof(glm::vec3) * positions.size(), positions.data(), usage, locationIndex, 3);
}

void Mesh::SetColorAttribute(std::vector<glm::vec3> colors, GLenum usage, GLuint locationIndex) {
	if (colors.size() == 0 || colors.size() != _vertexCount)
		return;
	SetAttributeData(_colorsVertexBufferObject, sizeof(glm::vec3) * colors.size(), colors.data(), usage, locationIndex, 3);
}

void Mesh::SetColorAttribute(std::vector<glm::vec4> colors, GLenum usage, GLuint locationIndex) {
	if (colors.size() == 0 || colors.size() != _vertexCount)
		return;
	SetAttributeData(_colorsVertexBufferObject, sizeof(glm::vec4) * colors.size(), colors.data(), usage, locationIndex, 4);
}

void Mesh::SetIndices(std::vector<unsigned int> indices, GLenum usage)
{
	_indicesCount = indices.size();
	if (_indicesCount == 0)
		return;

	if (_indicesBufferObject != 0)
		_indicesBufferObject = 0;

	glBindVertexArray(_vertexArrayObject);
	glGenBuffers(1, &_indicesBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*_indicesCount, indices.data(), usage);
	glBindVertexArray(0);
}
