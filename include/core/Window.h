#pragma once

#include <GLFW/glfw3.h>

class Window {
   public:
	Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	Window(const Window&) = delete;
	~Window();

	bool IsOpen() const;
	int ShouldClose() const;
	void SwapBuffers() const;
	void PollEvents() const;

	Window& operator=(const Window&) = delete;

	int GetWidth() const;
	int GetHeight() const;
	GLsizei GetFrameBufferWidth() const;
	GLsizei GetFrameBufferHeight() const;
	GLFWwindow* GetWindow() const;

   private:
	int mWidth, mHeight;
	GLsizei mFBWidth, mFBHeight;
	GLFWwindow* mWindow;

	static void FramebufferSizeCallback(GLFWwindow* win, int width, int height);
};
