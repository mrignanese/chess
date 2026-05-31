#pragma once

#include <GLFW/glfw3.h>

#include "core/Window.h"

class Mouse {
   public:
	Mouse(const Mouse&) = delete;
	~Mouse();

	static bool Init(const Window& window, int shape);
	static Mouse* Get();

	inline static bool IsButtonPressed(const Window& win, int button) {
		return Get()->IsButtonPressedImpl(win, button);
	};

	inline static bool IsButtonReleased(const Window& win, int button) {
		return Get()->IsButtonReleasedImpl(win, button);
	}

	inline static bool WasButtonPressed(const Window& win, int button) {
		return Get()->WasButtonPressedImpl(win, button);
	}

	inline static bool IsDragging(int button) {
		return Get()->IsDraggingImpl(button);
	};

	Mouse& operator=(const Mouse&) = delete;

	static inline float GetX() {
		return sX;
	}

	static inline float GetY() {
		return sY;
	}

	static inline GLFWcursor* GetCursor() {
		return sCursor;
	}

   private:
	Mouse(const Window& window, int shape);

	static Mouse* sMouse;
	static float sX, sY;
	static int sButton;
	static GLFWcursor* sCursor;
	static bool sInitialized;

	// bool arrays to keep track of button states
	static bool sButtons[GLFW_MOUSE_BUTTON_LAST + 1];
	static bool sButtonsPressedThisFrame[GLFW_MOUSE_BUTTON_LAST + 1];

	// implementations of static methods
	bool IsButtonPressedImpl(const Window& win, int button);
	bool IsButtonReleasedImpl(const Window& win, int button);
	bool WasButtonPressedImpl(const Window& win, int button);
	bool IsDraggingImpl(int button);

	// callbacks
	static void CursorPositionCallback(GLFWwindow* win, double x, double y);
	static void MouseButtonCallback(GLFWwindow* win, int button, int action, int mods);
};
