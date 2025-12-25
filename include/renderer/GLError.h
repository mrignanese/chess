#pragma once

#include <GL/glew.h>

#include <signal.h>
#include <string>

#define ASSERT(x) \
	if (!(x))     \
	raise(SIGTRAP)

#define GLCall(x)   \
	GLClearError(); \
	x;              \
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
std::string GLErrorToString(GLenum error);
GLboolean GLLogCall(const GLchar* function, const GLchar* file, GLint line);
