#include "core/Mouse.h"

Mouse* Mouse::sMouse = nullptr;
float Mouse::sX = 0.0f;
float Mouse::sY = 0.0f;
int Mouse::sButton = 0;
GLFWcursor* Mouse::sCursor = nullptr;
bool Mouse::sInitialized = false;

bool Mouse::sButtons[GLFW_MOUSE_BUTTON_LAST + 1] = {};
bool Mouse::sButtonsPressedThisFrame[GLFW_MOUSE_BUTTON_LAST + 1] = {};

Mouse::Mouse(const Window& window, int shape) {
	sCursor = glfwCreateStandardCursor(shape);
	glfwSetCursor(window.GetWindow(), sCursor);

	// set callback for mouse position and buttons status
	glfwSetCursorPosCallback(window.GetWindow(), CursorPositionCallback);
	glfwSetMouseButtonCallback(window.GetWindow(), MouseButtonCallback);
}

Mouse::~Mouse() {
	glfwDestroyCursor(sCursor);
	delete sMouse;
}

bool Mouse::Init(const Window& window, int shape) {
	if (!sInitialized) {
		sMouse = new Mouse(window, shape);
		sInitialized = true;
		return true;
	} else
		return false;
}

Mouse* Mouse::Get() {
	if (sInitialized)
		return sMouse;
	return nullptr;
}

bool Mouse::IsButtonPressedImpl(const Window& win, int button) {
	int state = glfwGetMouseButton(win.GetWindow(), button);
	return state == GLFW_PRESS ? true : false;
}

bool Mouse::IsButtonReleasedImpl(const Window& win, int button) {
	int state = glfwGetMouseButton(win.GetWindow(), button);
	return state == GLFW_RELEASE ? true : false;
}

bool Mouse::WasButtonPressedImpl(const Window& win, int button) {
	if (sButtonsPressedThisFrame[button]) {
		sButtonsPressedThisFrame[button] = false;
		return true;
	}

	return false;
}

bool Mouse::IsDraggingImpl(int button) {
	return false;
}

void Mouse::CursorPositionCallback(GLFWwindow* win, double x, double y) {
	sX = static_cast<float>(x);
	sY = static_cast<float>(y);
}

void Mouse::MouseButtonCallback(GLFWwindow* win, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		sButtons[button] = true;
		sButtonsPressedThisFrame[button] = true;
	} else if (action == GLFW_RELEASE) {
		sButtons[button] = false;
		sButtonsPressedThisFrame[button] = false;
	}
}
