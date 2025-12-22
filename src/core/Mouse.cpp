#include "core/Mouse.h"

Mouse* Mouse::sMouse = nullptr;
std::pair<float, float> Mouse::sPosition = {};
GLFWcursor* Mouse::sCursor = nullptr;
std::shared_ptr<Window> Mouse::sWindow = nullptr;
bool Mouse::sInitialized = false;

Mouse::Mouse(const std::shared_ptr<Window>& window, int shape) {
	sPosition = std::make_pair(0.0f, 0.0f);
	sCursor = glfwCreateStandardCursor(shape);
	sWindow = window;
}

Mouse::~Mouse() {
	glfwDestroyCursor(sCursor);
	delete sMouse;
}

bool Mouse::Init(const std::shared_ptr<Window>& window, int shape) {
  if(!sInitialized){
    sMouse = new Mouse(window, shape); 
    sInitialized = true;
    return true;
  }
  else 
    return false;
}

Mouse* Mouse::Get() {
	if(sInitialized)
		return sMouse;
	return nullptr;
}

bool Mouse::IsButtonPressedImpl(int button) {
	return glfwGetMouseButton(sWindow->GetWindow(), button);
}

bool Mouse::IsInsideRegionImpl(float x, float y, float width, float height) {
	return false;
}

bool Mouse::IsDraggingImpl(int button) {
	return false;
}