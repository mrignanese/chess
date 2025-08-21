#pragma once

#include <signal.h>

#include "GL_pch.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

#define ASSERT(x) \
	if (!(x))     \
	raise(SIGTRAP)

#define GLCall(x)   \
	GLClearError(); \
	x;              \
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
std::string GLErrorToString(GLenum error);

class Renderer {
   public:
	Renderer();
	~Renderer() = default;
	static void Clear();
	static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	void EnableBlending() const;
};