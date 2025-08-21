#pragma once

#include <vector>

#include "GL_pch.h"
#include "Renderer.h"

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

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

class VertexBufferLayout {
   private:
	std::vector<VertexBufferElement> mElements;
	unsigned int mStride;

   public:
	VertexBufferLayout() : mStride(0) {};

	template <typename T>
	void Push(unsigned int count);

	inline unsigned int GetStride() const {
		return mStride;
	}

	inline const std::vector<VertexBufferElement>& GetElements() const {
		return mElements;
	}
};

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