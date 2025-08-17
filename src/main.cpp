#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

int main() {
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	window = glfwCreateWindow(640, 480, "OpenGL", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	// make the window's context current
	glfwMakeContextCurrent(window);

	glfwSwapInterval(2);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[] = {
	    -0.5f, -0.5f, 0.0f, 0.0f,  // bottom-left
	    0.5f,  -0.5f, 1.0f, 0.0f,  // bottom-right
	    0.5f,  0.5f,  1.0f, 1.0f,  // top-right
	    -0.5f, 0.5f,  0.0f, 1.0f   // top-left
	};

	unsigned int indices[6] = {0, 1, 2, 2, 3, 0};

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	IndexBuffer ib(indices, 6);
	VertexArray va;
	VertexBufferLayout layout;

	layout.Push<float>(2);  // vertex coordinates
	layout.Push<float>(2);  // texture coordinates
	va.AddBuffer(vb, layout);

	// projection matrix to adjust for 4:3 aspect ration
	glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

	Shader shader("src/renderer/res/shader/Basic.shader");
	shader.Bind();
	shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
	shader.SetUniformMat4f("u_MVP", proj);

	Texture texture("src/renderer/res/textures/LightKnight.png");
	texture.Bind();
	// texture slot must match with one specified when binding the texture
	shader.SetUniform1i("u_Texture", 0);

	vb.Unbind();
	ib.Unbind();
	va.Unbind();
	shader.Unbind();

	Renderer renderer;

	float r1 = 0.0f;
	float increment = 0.05f;

	shader.GetActiveUniform();
	// window loop for rendering
	while (!glfwWindowShouldClose(window)) {
		renderer.Clear();

		shader.Bind();
		shader.SetUniform4f("u_Color", r1, 0.3f, 0.8f, 1.0f);

		renderer.Draw(va, ib, shader);

		if (r1 > 1.0f)
			increment = -0.05f;
		else if (r1 < 0.0f)
			increment = 0.05f;

		r1 += increment;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}