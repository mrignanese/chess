#include "core/Window.h"

Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
    : mWidth(width), mHeight(height), mWindow(nullptr) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(width, height, title, monitor, share);
	if (!mWindow) {
		glfwTerminate();
	}

	// make the window's context current
	glfwMakeContextCurrent(mWindow);
}

Window::~Window() {
	glfwTerminate();
}

int Window::ShouldClose() const {
	return glfwWindowShouldClose(mWindow);
}

void Window::SwapBuffers() const {
	return glfwSwapBuffers(mWindow);
}

bool Window::IsOpen() const {
	return mWindow != nullptr ? true : false;
}

int Window::GetWidth() const {
	return mWidth;
}

int Window::GetHeight() const {
	return mHeight;
}

GLFWwindow* Window::GetWindow() const {
	return mWindow;
}