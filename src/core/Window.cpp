#include "core/Window.h"

#include <iostream>

Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) :
    mWidth(width), mHeight(height), mFBWidth(0), mFBHeight(0), mWindow(nullptr) {
	// set OpenGL version to 3.3 and use core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(width, height, title, monitor, share);
	if (!mWindow) {
		std::cout << "Failed to create the window! Terminating GLFW!" << std::endl;
		glfwTerminate();
	}

	// make the window's context current
	glfwMakeContextCurrent(mWindow);
	// get actual pixel size of the framebuffer attached to the window.
	// Frame buffer width and height are not equal to window width and height
	glfwGetFramebufferSize(mWindow, &mFBWidth, &mFBHeight);
	glViewport(0, 0, mFBWidth, mFBHeight);

	glfwSetFramebufferSizeCallback(mWindow, FramebufferSizeCallback);
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

void Window::PollEvents() const {
	return glfwPollEvents();
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

GLsizei Window::GetFrameBufferWidth() const {
	return mFBWidth;
}

GLsizei Window::GetFrameBufferHeight() const {
	return mFBHeight;
}

GLFWwindow* Window::GetWindow() const {
	return mWindow;
}

void Window::FramebufferSizeCallback(GLFWwindow* win, int width, int height) {
	glViewport(0, 0, width, height);
}
