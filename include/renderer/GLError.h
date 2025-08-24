#pragma once

#include <signal.h>
#include <string>

#include "GLpch.h"

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