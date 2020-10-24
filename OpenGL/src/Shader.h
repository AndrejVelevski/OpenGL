#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <unordered_map>

class Shader
{
private:
	unsigned int id;
	static unsigned int compileShader(int type, const char* source);
	static unsigned int linkProgram(unsigned int vertexShader, unsigned int fragmentShader);
	std::unordered_map<std::string, unsigned int> uniforms;

public:
	Shader();
	Shader(const std::string& vertexSource, const std::string& fragmentSource);
	~Shader();

	unsigned int getId();
	void setUniform1i(const std::string& uniform, int i);
	void setUniform1f(const std::string& uniform, float f);
	void setUniform2f(const std::string& uniform, const glm::vec2& vec);
	void setUniform3f(const std::string& uniform, const glm::vec3& vec);
	void setUniform4f(const std::string& uniform, const glm::vec4& vec);
	void setUniformMatrix4fv(const std::string& uniform, const glm::mat4& mat);

	void create(const std::string& vertexSource, const std::string& fragmentSource);
	void bind();
	void unbind();
};

