#pragma once
#include "vector"
#include <iostream>
#include "glad/glad.h" 
#include "../src/Debug.h"	
#include <type_traits>

struct VertexBufferElement 
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int get_size_of_type(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT :         return 4;
			case GL_UNSIGNED_INT :  return 4;
			case GL_UNSIGNED_BYTE : return 1;
		}
		ASSERT(false);
		return 0;
	}
};


class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		: m_Stride(0) {}

	template<typename T>
	void Push(unsigned int count)
	{
		//static_assert(false);
		unsigned int type;
		if (std::is_same<T, float>::value) type = GL_FLOAT;
		else if (std::is_same<T, unsigned int>::value) type = GL_FLOAT;
		else if (std::is_same<T, unsigned char>::value) type = GL_FLOAT;
		else std::cout << "GRESKA LOS TIP BLA BLA BLA" << std::endl;

		m_Elements.push_back({ type, count, GL_FALSE });
		m_Stride += VertexBufferElement::get_size_of_type(type) * count;
	}

	// template<>
	// void Push<float>(unsigned int count)
	// {
	// 	m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
	// 	m_Stride += VertexBufferElement::get_size_of_type(GL_FLOAT) * count;
	// }

	// template<>
	// void Push<unsigned int>(unsigned int count)
	// {
	// 	m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
	// 	m_Stride += VertexBufferElement::get_size_of_type(GL_UNSIGNED_INT) * count;
	// }

	// template<>
	// void Push<unsigned char>(unsigned int count)
	// {
	// 	m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
	// 	m_Stride += VertexBufferElement::get_size_of_type(GL_UNSIGNED_BYTE) * count;
	// }

	inline const std::vector<VertexBufferElement> get_elements() const { return m_Elements; };
	inline unsigned int get_stride() const { return m_Stride; };
};

