#include "core/Window.h"

Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
    : mWidth(width), mHeight(height), mFbWidth(0), mFbHeight(0), mWindow(nullptr) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(width, height, title, monitor, share);
	if (!mWindow) {
		glfwTerminate();
	}

	// make the window's context current
	glfwMakeContextCurrent(mWindow);
	glfwGetFramebufferSize(mWindow, &mFbWidth, &mFbHeight);
	glViewport(0, 0, mFbWidth, mFbHeight);

	//glfwSetFramebufferSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
	//	Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
	//	if (win) {
	//		win->mFbWidth = width;
	//		win->mFbHeight = height;
	//		glViewport(0, 0, width, height);
	//	}
	//});
	//glfwSetWindowUserPointer(mWindow, this);
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

void Window::OnResize() {
	glfwGetFramebufferSize(mWindow, &mFbWidth, &mFbHeight);
	glViewport(0, 0, mFbWidth, mFbHeight);
}

int Window::GetWidth() const {
	return mWidth;
}

int Window::GetHeight() const {
	return mHeight;
}

int Window::GetFBWidth() const {
	return mFbWidth;
}

int Window::GetFBHeight() const {
	return mFbHeight;
}

GLFWwindow* Window::GetWindow() const {
	return mWindow;
}