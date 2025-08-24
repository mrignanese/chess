#pragma once

#include "GLpch.h"

class Window {
   private:
	int mWidth, mHeight;
	int mFbWidth, mFbHeight;
	GLFWwindow* mWindow;

   public:
	Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr,
	       GLFWwindow* share = nullptr);
	Window(const Window&) = delete;
	~Window();

	bool IsOpen() const;
	int ShouldClose() const;
	void SwapBuffers() const;
	void PollEvents() const;
	void OnResize();

	Window& operator=(const Window&) = delete;

	int GetWidth() const;
	int GetHeight() const;
	int GetFBWidth() const;
	int GetFBHeight() const;
	GLFWwindow* GetWindow() const;
};