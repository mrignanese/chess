#include "core/Mouse.h"

Mouse::Mouse(const std::shared_ptr<Window>& window, int shape) : mWindow(window) {
	mCursor = glfwCreateStandardCursor(shape);
	mPos.x = 0.0;
	mPos.y = 0.0;
}

Mouse::~Mouse() {
	glfwDestroyCursor(mCursor);
}

bool Mouse::IsButtonPressed(int button) const {
	return glfwGetMouseButton(mWindow->GetWindow(), button);
}

bool Mouse::IsInsideRegion(float x, float y, float width, float height) const {
	return false;
}

bool Mouse::IsDragging(int button) const {
	return false;
}

glm::vec2& Mouse::GetPosition() {
	glfwGetCursorPos(mWindow->GetWindow(), reinterpret_cast<double*>(&mPos.x),
	                 reinterpret_cast<double*>(&mPos.y));
	return mPos;
}

GLFWcursor* Mouse::GetCursor() const {
	return mCursor;
}