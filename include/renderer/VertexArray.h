#pragma once

#include "GLpch.h"
#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray {
   public:
	VertexArray();
	VertexArray(const VertexArray&) = delete;
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;

	VertexArray& operator=(const VertexArray&) = delete;

   private:
	GLuint mRendererID;
};