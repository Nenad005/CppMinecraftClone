#pragma once
#include "glad/glad.h" 

class IndexBuffer
{
private :
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int Get_Count() const { return m_Count; }
};
