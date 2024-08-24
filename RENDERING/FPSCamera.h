#pragma once
#include "../Vendor/glm/glm.hpp"
#include "../Vendor/glm/gtc/matrix_transform.hpp"
#include "string"

#define Mouse glm::vec2

class FPSCamera
{
private:
	float yaw, pitch;
	glm::vec3 up, pos;
public:
	glm::vec3 tpPos;
	float sens = 0.1f;
	FPSCamera(float x = 0, float y = 0, float z = 0);
	~FPSCamera();
	void move(float x, float y, float z);
	void set_look_direction(glm::vec2 mouse);
	void log_pos();
	void tp(glm::vec3 coords);
	void tp();
	void set_tp(glm::vec3 coords);
	void set_tp();
	std::string log_pos_string();
	std::string log_dir_string();
	glm::mat4 get_matrix();
};