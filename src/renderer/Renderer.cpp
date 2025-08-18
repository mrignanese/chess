#include "renderer/Renderer.h"

#include <iostream>

void GLClearError() {
	// clean all current errors
	while (glGetError() != GL_NO_ERROR);
}

std::string GLErrorToString(GLenum error) {
	switch (error) {
		case GL_INVALID_ENUM:
			return std::string("GL_INVALID_ENUM");
		case GL_INVALID_VALUE:
			return std::string("GL_INVALID_VALUE");
		case GL_INVALID_OPERATION:
			return std::string("GL_INVALID_OPERATION");
		case GL_STACK_OVERFLOW:
			return std::string("GL_STACK_OVERFLOW");
		case GL_STACK_UNDERFLOW:
			return std::string("GL_STACK_UNDERFLOW");
		case GL_OUT_OF_MEMORY:
			return std::string("GL_OUT_OF_MEMORY");
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			return std::string("GL_INVALID_FRAMEBUFFER_OPERATION");
		case GL_CONTEXT_LOST:
			return std::string("GL_CONTEXT_LOST");
		default:
			return std::string("Unkown OpenGL error");
	}
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << GLErrorToString(error) << "): " << function << " " << file << " "
		          << line << std::endl;
		return false;
	}

	return true;
}

void Renderer::Clear() const {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) {
	shader.Bind();
	va.Bind();
	ib.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}