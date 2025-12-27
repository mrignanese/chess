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

	inline static bool IsInsideRegion(float x, float y, float width, float height) {
		return Get()->IsInsideRegionImpl(x, y, width, height);
	};

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

	// implementations of static methods
	bool IsButtonPressedImpl(const Window& win, int button);
	bool IsInsideRegionImpl(float x, float y, float width, float height);
	bool IsDraggingImpl(int button);

	// callbacks
	static void CursorPositionCallback(GLFWwindow* win, double x, double y);
	static void MouseButtonCallback(GLFWwindow* win, int button, int action, int mods);
};
