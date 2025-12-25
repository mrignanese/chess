#include "renderer/Renderer.h"

#include <GL/glew.h>

#include <iostream>

#include "renderer/GLError.h"

Renderer::Renderer() {
	if (glewInit() != GLEW_OK)
		std::cout << "Failed to initialize GLEW!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;
}

Renderer& Renderer::Get() {
	static Renderer renderer;
	return renderer;
}

void Renderer::ClearImpl() {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::DrawImpl(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) {
	shader.Bind();
	va.Bind();
	ib.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::EnableBlendingImpl() {
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}