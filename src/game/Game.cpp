#include "game/Game.h"

#include <exception>

#include "core/Window.h"
#include "game/InitialPosition.h"
#include "game/utilities/ChessCoordinates.h"
#include "game/utilities/ChessLog.h"

Game::Game() {
	// initialize the Window only
	mWindow = std::make_unique<Window>(1920, 1200, "Chess", nullptr, nullptr);
	mIsRunning = true;
	if (!mWindow->IsOpen())
		std::cerr << "Failed to open the window!" << std::endl;

	Mouse::Init(*mWindow, GLFW_ARROW_CURSOR);
}

Game::~Game() {
}

void Game::Init() {
	float frameBufferWidth = static_cast<float>(mWindow->GetFrameBufferWidth());
	float frameBufferHeight = static_cast<float>(mWindow->GetFrameBufferHeight());
	mBoardRenderer = std::make_unique<BoardRenderer>(frameBufferWidth, frameBufferHeight);

	LoadInitialPosition();
}

void Game::Run() {
	if (Mouse::WasButtonPressed(*mWindow, GLFW_MOUSE_BUTTON_LEFT)) {
		float squareSize = mWindow->GetFrameBufferHeight() / 8;
		std::string selectedSquare = GetSquareNameFromMousePosition(squareSize);
		CHESS_LOG("Mouse is in square", selectedSquare);

		auto selectedPiece = mBoard.find(selectedSquare);
		if (selectedPiece != mBoard.end()) {
			CHESS_LOG("Selected piece with mouse", selectedPiece->second->GetName());
		} else
			CHESS_LOG("Selected square has no piece", "");
	}

	DrawBoard();
}

void Game::Terminate() {
}

void Game::DrawBoard() {
	if (mBoardRenderer)
		mBoardRenderer->Draw(mBoard);
}

const Window& Game::GetWindow() const {
	return *mWindow;
}

const Board& Game::GetBoard() const {
	return mBoard;
}

void Game::LoadInitialPosition() {
	// TODO: initialPosition must be loaded as json file,
	// to be able to load easily also a chess 960 position
	for (const auto& element : initialPosition) {
		const auto& [square, piece] = element;
		mBoard[square] = std::make_shared<Piece>(piece);
	}
}
