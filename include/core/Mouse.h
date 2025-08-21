#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "GL_pch.h"
#include "core/Window.h"

class Mouse {
   private:
	glm::vec2 mPos;
	GLFWcursor* mCursor;
	std::shared_ptr<Window> mWindow;

   public:
	Mouse(const std::shared_ptr<Window>& window, int shape);
	Mouse(const Mouse&) = delete;
	~Mouse();

	bool IsButtonPressed(int button) const;
	bool IsInsideRegion(float x, float y, float width, float height) const;
	bool IsDragging(int button) const;

	Mouse& operator=(const Mouse&) = delete;

	glm::vec2& GetPosition();
	GLFWcursor* GetCursor() const;
};