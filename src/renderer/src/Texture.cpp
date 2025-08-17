#include "Texture.h"

#include "stb_image/stb_image.h"

Texture::Texture(const std::string& path)
    : mRendererID(0), mFilePath(path), mLocalBuffer(nullptr), mWidth(0), mHeight(0), mBPP(0) {
	// enable this flag because png files are loaded considering the origin
	// as the top left corner, while OpenGL loads textures starting from the bottom left one
	stbi_set_flip_vertically_on_load(1);
	mLocalBuffer = stbi_load(path.c_str(), &mWidth, &mHeight, &mBPP, 4);

	GLCall(glGenTextures(1, &mRendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, mRendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	// send png buffer to OpenGL (graphics card)
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
	                    mLocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (mLocalBuffer)
		stbi_image_free(mLocalBuffer);
}

Texture::~Texture() {
	GLCall(glDeleteTextures(1, &mRendererID));
}

void Texture::Bind(unsigned int slot) const {
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, mRendererID));
}

void Texture::Unbind() const {
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

int Texture::GetWidth() const {
	return mWidth;
}

int Texture::GetHeight() const {
	return mHeight;
}
