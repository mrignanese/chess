#pragma once

#include <GL/glew.h>

#include <cstdint>
#include <vector>

#include "GLError.h"

struct VertexBufferElement {
	GLenum type;			// element data type (e.g, GL_FLOAT, GL_UNSIGNED_INT, etc.)
	GLuint count;			// how many elements of the specified type
	GLboolean normalized;	// true only for GL_UNSIGNED_BYTE

	static uint32_t GetSizeOfType(uint32_t type) {
		switch (type) {
			case GL_FLOAT:
				return 4;
			case GL_UNSIGNED_INT:
				return 4;
			case GL_UNSIGNED_BYTE:
				return 1;
		}

		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout {
   public:
	VertexBufferLayout() : mStride(0) {};
	VertexBufferLayout(const VertexBufferLayout&) = delete;
	~VertexBufferLayout() = default;

	template <typename T>
	void Push(uint32_t count);

	VertexBufferLayout& operator=(const VertexBufferLayout&) = delete;

	inline const std::vector<VertexBufferElement>& GetElements() const {
		return mElements;
	}

	inline GLsizei GetStride() const {
		return mStride;
	}

   private:
	std::vector<VertexBufferElement> mElements;
	GLsizei mStride;  // distance in bytes between two elements (vertices) of the VBO
};

// template specializations of Push for float, unsigned int and unsigned char types
template <>
inline void VertexBufferLayout::Push<float>(uint32_t count) {
	mElements.push_back({GL_FLOAT, count, GL_FALSE});
	mStride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template <>
inline void VertexBufferLayout::Push<uint32_t>(uint32_t count) {
	mElements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
	mStride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template <>
inline void VertexBufferLayout::Push<u_char>(uint32_t count) {
	mElements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
	mStride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}
