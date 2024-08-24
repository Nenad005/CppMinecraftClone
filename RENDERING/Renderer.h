#pragma once
#include "../OPEN-GL/VertexArray.h"
#include "../OPEN-GL/IndexBuffer.h"
#include "../OPEN-GL/Shader.h"

class Renderer
{
public:
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void clear();
};