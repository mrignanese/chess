#include "renderer/Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "renderer/GLError.h"

Shader::Shader(const std::string& filepath) : mFilePath(filepath) {
	const auto& [vertexSource, fragmentSource] = ParseShader(filepath);
	mRendererID = CreateShader(vertexSource, fragmentSource);
}

Shader::~Shader() {
	GLCall(glDeleteProgram(mRendererID));
}

void Shader::Bind() const {
	GLCall(glUseProgram(mRendererID));
}

void Shader::Unbind() const {
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, GLint value) {
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, GLfloat value) {
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

std::pair<std::string, std::string> Shader::ParseShader(const std::string& filepath) {
	// open file specified by <filepath>, parse the content and return two strings
	// containing vertex shader and fragment shader source code
	std::ifstream stream(filepath);

	enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

	std::string line;
	std::stringstream ss[2];
	ShaderType type;

	// parse shader file
	while (getline(stream, line)) {
		// deduce shader type
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		// shader code
		else
			// store shader code with newline character at the end of each line
			ss[(int)type] << line << '\n';
	}

	return {ss[0].str(), ss[1].str()};
}

GLuint Shader::CompileShader(GLenum type, const std::string& source) {
	// create shader and compile it. If compilation succed returns a non-zero ID
	GLCall(GLuint id = glCreateShader(type));  // create shader
	const GLchar* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));  // set shader source code
	GLCall(glCompileShader(id));                   // compile shader

	// check if compilation errors occured. If compilation failed,
	// display error message
	GLint result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		GLint length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		// allocate message on the stack but dynamically
		GLchar* message = (GLchar*)alloca(length * sizeof(GLchar));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
		          << std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(id));

		return 0;
	}

	return id;
}

GLuint Shader::CreateShader(const std::string& vertex, const std::string& fragment) {
	// create program (the shader ID) and compile both vertex and fragment shader
	GLCall(GLuint program = glCreateProgram());
	GLuint vs = CompileShader(GL_VERTEX_SHADER, vertex);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragment);

	// combine the two shaders in one single program
	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

GLint Shader::GetUniformLocation(const std::string& name) {
	// check if the uniform location was already queried and cached
	if (mUniformLocationCache.find(name) != mUniformLocationCache.end())
		return mUniformLocationCache[name];

	// query OpenGL for the uniform location in the shader program
	GLCall(GLint location = glGetUniformLocation(mRendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' does not exist!" << std::endl;

	// cache the result (including -1) to avoid repeated OpenGL calls
	mUniformLocationCache[name] = location;

	return location;
}
