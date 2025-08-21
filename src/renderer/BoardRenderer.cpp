#include "renderer/BoardRenderer.h"

constexpr float size = 1.0f;

BoardRenderer::BoardRenderer(const std::shared_ptr<Window>& window, const std::shared_ptr<Mouse>& mouse)
    : mWindow(window),
      mMouse(mouse),
      mPositions{
          0.0f, 0.0f, 0.0f, 0.0f,  // bottom-left corner
          size, 0.0f, 1.0f, 0.0f,  // bottom-right corner
          size, size, 1.0f, 1.0f,  // top-right corner
          0.0f, size, 0.0f, 1.0f   // top-left corner
      },
      mIndices{0, 1, 2, 2, 3, 0},
      mVb(mPositions, 4 * 4 * sizeof(float)),
      mIb(mIndices, 6),
      mVa(),
      mLayout(),
      mShader("resources/shaders/Square.shader"),
      mTexture("resources/textures/LightKnight.png") {
	// specify vertex buffer layout
	mLayout.Push<float>(2);  // 2 floats for vertex coordinates
	mLayout.Push<float>(2);  // 2 floats for texture coordinates
	mVa.AddBuffer(mVb, mLayout);

	mShader.Bind();
	mTexture.Bind();
	//  texture slot must match with one specified when binding the texture
	mShader.SetUniform1i("u_Texture", 0);

	mProj = glm::ortho(0.0f, (float)window->GetFBWidth(), 0.0f, (float)window->GetFBHeight(), -1.0f, 1.0f);
	mView = glm::mat4(1.0f);
	mModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	mMVP = mProj * mView * mModel;

	mSquareSize = static_cast<float>(window->GetFBHeight() / 8);
}

BoardRenderer::~BoardRenderer() {
}

void BoardRenderer::DrawSquare(Renderer& renderer, int row, int col) {
	mModel = glm::translate(glm::mat4(1.0f), glm::vec3(col * mSquareSize, row * mSquareSize, 0.0f));
	mModel = glm::scale(mModel, glm::vec3(mSquareSize, mSquareSize, 1.0f));
	mMVP = mProj * mView * mModel;
	mShader.Bind();

	bool coordsEven = (row % 2) && (col % 2);
	bool coordsOdd = !(row % 2) && !(col % 2);
	if (coordsEven || coordsOdd)
		mShader.SetUniform4f("u_Color", 0.28f, 0.62f, 0.17f, 1.0f);
	else
		mShader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	mShader.SetUniformMat4f("u_MVP", mMVP);
	renderer.Draw(mVa, mIb, mShader);
}

void BoardRenderer::Draw(Renderer& renderer) {
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			DrawSquare(renderer, col, row);
		}
	}
}