#include "Shader.h"
#include "Input.h"


Shader::Shader() {
	_shaderHandle = 0;
}

Shader::~Shader() {
	glDeleteShader(_shaderHandle);
}

// El método CreateShader(...) es el encargado de cargar el código, crear y compilar un archivo shader. 
// Utiliza la variable path para abrir un archivo con ese nombre y obtener el código fuente del shader.
// Crea un nuevo shader de tipo type(vertex shader o fragment shader) y guarda su identificador en la 
// variable _shaderHandle.Si la clase ya había cargado un shader antes(_shaderHandle tiene un valor diferente 
// a 0) entonces primero lo debe borrar para asegurar que siempre está creando un shader nuevo.El método es 
// responsable de llamar los métodos glShaderSource y glCompileShader.
void Shader::CreateShader(std::string path, GLenum type) {
	InputFile ifile;
	// Utiliza la variable path para abrir un archivo con ese nombre y obtener el código fuente del shader.
	ifile.Read(path);
	std::string fragmentSource = ifile.GetContents();

	// Si la clase ya había cargado un shader antes(_shaderHandle tiene un valor diferente 
	// a 0) entonces primero lo debe borrar para asegurar que siempre está creando un shader nuevo.
	if (_shaderHandle != 0) {
		glDeleteShader(_shaderHandle);
	}

	// Creamos un shader de tipo type y guarda su identificador en la variable _shaderHandle
	_shaderHandle = glCreateShader(type);
	//Obtener los datos en el formato correcto
	const GLchar *fragmentSource_c = (const GLchar*)fragmentSource.c_str();
	//Le estamos dando el código fuente a OpenGL para que se lo asigne a shader
	glShaderSource(_shaderHandle, 1, &fragmentSource_c, nullptr);
	//Compilamos el shader en busca de errores
	//Asumimos que no hay errores
	glCompileShader(_shaderHandle);
}

// Regresa el valor de la variable _shaderHandle.
GLuint Shader::GetHandle() {
	return _shaderHandle;
}