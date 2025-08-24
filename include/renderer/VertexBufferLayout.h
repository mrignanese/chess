#pragma once

#include <vector>

#include "GLError.h"
#include "GLpch.h"

struct VertexBufferElement {
	GLenum type;
	GLuint count;
	GLboolean normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
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

/*
VertexBufferLayout class:
manages the description of vertex attributes in a vertex buffer.
For example:
    - first attribute: vertex positions (2 floats)
    - second attribute: texture coordinates (2 floats).
*/

class VertexBufferLayout {
   public:
	VertexBufferLayout() : mStride(0) {};
	VertexBufferLayout(const VertexBufferLayout&) = delete;
	~VertexBufferLayout() = default;

	template <typename T>
	void Push(unsigned int count);

	VertexBufferLayout& operator=(const VertexBufferLayout&) = delete;

	inline const std::vector<VertexBufferElement>& GetElements() const {
		return mElements;
	}

	inline GLsizei GetStride() const {
		return mStride;
	}

   private:
	std::vector<VertexBufferElement> mElements;
	GLsizei mStride; // distance in bytes between two elements (vertices) of the VBO
};

// template specializations of Push for float, unsigned int and unsigned char types
template <>
inline void VertexBufferLayout::Push<float>(unsigned int count) {
	mElements.push_back({GL_FLOAT, count, GL_FALSE});
	mStride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template <>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
	mElements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
	mStride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template <>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
	mElements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
	mStride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}