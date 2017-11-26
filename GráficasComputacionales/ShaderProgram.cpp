#include "ShaderProgram.h"

#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <memory>

ShaderProgram::ShaderProgram()
{
	_programHandle = 0;
}

ShaderProgram::~ShaderProgram()
{
	DeleteProgram();
}

void ShaderProgram::CreateProgram()
{
	_programHandle = glCreateProgram();
}

void ShaderProgram::AttachShader(std::string name, GLenum type)
{
	std::unique_ptr<Shader> shader(new Shader);
	shader->CreateShader(name, type);
	_attachedShaders.push_back(std::move(shader));
}

void ShaderProgram::LinkProgram()
{
	for (size_t i = 0; i < _attachedShaders.size(); i++)
		glAttachShader(_programHandle, _attachedShaders[i]->GetHandle());

	glLinkProgram(_programHandle);

	// Get status
	GLint linkSuccess = 0;
	glGetProgramiv(_programHandle, GL_LINK_STATUS, &linkSuccess);
	if (linkSuccess == GL_FALSE)
	{
		// Get link log length
		GLint logLength = 0;
		glGetProgramiv(_programHandle, GL_INFO_LOG_LENGTH, &logLength);

		if (logLength > 0)
		{
			// Allocate memory for link log
			std::vector<GLchar> linkLog(logLength);

			// Get link log
			glGetProgramInfoLog(_programHandle, logLength, &logLength, &linkLog[0]);

			// Print link log
			for (size_t i = 0; i < linkLog.size(); i++)
				std::cout << linkLog[i];
			std::cout << std::endl;
		}
		std::cout << "Shaders could not be linked." << std::endl;

		// Delete and detach shaders; delte program handle
		DeleteProgram();

		return;
	}

	std::cout << "Build succeeded... " << std::endl;

	DeleteAndDetachShaders();
}

void ShaderProgram::Activate()
{
	glUseProgram(_programHandle);
}

void ShaderProgram::Deactivate()
{
	glUseProgram(0);
}

void ShaderProgram::SetAttribute(GLuint locationIndex, std::string name)
{
	glBindAttribLocation(_programHandle, locationIndex, name.c_str());
}

void ShaderProgram::SetUniformf(std::string name, float value)
{
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform1f(uniformLocation, value);
}

void ShaderProgram::SetUniformf(std::string name, float x, float y)
{
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform2f(uniformLocation, x, y);
}

void ShaderProgram::SetUniformf(std::string name, float x, float y, float z)
{
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform3f(uniformLocation, x, y, z);
}

void ShaderProgram::SetUniformf(std::string name, glm::vec3 value)
{
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform3fv(uniformLocation, 1, glm::value_ptr(value));
}

void ShaderProgram::SetUniformf(std::string name, float x, float y, float z, float w)
{
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform4f(uniformLocation, x, y, z, w);
}

void ShaderProgram::SetUniformi(std::string name, int value)
{
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform1i(uniformLocation, value);
}

void ShaderProgram::SetUniformMatrix(std::string name, glm::mat3 matrix)
{
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::SetUniformMatrix(std::string name, glm::mat4 matrix)
{
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}


void ShaderProgram::DeleteAndDetachShaders()
{
	for (size_t i = 0; i < _attachedShaders.size(); i++)
		glDetachShader(_programHandle, _attachedShaders[i]->GetHandle());

	_attachedShaders.clear();
}

void ShaderProgram::DeleteProgram()
{
	DeleteAndDetachShaders();
	glDeleteProgram(_programHandle);
}