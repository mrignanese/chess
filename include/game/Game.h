#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "game/pieces/Piece.h"
#include "renderer/BoardRenderer.h"

class Window;
using Board = std::unordered_map<std::string, std::shared_ptr<Piece>>;

class Game {
   public:
	Game();
	Game(const Game&) = delete;
	~Game();

	void Init();
	void Run();
	void Terminate();

	bool IsMoveLegal();
	void UpdateBoardPosition();
	void DrawBoard();

	const Window& GetWindow() const;
	const Board& GetBoard() const;

	Game& operator=(const Game&) = delete;

   private:
	void LoadInitialPosition();

	bool mIsRunning;
	std::unique_ptr<Window> mWindow;
	std::unique_ptr<BoardRenderer> mBoardRenderer;
	Board mBoard;
};
