#include "renderer/VertexBuffer.h"

#include "renderer/GLError.h"

VertexBuffer::VertexBuffer(const GLvoid* data, GLsizeiptr size) {
	// creates new VBO with <data> and given <size> in bytes.
	// Target: GL_ARRAY_BUFFER
	GLCall(glGenBuffers(1, &mRendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
	GLCall(glDeleteBuffers(1, &mRendererID));
}

void VertexBuffer::Bind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererID));
}

void VertexBuffer::Unbind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
