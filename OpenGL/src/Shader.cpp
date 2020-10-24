#include "Shader.h"

#include "Utils.h"
#include <glad\glad.h>
#include <iostream>
#include <sstream>
#include <fstream>

Shader::Shader()
{
	id = 0;
}

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
{
	create(vertexSource, fragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

unsigned int Shader::getId()
{
	return id;
}

void Shader::setUniform1i(const std::string& uniform, int i)
{
	auto iterator = uniforms.find(uniform);
	if (iterator != uniforms.end())
	{
		glUniform1i(iterator->second, i);
	}
	else
	{
		int location = glGetUniformLocation(id, uniform.c_str());
		uniforms.insert(std::make_pair(uniform, location));
		glUniform1i(location, i);
	}
}

void Shader::setUniform1f(const std::string& uniform, float f)
{
	auto iterator = uniforms.find(uniform);
	if (iterator != uniforms.end())
	{
		glUniform1f(iterator->second, f);
	}
	else
	{
		int location = glGetUniformLocation(id, uniform.c_str());
		uniforms.insert(std::make_pair(uniform, location));
		glUniform1f(location, f);
	}
}

void Shader::setUniform2f(const std::string& uniform, const glm::vec2& vec)
{
	auto iterator = uniforms.find(uniform);
	if (iterator != uniforms.end())
	{
		glUniform2f(iterator->second, vec.x, vec.y);
	}
	else
	{
		int location = glGetUniformLocation(id, uniform.c_str());
		uniforms.insert(std::make_pair(uniform, location));
		glUniform2f(location, vec.x, vec.y);
	}
}

void Shader::setUniform3f(const std::string& uniform, const glm::vec3& vec)
{
	auto iterator = uniforms.find(uniform);
	if (iterator != uniforms.end())
	{
		glUniform3f(iterator->second, vec.x, vec.y, vec.z);
	}
	else
	{
		int location = glGetUniformLocation(id, uniform.c_str());
		uniforms.insert(std::make_pair(uniform, location));
		glUniform3f(location, vec.x, vec.y, vec.z);
	}
}

void Shader::setUniform4f(const std::string& uniform, const glm::vec4& vec)
{
	auto iterator = uniforms.find(uniform);
	if (iterator != uniforms.end())
	{
		glUniform4f(iterator->second, vec.x, vec.y, vec.z, vec.z);
	}
	else
	{
		int location = glGetUniformLocation(id, uniform.c_str());
		uniforms.insert(std::make_pair(uniform, location));
		glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
	}
}

void Shader::setUniformMatrix4fv(const std::string& uniform, const glm::mat4& mat)
{
	auto iterator = uniforms.find(uniform);
	if (iterator != uniforms.end())
	{
		glUniformMatrix4fv(iterator->second, 1, GL_FALSE, glm::value_ptr(mat));
	}
	else
	{
		int location = glGetUniformLocation(id, uniform.c_str());
		uniforms.insert(std::make_pair(uniform, location));
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}
}

void Shader::create(const std::string& vertexSource, const std::string& fragmentSource)
{
	std::stringstream vertex, fragment;

	std::ifstream vertexFile(vertexSource);
	std::ifstream fragmentFile(fragmentSource);

	if (vertexFile.is_open())
	{
		std::string line;

		while (std::getline(vertexFile, line))
		{
			vertex << line << std::endl;
		}
		vertexFile.close();
	}

	if (fragmentFile.is_open())
	{
		std::string line;

		while (std::getline(fragmentFile, line))
		{
			fragment << line << std::endl;
		}
		fragmentFile.close();
	}

	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertex.str().c_str());
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragment.str().c_str());
	id = linkProgram(vertexShader, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::bind()
{
	glUseProgram(id);
}

void Shader::unbind()
{
	glUseProgram(0);
}

unsigned int Shader::compileShader(int type, const char* source)
{
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		char* message = new char[length];
		glGetShaderInfoLog(shader, length, nullptr, message);

		std::cerr << "Failed to compile shader:\n" << message << std::endl;
		delete[] message;
	}

	return shader;
}

unsigned int Shader::linkProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	unsigned int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetProgramInfoLog(program, length, nullptr, message);

		std::cerr << "Failed to link program:\n" << message << std::endl;
		delete[] message;
	}

	return program;
}