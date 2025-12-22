#pragma once

#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "GLpch.h"
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
	enum class SquareColor { DARK, LIGHT };

	std::shared_ptr<Window> mWindow;
	float mPositions[16];      // array containing vertex 2D coordinates and texture 2D coordinates
	unsigned int mIndices[6];  // indices to access mPositions elements

	VertexBuffer mVb;
	IndexBuffer mIb;
	VertexArray mVa;
	VertexBufferLayout mLayout;
	Shader mSquareShader, mPieceShader;
	glm::mat4 mProj, mView, mModel, mMVP;
	float mSquareSize;
	std::unordered_map<std::string, std::shared_ptr<Texture>> mPieceTextures;

   public:
	BoardRenderer(const std::shared_ptr<Window>& window);
	BoardRenderer(const BoardRenderer&) = delete;
	~BoardRenderer() = default;

	BoardRenderer& operator=(const BoardRenderer&) = delete;

	void Draw();
	void DrawPiece(const std::string& pieceName, const std::string& square);
	void DestroyPiece(const std::string& name, const std::string& square);

   private:
	void DrawSquare(int row, int col);
	std::pair<int, int> GetCoordinatesFromSquareName(const std::string& name) const;
	std::string GetSquareNameFromCoordinates(int row, int col) const;
};