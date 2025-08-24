#pragma once

#include "GLpch.h"

class IndexBuffer {
   public:
	IndexBuffer(const GLvoid* data, unsigned int count);
	IndexBuffer(const IndexBuffer&) = delete;
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	IndexBuffer& operator=(const IndexBuffer&) = delete;

	unsigned int GetCount() const;

   private:
	GLuint mRendererID;
	unsigned int mCount;
};