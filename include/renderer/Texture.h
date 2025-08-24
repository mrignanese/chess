#pragma once

#include <string>

#include "GLpch.h"

class Texture {
   public:
	Texture(const std::string& path);
	Texture(const Texture&) = delete;
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	Texture& operator=(const Texture&) = delete;

	GLsizei GetWidth() const;
	GLsizei GetHeight() const;

   private:
	GLuint mRendererID;
	std::string mFilePath;
	unsigned char* mLocalBuffer;  // buffer to store the image
	GLsizei mWidth, mHeight, mBPP;
};