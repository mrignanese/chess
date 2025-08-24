#include "renderer/IndexBuffer.h"

#include "renderer/GLError.h"

IndexBuffer::IndexBuffer(const GLvoid* data, unsigned int count) : mCount(count) {
	// creates new IBO with 'data' and given count (number of elements).
	// Target: GL_ELEMENT_ARRAY_BUFFER
	GLCall(glGenBuffers(1, &mRendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
	GLCall(glDeleteBuffers(1, &mRendererID));
}

void IndexBuffer::Bind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID));
}

void IndexBuffer::Unbind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int IndexBuffer::GetCount() const {
	return mCount;
}