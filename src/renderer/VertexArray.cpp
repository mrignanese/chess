#include "renderer/VertexArray.h"

#include "renderer/GLError.h"
#include "renderer/VertexBufferLayout.h"

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &mRendererID));
	GLCall(glBindVertexArray(mRendererID));
}

VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &mRendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	// add vertex buffer 'vb' to vertex array and specify how to interpret vb data
	// using the vertex buffer layout 'layout'
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		// stride: number of bytes between two VBO elements (vertices)
		// offset: numvre of bytes between two attributes of the same element
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized,
		                             layout.GetStride(), (const GLvoid*)(intptr_t)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const {
	GLCall(glBindVertexArray(mRendererID));
}

void VertexArray::Unbind() const {
	GLCall(glBindVertexArray(0));
}