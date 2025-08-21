#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <memory>

#include "GL_pch.h"
#include "core/Mouse.h"
#include "core/Window.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "renderer/BoardRenderer.h"
//#include "renderer/IndexBuffer.h"
#include "renderer/Renderer.h"
//#include "renderer/Shader.h"
//#include "renderer/Texture.h"
//#include "renderer/VertexArray.h"
//#include "renderer/VertexBuffer.h"
//#include "renderer/VertexBufferLayout.h"

int main() {
	if (!glfwInit())
		return -1;

	std::shared_ptr<Window> window = std::make_shared<Window>(1920, 1200, "Chess", nullptr, nullptr);
	std::shared_ptr<Mouse> mouse = std::make_shared<Mouse>(window, GLFW_ARROW_CURSOR);

	if (!window->IsOpen()) {
		std::cout << "Failed to open the window!" << std::endl;
		return -1;
	}

	std::cout << (float)(window->GetFBHeight() / 8) << std::endl;

	Renderer renderer;
	renderer.EnableBlending();

	BoardRenderer board(window, mouse);

	//float positions[] = {
	//    -50.0f, -50.0f, 0.0f, 0.0f,  // bottom-left
	//    50.0f,  -50.0f, 1.0f, 0.0f,  // bottom-right
	//    50.0f,  50.0f,  1.0f, 1.0f,  // top-right
	//    -50.0f, 50.0f,  0.0f, 1.0f   // top-left
	//};

	//unsigned int indices[6] = {0, 1, 2, 2, 3, 0};

	//VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	//IndexBuffer ib(indices, 6);
	//VertexArray va;
	//VertexBufferLayout layout;

	//layout.Push<float>(2);  // vertex coordinates
	//layout.Push<float>(2);  // texture coordinates
	//va.AddBuffer(vb, layout);

	// projection matrix to adjust for 4:3 aspect ration
	//glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
	//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	// src/renderer/res/shader/Basic.shader
	//Shader shader("/home/michele/Desktop/chess/resources/shader/Square.shader");
	//shader.Bind();
	//shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

	//Texture texture("src/renderer/res/textures/LightKnight.png");
	//texture.Bind();
	//  texture slot must match with one specified when binding the texture
	//shader.SetUniform1i("u_Texture", 0);

	//vb.Unbind();
	//ib.Unbind();
	//va.Unbind();
	//shader.Unbind();

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = "../build/imgui.ini";

	glm::vec3 translationA = glm::vec3(200, 200, 0);
	glm::vec3 translationB = glm::vec3(400, 200, 0);

	float r = 0.0f;
	float increment = 0.05f;

	// shader.GetActiveUniform();

	// GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
	// if (!cursor)
	//	std::cout << "Failed to initialized the cursor" << std::endl;

	// double mouseX, mouseY;
	// double currentX, currentY;

	// window loop for rendering
	while (!window->ShouldClose()) {
		renderer.Clear();

		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		// currentX = mouseX;
		// currentY = mouseY;

		// glfwGetCursorPos(window->GetWindow(), &mouseX, &mouseY);

		// int state = glfwGetMouseButton(window->GetWindow(), GLFW_MOUSE_BUTTON_LEFT);
		// if (state == GLFW_PRESS) {
		//	// std::cout << "Pressed left button" << std::endl;
		//	translationA.x = mouseX;
		//	translationA.y = mouseY;
		// }

		// if ((currentX != mouseX) || (currentY != mouseY)) {
		//	std::cout << mouseX << ", " << mouseY << std::endl;
		// }

		//shader.Bind();

		//{
		//	glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
		//	glm::mat4 mvp = proj * view * model;
		//	// shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
		//	shader.SetUniformMat4f("u_MVP", mvp);
		//	renderer.Draw(va, ib, shader);
		//}

		//{
		//	glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
		//	glm::mat4 mvp = proj * view * model;
		//	shader.SetUniformMat4f("u_MVP", mvp);
		//	renderer.Draw(va, ib, shader);
		//}

		board.Draw(renderer);

		if (r > 1.0f)
			increment = -0.05f;
		else if (r < 0.0f)
			increment = 0.05f;

		r += increment;

		{
			ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, (float)window->GetWidth());
			ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, (float)window->GetWidth());
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
			            ImGui::GetIO().Framerate);
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window->SwapBuffers();
		window->PollEvents();
	}

	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	return 0;
}