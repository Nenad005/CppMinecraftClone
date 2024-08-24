#include "Shader.h"
#include "../src/Debug.h"
#include "glad/glad.h" 
#include "iostream"
#include "fstream"
using std::cout;


Shader::Shader(const std::string& filepath, bool log) : m_FilePath(filepath), m_RendererID(0)
{
    ShadersStr shaders = read_shader(filepath, log);
    m_RendererID = create_shader(shaders.vertexShader, shaders.fragmentShader);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

GLint Shader::get_uniform_location(const std::string& name)
{
    if (uniformLocationsMap.find(name) != uniformLocationsMap.end())
        return uniformLocationsMap[name];


    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
    {
        std::cout << "Shader Uniform (" << name << ") not found\n";
    }
    else uniformLocationsMap[name] = location;
    //std::cout << "Location of uniform (" << name << ") : " << location << std::endl;
    return location;
}

unsigned int Shader::compile_shader(const std::string& source, unsigned int type)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "[FAILED TO COMPILE " << (type == GL_VERTEX_SHADER ? "VERTEX SHADER" : "FRAGMENT SHADER") << "] ---> ";
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::create_shader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compile_shader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = compile_shader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

ShadersStr Shader::read_shader(const std::string& location, bool print)
{
    std::ifstream str;
    str.open(location);

    if (str.is_open())
    {
        std::string line;
        std::string vtShaderStr = "";
        std::string fgShaderStr = "";
        bool fragment = false;
        while (std::getline(str, line))
        {
            if (line.find("#FRAGMENT SHADER") != std::string::npos)
            {
                fragment = true;
                continue;
            }
            if (line.find("#VERTEX SHADER") != std::string::npos)
            {
                fragment = false;
                continue;
            }
            if (fragment) fgShaderStr += line + "\n";
            else vtShaderStr += line + "\n";
        }
        if (print)
        {
            //std::cout << location << " : \n\n\n" << doc << "\n";
            std::cout << "VERTEX SHADER at (" << location << ") : " << vtShaderStr << "\n";
            std::cout << "\n------------------------------------------\n\n";
            std::cout << "FRAGMENT SHADER at (" << location << ") : " << fgShaderStr << "\n";
            std::cout << "\n------------------------------------------\n\n";
        }
        str.close();
        return ShadersStr{ vtShaderStr, fgShaderStr, true };
    }
    else
    {
        std::cout << "[ERROR] ---> Error reading from (" << location << ").\n\n";
        return ShadersStr{ "", "", false };
    }
}

void Shader::set_uniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(get_uniform_location(name), v0, v1, v2, v3));
}

void Shader::set_uniform1f(const std::string& name, float v0)
{
    GLint location = get_uniform_location(name);
    GLCall(glUniform1f(location, v0));
}

void Shader::set_uniform1i(const std::string& name, int v0)
{
    GLint location = get_uniform_location(name);
    GLCall(glUniform1i(location, v0));
}

void Shader::set_uniformMat4(const std::string& name, glm::mat4& v0)
{
    GLint location = get_uniform_location(name);
    GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &v0[0][0]));
}