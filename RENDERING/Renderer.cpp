#include "Renderer.h"
#include "glad/glad.h" 
#include "../src/Debug.h"


void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.bind();

    va.bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.Get_Count(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ));
}