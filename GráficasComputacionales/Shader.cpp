#include "Shader.h"

#include "Input.h"
#include <iostream>
#include <vector>

Shader::Shader()
{
	_shaderHandle = 0;
}

Shader::~Shader()
{
	glDeleteShader(_shaderHandle);
}

void Shader::CreateShader(std::string path, GLenum type)
{
	InputFile ifile;
	if (!ifile.Read(path)) return;
	std::string source = ifile.GetContents();

	if (_shaderHandle)
		glDeleteShader(_shaderHandle);

	_shaderHandle = glCreateShader(type);

	const GLchar *source_c = (const GLchar*)source.c_str();
	glShaderSource(_shaderHandle, 1, &source_c, nullptr);

	glCompileShader(_shaderHandle);

	// Get compile status
	GLint shaderCompileSuccess = 0;
	glGetShaderiv(_shaderHandle, GL_COMPILE_STATUS, &shaderCompileSuccess);
	if (shaderCompileSuccess == GL_FALSE)
	{
		// Get compile log length
		GLint logLength = 0;
		glGetShaderiv(_shaderHandle, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{

			// Allocate memory for compile log
			std::vector<GLchar> compileLog(logLength);

			// Get compile log
			glGetShaderInfoLog(_shaderHandle, logLength, &logLength, &compileLog[0]);

			// Print compile log
			for (int i = 0; i<logLength; i++)
				std::cout << compileLog[i];
			std::cout << std::endl;
		}
		std::cout << "Shader " << path << " did not compiled." << std::endl;

		//We don't need the shader anymore.
		glDeleteShader(_shaderHandle);

		return;
	}

	std::cout << "Shader " << path << " compiled successfully" << std::endl;
}

GLuint Shader::GetHandle()
{
	return _shaderHandle;
}