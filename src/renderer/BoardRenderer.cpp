#include "renderer/BoardRenderer.h"

#include "game/InitialPosition.h"
#include "renderer/Renderer.h"

BoardRenderer::BoardRenderer(const std::shared_ptr<Window>& window)
    : mWindow(window),
      mPositions{
          0.0f, 0.0f, 0.0f, 0.0f,  // bottom-left corner
          1.0f, 0.0f, 1.0f, 0.0f,  // bottom-right corner
          1.0f, 1.0f, 1.0f, 1.0f,  // top-right corner
          0.0f, 1.0f, 0.0f, 1.0f   // top-left corner
      },
      mIndices{0, 1, 2, 2, 3, 0},
      mVb(mPositions, 4 * 4 * sizeof(float)),
      mIb(mIndices, 6),
      mVa(),
      mLayout(),
      mSquareShader("resources/shaders/Square.shader"),
      mPieceShader("resources/shaders/Piece.shader") {
	// specify vertex buffer layout
	mLayout.Push<float>(2);  // 2 floats for vertex coordinates
	mLayout.Push<float>(2);  // 2 floats for texture coordinates
	mVa.AddBuffer(mVb, mLayout);

	mSquareShader.Bind();
	mPieceShader.Bind();

	mProj = glm::ortho(0.0f, (float)window->GetFrameBufferWidth(), 0.0f,
	                   (float)window->GetFrameBufferHeight(), -1.0f, 1.0f);
	mView = glm::mat4(1.0f);
	mModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	mMVP = mProj * mView * mModel;

	mSquareSize = static_cast<float>(window->GetFrameBufferHeight() / 8);

	// consider all png files that are used to draw pieces and load textures
	std::filesystem::path pieceTexturesPath = "resources/textures/pieces";
	for (const auto& element : std::filesystem::directory_iterator(pieceTexturesPath)) {
		// load texture and store all textures as ['piece-name', Texture] key-data pairs.
		// For example ['white-queen', Texture], ['black-bishop', Texture]
		std::shared_ptr<Texture> texture = std::make_shared<Texture>(element.path().string());
		if (texture) {
			std::string pieceName = element.path().stem().string();
			mPieceTextures[pieceName] = texture;
		} else
			std::cout << "Failed to load texture " << element << std::endl;
	}
}

void BoardRenderer::Draw() {
	// draw squares
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			DrawSquare(col, row);
		}
	}
	// draw pieces in initial position
	for (const auto& element : initialPosition) {
		auto [square, piece] = element;
		DrawPiece(piece, square);
	}
}

void BoardRenderer::DrawPiece(const std::string& pieceName, const std::string& square) {
	// retrieve mathematical coordinates and set the MVP matrix
	auto [col, row] = GetCoordinatesFromSquareName(square);
	mModel = glm::translate(glm::mat4(1.0f), glm::vec3(col * mSquareSize, row * mSquareSize, 0.0f));
	mModel = glm::scale(mModel, glm::vec3(mSquareSize, mSquareSize, 1.0f));
	mMVP = mProj * mView * mModel;
	mPieceShader.Bind();

	// get the correct texture considering the given pieceName
	mPieceTextures.at(pieceName)->Bind();
	// texture slot must match with one specified when binding the texture
	mPieceShader.SetUniform1i("u_Texture", 0);
	mPieceShader.SetUniformMat4f("u_MVP", mMVP);
	Renderer::Draw(mVa, mIb, mPieceShader);
}

void BoardRenderer::DrawSquare(int row, int col) {
	mModel = glm::translate(glm::mat4(1.0f), glm::vec3(col * mSquareSize, row * mSquareSize, 0.0f));
	mModel = glm::scale(mModel, glm::vec3(mSquareSize, mSquareSize, 1.0f));
	mMVP = mProj * mView * mModel;
	mSquareShader.Bind();

	bool coordsEven = (row % 2) && (col % 2);
	bool coordsOdd = !(row % 2) && !(col % 2);
	if (coordsEven || coordsOdd)
		mSquareShader.SetUniform4f("u_Color", 0.28f, 0.62f, 0.17f, 1.0f);
	else
		mSquareShader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	mSquareShader.SetUniformMat4f("u_MVP", mMVP);
	Renderer::Draw(mVa, mIb, mSquareShader);
}

std::pair<int, int> BoardRenderer::GetCoordinatesFromSquareName(const std::string& name) const {
	// Offset col and row so that 'a1' square is (0,0)
	int row = std::atoi(&name[1]) - 1;  // Row 1 of chessboard is row 0
	int col = name[0] - 'a';            // Column 'a' is column 0
	return std::pair<int, int>(col, row);
}

std::string BoardRenderer::GetSquareNameFromCoordinates(int row, int col) const {
	char squareName[2];
	squareName[0] = col + 97;
	squareName[1] = row + 1;
	return std::string(squareName);
}
