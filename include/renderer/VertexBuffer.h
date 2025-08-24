#pragma once

#include "GLpch.h"

class VertexBuffer {
   public:
	VertexBuffer(const GLvoid* data, GLsizeiptr size);
	VertexBuffer(const VertexBuffer&) = delete;
	~VertexBuffer();

	VertexBuffer& operator=(const VertexBuffer&) = delete;

	void Bind() const;
	void Unbind() const;

   private:
	GLuint mRendererID;
};