#include "ShaderProgram.h"

// El constructor inicializa los valores por default de las variables.
ShaderProgram::ShaderProgram() {
	_programHandle = 0;
}

// El destructor manda a llamar el método DeleteProgram()
ShaderProgram::~ShaderProgram() {
	DeleteProgram();
}
// Encargado de crear el programa shader utilizando la instrucción de OpenGL adecuada.
// Guarda un identificador del programa creado en la variable _programHandle.
void ShaderProgram::CreateProgram() {
	_programHandle = glCreateProgram();
}

// recibe la ruta a un archivo shader (path) y el tipo de shader que se quiere crear (type) con
// los cuales se creará un apuntador único a un objeto de clase Shader y se incluirá en la lista 
// _attachedShaders. La lista _attachedShaders es una lista de unique_ptr
// Se utilizan apuntadores (unique_ptr) en este método para evitar que la referencia al objeto original 
// se pierda cuando el método termina. Para poder utilizar apuntadores en un archivo fuente, es necesario 
// hacer uso de la librería memory.
void ShaderProgram::AttachShader(std::string name, GLenum type) {
	// Create and add the shaders to a list
	std::unique_ptr<Shader> shader(new Shader);
	shader->CreateShader(name, type);
	_attachedShaders.push_back(std::move(shader));
}


// El método LinkProgram()tiene que adjuntar los shaders en la lista _attachedShaders al programa shader 
// utilizando el método glAttachShader(). Después, iniciar el proceso de linkeo utilizando la función de 
// OpenGL adecuada.Por último, debe mandar a llamar el método DeleteAndDetachShaders().
void ShaderProgram::LinkProgram() {
	int i = 0;
	while (i < _attachedShaders.size())
	{

		// Ese get lo que hace es regresar un apuntador al objeto Shader que tienen en la lista en la 
		// posición i. glAttachShader no recibe un objeto Shader como segundo parámetro, lo que recibe es un 
		// identificador del shader que creaste (ya sea un vertex o fragment). Ese identificador lo obtienes 
		// con el método GetHandle() de la clase Shader.
		glAttachShader(_programHandle, _attachedShaders.at(i).get()->GetHandle());
		i++;
	}
	glLinkProgram(_programHandle);
	DeleteAndDetachShaders();
}

// El método Activate() hace bind del programa shader para poderlo usar.
void ShaderProgram::Activate() {
	glUseProgram(_programHandle);

}

// El método Deactivate() hace unbind del programa shader.
void ShaderProgram::Deactivate() {
	// glUseProgram(0) es para desactivar cualquier Shader Program que estuviera activo.
	glUseProgram(0);
}

// El método SetAttribute(...) es el encargado de hacer la relación entre el índice en el shader de un VBO
// (locationIndex) y el nombre de la variable(name) en el shader.
void ShaderProgram::SetAttribute(GLuint locationIndex, std::string name) {
	//Asociamos un buffer con índice locationIndex a la variable name en el shader
	glBindAttribLocation(_programHandle, locationIndex, name.c_str());
}

// Los métodos SetUniformf(...) reciben el nombre (name) de un uniform en el shader y el valor de la variable. 
// Este método debe encontrar la posición de la variable en el shader, utilizando la función de OpenGL adecuada, 
// y darles el valor correcto.
void ShaderProgram::SetUniformf(std::string name, float x, float y) {
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform2f(uniformLocation, x, y);
}

void ShaderProgram::SetUniformf(std::string name, float x, float y, float z) {
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform3f(uniformLocation, x, y, z);
}

void ShaderProgram::SetUniformf(std::string name, float x, float y, float z, float w) {
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform4f(uniformLocation, x, y, z, w);
}

// El método DeleteAndDetachShaders() recorre la lista _attachedShaders y los va eliminando del programa shader
// uno por uno utilizando la función glDetachShader().Al terminar este proceso, debe borrar la lista.
void ShaderProgram::DeleteAndDetachShaders() {
	int i = 0;
	while (i < _attachedShaders.size())
	{

		glDetachShader(_programHandle, _attachedShaders.at(i)->GetHandle());
		i++;
	}
	_attachedShaders.clear();
}

// El método DeleteProgram() llama al método DeleteAndDetachShaders() y borra el programa shader guardado en
// el identificador _programHandle.
void ShaderProgram::DeleteProgram() {
	DeleteAndDetachShaders();
	glDeleteProgram(_programHandle);
}