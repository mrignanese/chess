#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

#include "core/Mouse.h"
#include "core/Window.h"
#include "game//utilities/ChessCoordinates.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "renderer/BoardRenderer.h"
#include "renderer/Renderer.h"

int main() {
	if (!glfwInit())
		return -1;

	Window window(1920, 1200, "Chess", nullptr, nullptr);
	Mouse::Init(window, GLFW_ARROW_CURSOR);

	if (!window.IsOpen()) {
		std::cout << "Failed to open the window!" << std::endl;
		return -1;
	}

	Renderer::EnableBlending();

	BoardRenderer board(window);

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = "../build/imgui.ini";

	// window loop for rendering
	while (!window.ShouldClose()) {
		Renderer::Clear();

		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		board.Draw();

		if (Mouse::IsButtonPressed(window, GLFW_MOUSE_BUTTON_LEFT)) {
			float size = window.GetFrameBufferHeight() / 8;
			std::cout << "Left button pressed\n";
			float x = Mouse::GetX();
			float y = Mouse::GetY();
			std::cout << "x = " << x << " " << "y = " << y << std::endl;

			int row = y / size;
			int col = x / size;
			std::cout << "row = " << row << " " << "col = " << col << std::endl;
			
			std::string square = GetSquareNameFromCoordinates(row, col);
			//char squareName[2];
			//squareName[0] = col + 97;  // 97 is ASCII code for 'a' (first column)
			//squareName[1] = row + 1;
			//std::string square(squareName);
			//std::cout << squareName[0] << " " << squareName[1] << std::endl;
			std::cout << "Mouse is in square " << square << std::endl;
		}
		/*
		{
		    ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, (float)window->GetWidth());
		    ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, (float)window->GetWidth());
		    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f /
		ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}
		*/

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.SwapBuffers();
		window.PollEvents();
	}

	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	return 0;
}