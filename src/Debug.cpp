#include "Debug.h"
#include "glad/glad.h" 
#include "iostream"

void GLClearError()
{
    while (glGetError() != 0);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OPENGL ERROR] (" << error << ") " << function << " --> " << file << " at line --> " << line << std::endl;
        return false;
    }
    return true;
}