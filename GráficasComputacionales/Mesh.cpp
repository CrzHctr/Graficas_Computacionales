#include "Mesh.h"
#include <iostream>


Mesh::Mesh() {
	_vertexArrayObject = 0;
	_positionsVertexBufferObject = 0;
	_colorsVertexBufferObject = 0;
	_normalsVertexBufferObject = 0;
	_vertexCount = 0;
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &_positionsVertexBufferObject);
	glDeleteBuffers(1, &_colorsVertexBufferObject);
	glDeleteVertexArrays(1, &_vertexArrayObject);
	glDeleteBuffers(1, &_normalsVertexBufferObject);
	glDeleteBuffers(1, &_texCoordsVertexBufferObject);
}

// El método CreateMesh(vertexCount:GLint) inicializa la variable _vertexCount con el valor vertexCount
// enviado al método.También crea un VAO y guarda su identificador en la variable _vertexArrayObject.
void Mesh::CreateMesh(GLint vertexCount) {
	_vertexCount = vertexCount;
	// Queremos generar 1 manager
	// Crea un VAO y guarda su identificador en la variable _vertexArrayObject
	glGenVertexArrays(1, &_vertexArrayObject);
}


// El método Draw() hace bind del VAO y dibuja todos los vértices de la malla poligonal utilizando las 
// variables primitive y _vertexCount.Utilizar la función de dibujado glDrawArrays. Al finalizar la 
// instrucción de dibujado, debe hacer un unbind del VAO.
void Mesh::Draw(GLenum primitive) {
	// Utilizar el vao. A partir de este momento, todos VBOs creados y configurados
	// se van a asociar a este manager.
	// Activamos el manager, en este momento se activan todos los
	// VBOs asociados automáticamente.
	glBindVertexArray(_vertexArrayObject);
	//Función de dibujado sin índices
	// glDrawArrays(GLenum mode, GLint first, GLsizei count);
	// En donde mode especifica la primitiva a utilizar, first es el índice inicial de los VBOs para 
	//comenzar a dibujar la geometría y count hace referencia al número de vértices a dibujar.
	//glDrawArrays(primitive, 0, _vertexCount);
	//Terminamos de utilizar el manager y se hace
	// unbind del VAO.
	//glBindVertexArray(0);

	if (_indicesCount == 0) {
		glDrawArrays(primitive, 0, _vertexCount);
	}
	else {
		glDrawElements(primitive, _indicesCount, GL_UNSIGNED_INT, nullptr);
	}
	glBindVertexArray(0);
}


// El método SetPositionAttribute(...) recibe una lista de posiciones de vértices (positions), un hint 
// de uso del atributo en memoria(usage) y el índice del atributo que se debe activar en el 
// shader(locationIndex), los cuales utiliza, junto con la variable de instancia 
// _positionsVertexBufferObject, para llamar al método SetAttributeData(...). Si la lista de posiciones 
// está vacía o el número de elementos en la lista no coincide con el valor de _vertexCount, este método 
// no hace nada.
void Mesh::SetPositionAttribute(std::vector<glm::vec2> positions, GLenum usage, GLuint locationIndex) {
	if (positions.size() == 0 || positions.size() != _vertexCount) {
		return;
	}
	SetAttributeData(_positionsVertexBufferObject, sizeof(glm::vec2) * positions.size(), positions.data(),
		usage, locationIndex, 2);
	std::cout << "Posiciones vec2: " << positions.size() << std::endl;

}

// Aplica lo mismo que arriba pero con vec3
void Mesh::SetPositionAttribute(std::vector<glm::vec3> positions, GLenum usage, GLuint locationIndex) {
	if (positions.size() == 0 || positions.size() != _vertexCount) {
		return;
	}
	SetAttributeData(_positionsVertexBufferObject, sizeof(glm::vec3) * positions.size(), positions.data(),
		usage, locationIndex, 3);
	std::cout << "Posiciones vec3: " << positions.size() << std::endl;

}



// El método SetColorAttribute(...) recibe una lista de colores de vértices (colors), un hint de uso del 
// atributo en memoria (usage) y el índice del atributo que se debe activar en el shader (locationIndex), 
// los cuales utiliza, junto con la variable de instancia _colorsVertexBufferObject, para llamar al método 
// SetAttributeData(...). Si la lista de colores está vacía o el número de elementos en la lista no coincide 
// con el valor de _vertexCount, este método no hace nada.
void Mesh::SetColorAttribute(std::vector<glm::vec3> colors, GLenum usage, GLuint locationIndex) {
	if (colors.size() == 0 || colors.size() != _vertexCount) {
		return;
	}
	SetAttributeData(_colorsVertexBufferObject, sizeof(glm::vec3) * colors.size(), colors.data(), usage,
		locationIndex, 3);
	std::cout << "Colores vec2: " << colors.size() << std::endl;

}

