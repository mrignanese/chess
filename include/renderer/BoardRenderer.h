#pragma once

#include <GL/glew.h>

#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "core/Mouse.h"
#include "core/Window.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/VertexBufferLayout.h"

class BoardRenderer {
   public:
	BoardRenderer(const Window& window);
	BoardRenderer(const BoardRenderer&) = delete;
	~BoardRenderer() = default;

	void Draw();

	BoardRenderer& operator=(const BoardRenderer&) = delete;

   private:
	void DrawSquare(int row, int col);
	void DrawPiece(const std::string& name, const std::string& square);
	void DestroyPiece(const std::string& name, const std::string& square);
	std::pair<int, int> GetCoordinatesFromSquareName(const std::string& name) const;
	std::string GetSquareNameFromCoordinates(int row, int col) const;

   private:
	enum class SquareColor { DARK, LIGHT };

	float mPositions[16];	// array containing vertex 2D coordinates and texture 2D coordinates
	uint32_t mIndices[6];	// indices to access mPositions elements
	VertexBuffer mVb;
	IndexBuffer mIb;
	VertexArray mVa;
	VertexBufferLayout mLayout;
	Shader mSquareShader, mPieceShader;
	glm::mat4 mProj, mView, mModel, mMVP;
	float mSquareSize;
	std::unordered_map<std::string, std::shared_ptr<Texture>> mPieceTextures;
};
