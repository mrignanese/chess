#pragma once

#include <GL/glew.h>

#include <cstdint>

class IndexBuffer {
   public:
	IndexBuffer(const GLvoid* data, uint32_t count);
	IndexBuffer(const IndexBuffer&) = delete;
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	IndexBuffer& operator=(const IndexBuffer&) = delete;

	uint32_t GetCount() const;

   private:
	GLuint mRendererID;
	uint32_t mCount;
};
