#pragma once
#include "string"
#include "../Vendor/glm/gtc/type_ptr.hpp"
#include "../Vendor/glm/glm.hpp"
#include <unordered_map>

struct ShadersStr
{
	std::string vertexShader;
	std::string fragmentShader;
	bool valid;
};

class Shader
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	std::unordered_map<std::string, int> uniformLocationsMap;

	int get_uniform_location(const std::string& name);
	unsigned int compile_shader(const std::string& source, unsigned int type);
	unsigned int create_shader(const std::string& vertexShader, const std::string& fragmentShader);
	ShadersStr read_shader(const std::string& location, bool print);

public:
	Shader(const std::string& filepath, bool log);
	~Shader();

	void bind() const;
	void unbind() const;

	void set_uniformMat4(const std::string& name, glm::mat4& v0);
	void set_uniform4f(const std::string& name, float v0, float v2, float v3, float v4);
	void set_uniform1f(const std::string& name, float v0);
	void set_uniform1i(const std::string& name, int v0);
};

