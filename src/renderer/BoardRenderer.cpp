#include "renderer/BoardRenderer.h"

#include "game/InitialPosition.h"
#include "game/utilities/ChessCoordinates.h"
#include "renderer/Renderer.h"

BoardRenderer::BoardRenderer(const Window& window) :
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

	mProj = glm::ortho(0.0f, static_cast<float>(window.GetFrameBufferWidth()), 0.0f,
	                   static_cast<float>(window.GetFrameBufferHeight()), -1.0f, 1.0f);
	mView = glm::mat4(1.0f);
	mModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	mMVP = mProj * mView * mModel;

	// compute square size so that the board fits considering window height
	mSquareSize = static_cast<float>(window.GetFrameBufferHeight() / 8);

	// consider all png files that are used to draw pieces and load textures
	std::filesystem::path pieceTexturesPath("resources/textures/pieces");
	for (const auto& element : std::filesystem::directory_iterator(pieceTexturesPath)) {
		// load texture and store all textures as ['color-pieceName', Texture] pairs.
		// For example ['white-queen', Texture], ['black-bishop', Texture], ...
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
		const auto& [square, piece] = element;
		DrawPiece(piece, square);
	}
}

void BoardRenderer::DrawSquare(int row, int col) {
	// translate and scale model matrix (identity) depending on coordinates and square size. This is
	// needed to render the square in the proper position and with the correct size
	mModel = glm::translate(glm::mat4(1.0f), glm::vec3(col * mSquareSize, row * mSquareSize, 0.0f));
	mModel = glm::scale(mModel, glm::vec3(mSquareSize, mSquareSize, 1.0f));
	mMVP = mProj * mView * mModel;

	// bind the shader and set vertex positions using the MVP matrix
	mSquareShader.Bind();
	mSquareShader.SetUniformMat4f("u_MVP", mMVP);

	// check if coordinates are both even or odd to set square color
	bool coordsEven = (row % 2) && (col % 2);
	bool coordsOdd = !(row % 2) && !(col % 2);
	if (coordsEven || coordsOdd)
		mSquareShader.SetUniform4f("u_Color", 0.28f, 0.62f, 0.17f, 1.0f);  // dark square
	else
		mSquareShader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);  // light square

	Renderer::Draw(mVa, mIb, mSquareShader);
}

void BoardRenderer::DrawPiece(const std::string& name, const std::string& square) {
	// retrieve mathematical coordinates and set the MVP matrix
	const auto [col, row] = GetCoordinatesFromSquareName(square);
	mModel = glm::translate(glm::mat4(1.0f), glm::vec3(col * mSquareSize, row * mSquareSize, 0.0f));
	mModel = glm::scale(mModel, glm::vec3(mSquareSize, mSquareSize, 1.0f));
	mMVP = mProj * mView * mModel;

	mPieceShader.Bind();
	mPieceShader.SetUniformMat4f("u_MVP", mMVP);

	// get the correct texture considering the given <name>
	mPieceTextures.at(name)->Bind();
	// texture slot must match with one specified when binding the texture
	mPieceShader.SetUniform1i("u_Texture", 0);

	Renderer::Draw(mVa, mIb, mPieceShader);
}

void BoardRenderer::DestroyPiece(const std::string& name, const std::string& square) {
}
