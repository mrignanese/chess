#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "core/Mouse.h"
#include "core/Window.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/VertexBufferLayout.h"

class BoardRenderer {
   private:
	std::shared_ptr<Window> mWindow;
	std::shared_ptr<Mouse> mMouse;
	float mPositions[16];       // array containing vertex 2D coordinates and texture 2D coordinates
    unsigned int mIndices[6];   // indices to access mPositions elements

	VertexBuffer mVb;
	IndexBuffer mIb;
	VertexArray mVa;
	VertexBufferLayout mLayout;
	Shader mShader;
	Texture mTexture;
	glm::mat4 mProj, mView, mModel, mMVP;

	float mSquareSize;

   public:
	BoardRenderer(const std::shared_ptr<Window>& window, const std::shared_ptr<Mouse>& mouse);
	BoardRenderer(const BoardRenderer&) = delete;
	~BoardRenderer();

	BoardRenderer& operator=(const BoardRenderer&) = delete;

	void Draw(Renderer& renderer);

   private:
	void DrawSquare(Renderer& renderer, int row, int col);
};