#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "core/Window.h"
#include "game/Game.h"
#include "renderer/Renderer.h"

namespace Application {

int Run() {
	// check if GLFW is initialized properly
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW!" << std::endl;
		return -1;
	}

	Game game;

	// initialize the renderer and the game
	Renderer::Init();
	game.Init();
	
	const Window& window = game.GetWindow();
	
	// window loop
	while (!window.ShouldClose()) {
		Renderer::Clear();

		game.Run();

		window.PollEvents();
		window.SwapBuffers();
	}

	glfwTerminate();
	return 0;
}

}
