#pragma once

#include <GL/glew.h>

#include <string>

class Texture {
   public:
	Texture(const std::string& path);
	Texture(const Texture&) = delete;
	~Texture();

	void Bind(uint32_t slot = 0) const;
	void Unbind() const;

	Texture& operator=(const Texture&) = delete;

	GLsizei GetWidth() const;
	GLsizei GetHeight() const;

   private:
	GLuint mRendererID;
	std::string mFilePath;
	u_char* mLocalBuffer;  // buffer to store the image
	GLsizei mWidth, mHeight, mBPP;
};
