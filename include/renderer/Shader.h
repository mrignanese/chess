#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

class Shader {
   public:
	Shader(const std::string& filepath);
	Shader(const Shader&) = delete;
	~Shader();

	void Bind() const;
	void Unbind() const;

	// methods to set uniforms
	void SetUniform1i(const std::string& name, GLint value);
	void SetUniform1f(const std::string& name, GLfloat value);
	void SetUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

	Shader& operator=(const Shader&) = delete;

   private:
	std::pair<std::string, std::string> ParseShader(const std::string& filepath);
	GLuint CompileShader(GLenum type, const std::string& source);
	GLuint CreateShader(const std::string& vertex, const std::string& fragment);

	GLint GetUniformLocation(const std::string& name);

	std::string mFilePath;
	GLuint mRendererID;
	std::unordered_map<std::string, GLint> mUniformLocationCache;
};
