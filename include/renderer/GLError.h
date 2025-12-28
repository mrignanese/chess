#pragma once

#include <GL/glew.h>

#include <signal.h>
#include <string>

#define ASSERT(x) \
	if (!(x))     \
	raise(SIGTRAP)

#if DEBUG
#define GLCall(x)   \
	GLClearError(); \
	x;              \
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#endif

void GLClearError();
std::string GLErrorToString(GLenum error);
GLboolean GLLogCall(const GLchar* function, const GLchar* file, GLint line);
