#pragma once

#include "GLpch.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"



class Renderer {
   public:
	Renderer(const Renderer&) = delete;
	~Renderer() = default;

	static Renderer& Get();

	inline static void Clear() {
		return Get().ClearImpl();
	}

	inline static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) {
		return Get().DrawImpl(va, ib, shader);
	}

	static void EnableBlending() {
		return Get().EnableBlendingImpl();
	}

	Renderer& operator=(const Renderer&) = delete;

   private:
	Renderer();

	void ClearImpl();
	void DrawImpl(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	void EnableBlendingImpl();
};
