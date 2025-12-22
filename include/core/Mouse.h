#pragma once

#include <memory>

#include "GLpch.h"
#include "core/Window.h"

class Mouse {
   public:
	Mouse(const Mouse&) = delete;
	~Mouse();

	static bool Init(const std::shared_ptr<Window>& window, int shape);
	static Mouse* Get();

	static bool IsButtonPressed(int button) {
		return Get()->IsButtonPressed(button);
	};

	static bool IsInsideRegion(float x, float y, float width, float height) {
		return Get()->IsInsideRegion(x, y, width, height);
	};

	static bool IsDragging(int button) {
		return Get()->IsDragging(button);
	};

	Mouse& operator=(const Mouse&) = delete;

	static inline const std::pair<float, float>& GetPosition() {
		return sPosition;
	}
	static inline GLFWcursor* GetCursor() {
		return sCursor;
	}

   private:
    static Mouse* sMouse;
	static std::pair<float, float> sPosition;
	static GLFWcursor* sCursor;
	static std::shared_ptr<Window> sWindow;
	static bool sInitialized;

	Mouse(const std::shared_ptr<Window>& window, int shape);

	// implementations of static methods
	bool IsButtonPressedImpl(int button);
	bool IsInsideRegionImpl(float x, float y, float width, float height);
	bool IsDraggingImpl(int button);
};