void Mesh::SetColorAttribute(std::vector<glm::vec4> colors, GLenum usage, GLuint locationIndex) {
	if (colors.size() == 0 || colors.size() != _vertexCount) {
		return;
	}
	SetAttributeData(_colorsVertexBufferObject, sizeof(glm::vec4) * colors.size(), colors.data(), usage,
		locationIndex, 4);
	std::cout << "Colores vec3: " << colors.size() << std::endl;
}

// El método SetAttributeData(...) es el encargado de crear un nuevo VBO con los datos proporcionados. 
// buffer es el identificador del VBO que se va a crear. Si buffer ya existe (ha sido creado antes por lo 
// que es diferente de 0), primero se debe borrar para que siempre se cree uno nuevo (revisar manual de 
// referencia en la presentación). size es el tamaño de la lista de datos en bytes. data son los datos en 
// la lista del atributo. usage es un hint de uso que se le dará al atributo para determinar en qué tipo de 
// memoria guardarlo. locationIndex es el índice del atributo que debe activarse en el shader. Finalmente, 
// components es el número de componentes de cada uno de los elementos en la lista del atributo.
// Por ejemplo, si se quiere mandar a llamar SetAttributeData(...), desde el método 
// SetPositionAttribute(...), para crear el VBO del atributo de posiciones con componentes(x, y, z), 
// se haría de la siguiente manera : 
// SetAttributeData(_positionsVertexBufferObject, sizeof(glm::vec3) * positions.size(), positions.data(), 
//					usage, locationIndex, 3);



void Mesh::SetNormalAttribute(std::vector<glm::vec3> normal, GLenum usage, GLuint locationIndex)
{
	if (normal.size() > 0 && normal.size() == _vertexCount)
		SetAttributeData(_normalsVertexBufferObject, sizeof(glm::vec3) * normal.size(), normal.data(), usage, locationIndex, 3);
}

void Mesh::SetTexCoordAttribute(std::vector<glm::vec2> texCoords, GLenum usage, GLuint locationIndex)
{
	if (texCoords.size() > 0 && texCoords.size() == _vertexCount)
		SetAttributeData(_normalsVertexBufferObject, sizeof(glm::vec3) * texCoords.size(), texCoords.data(), usage, locationIndex, 2);
}

void Mesh::SetAttributeData(GLuint buffer, const GLsizeiptr size, const void * data, GLenum usage,
	GLuint locationIndex, const GLint components) {

	// buffer es el identificador del VBO que se va a crear.
	// Si buffer ya existe (ha sido creado antes por lo que es diferente de 0), primero se debe borrar 
	// para que siempre se cree uno nuevo
	if (buffer != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// Utilizar el vao. A partir de este momento, todos VBOs creados y configurados
	// se van a asociar a este manager.
	// Activamos el manager, en este momento se activan todos los
	// VBOs asociados automáticamente.
	glBindVertexArray(_vertexArrayObject);

	// buffer es el identificador del VBO que se va a crear.
	// Creación del VBO posiciones
	glGenBuffers(1, &buffer);
	// Activamos el buffer de posiciones para poder utilizarlo
	glBindBuffer(GL_ARRAY_BUFFER, buffer);


	// Creamos la memoria y la inicializamos con los datos del atributo de posiciones.
	// size es el tamaño de la lista de datos en bytes. data son los datos en 
	// la lista del atributo. usage es un hint de uso que se le dará al atributo para determinar en qué tipo de 
	// memoria guardarlo.
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);

	//Activamos el atributo en la tarjeta de video
	glEnableVertexAttribArray(locationIndex); //Posición
											  //Configuraos los datos del atributo en la tarjeta de video
	glVertexAttribPointer(locationIndex, components, GL_FLOAT, GL_FALSE, 0, nullptr);

	//Ya no se utiliza este VBO, así que lo desactivamos
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Desactivamos el manager del buffer
	glBindVertexArray(0);
}

void Mesh::SetIndices(std::vector<unsigned int> indices, GLenum usage) {
	if (indices.size() != 0) {

		_indicesCount = indices.size();

		if (_indicesBufferObject != 0) {
			glDeleteBuffers(1, &_indicesBufferObject);
		}

		glBindVertexArray(_vertexArrayObject);

		glGenBuffers(1, &_indicesBufferObject);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesBufferObject);

		//GL_ELEMENT_ARRAY_BUFFER = Se usa ya que los indices no son atributos únicos, si no se usaría 
		// GL_ARRAY_BUFFER
		//sizeof(unsigned int) * indices.size() // sizeof saca el tamaño en bytes de lo que se mande
		// y luego se multiplica por el tamaño del arreglo
		//indices.data() es un apuntador a los datos de la lista
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), usage);

		glBindVertexArray(0);


	}
	else {
		return;
	}
}
