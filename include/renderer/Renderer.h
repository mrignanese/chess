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
	Renderer(const Renderer&) = delete;
	~Renderer() = default;

	static Renderer& Get();

	inline static void Clear() {
		return Get().ClearImpl();
	}

	inline static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) {
		return Get().DrawImpl(va, ib, shader);
	}

	static void EnableBlending() {
		return Get().EnableBlendingImpl();
	}

	Renderer& operator=(const Renderer&) = delete;

   private:
	Renderer();

	void ClearImpl();
	void DrawImpl(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	void EnableBlendingImpl();
};
