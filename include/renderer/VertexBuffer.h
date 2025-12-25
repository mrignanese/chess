#pragma once

#include <GL/glew.h>

class VertexBuffer {
   public:
	VertexBuffer(const GLvoid* data, GLsizeiptr size);
	VertexBuffer(const VertexBuffer&) = delete;
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	VertexBuffer& operator=(const VertexBuffer&) = delete;

   private:
	GLuint mRendererID;
};
