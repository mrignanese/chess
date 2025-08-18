#pragma once

#include <GLFW/glfw3.h>

class Window {
   private:
	int mWidth, mHeight;
	GLFWwindow* mWindow;

   public:
	Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr,
	       GLFWwindow* share = nullptr);
	Window(const Window&) = delete;
	~Window();

	bool IsOpen() const;
	int ShouldClose() const;
	void SwapBuffers() const;

	Window& operator=(const Window&) = delete;

	int GetWidth() const;
	int GetHeight() const;
	GLFWwindow* GetWindow() const;
};