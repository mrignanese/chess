#include <iostream>
#include <memory>

#include "GLpch.h"
#include "core/Mouse.h"
#include "core/Window.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "renderer/BoardRenderer.h"
#include "renderer/Renderer.h"

int main() {
	if (!glfwInit())
		return -1;

	std::shared_ptr<Window> window = std::make_shared<Window>(1920, 1200, "Chess", nullptr, nullptr);
	std::shared_ptr<Mouse> mouse = std::make_shared<Mouse>(window, GLFW_ARROW_CURSOR);

	if (!window->IsOpen()) {
		std::cout << "Failed to open the window!" << std::endl;
		return -1;
	}

	Renderer::EnableBlending();

	BoardRenderer board(window, mouse);

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = "../build/imgui.ini";

	// window loop for rendering
	while (!window->ShouldClose()) {
		Renderer::Clear();

		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		board.Draw();

		/*
		{
		    ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, (float)window->GetWidth());
		    ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, (float)window->GetWidth());
		    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
		    ImGui::GetIO().Framerate);
		}
		*/

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