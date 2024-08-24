#include "FPSCamera.h"
#include "iostream"
#include "sstream"
#include <iomanip>
//#include "string"
using std::cout;
using std::endl;


FPSCamera::FPSCamera(float x, float y, float z)
	: yaw(0), pitch(0), pos(x, y, z), tpPos(0,0,0), up(0, 1, 0) {}

FPSCamera::~FPSCamera() {}

glm::vec3 LogLookDir(0);


void FPSCamera::move(float x, float y, float z)
{
	glm::vec2 alpha(glm::cos(glm::radians(yaw)), glm::sin(glm::radians(yaw)));
	glm::vec2 beta(-glm::sin(glm::radians(yaw)), glm::cos(glm::radians(yaw)));
	glm::vec2 offset((z * alpha) + (x * beta));

	pos.x += offset.x;
	pos.y += y;
	pos.z += offset.y;
}

void FPSCamera::set_look_direction(glm::vec2 mouse)
{
	yaw += mouse.x * sens;
	pitch -= mouse.y * sens;

	if (pitch > 89.9f) pitch = 89.9f;
	if (pitch < -89.9f) pitch = -89.9f;
}

glm::mat4 FPSCamera::get_matrix()
{
	glm::vec3 LookDir(0, 0, 0);

	LookDir.x = glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
	LookDir.y = glm::sin(glm::radians(pitch));
	LookDir.z = glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw));
	LookDir = glm::normalize(LookDir);

	LogLookDir = LookDir; //TEMP

	LookDir.x += pos.x;
	LookDir.y += pos.y;
	LookDir.z += pos.z;

	glm::mat4 matrix = glm::lookAt(pos, LookDir, up);
	matrix = glm::translate(matrix, glm::vec3(-0.5f, -3.0f, -0.5f));
	return matrix;
}


void FPSCamera::log_pos()
{
	cout << std::setprecision(2) << std::fixed;
	cout << "Camera pos : ( X : " << pos.x << ", Y : " << pos.y << ", Z : " << pos.z << ")\n";
}

void FPSCamera::tp(glm::vec3 coords)
{
	pos = coords;
}

void FPSCamera::tp()
{
	pos = tpPos;
}

void FPSCamera::set_tp(glm::vec3 coords)
{
	tpPos = coords;
}

void FPSCamera::set_tp()
{
	tpPos = pos;
}

std::string FPSCamera::log_pos_string()
{
	std::stringstream ss;
	ss << std::setprecision(2) << std::fixed;
	ss << "Camera pos : ( X : " << pos.x << ", Y : " << pos.y << ", Z : " << pos.z << ")\n";
	//std::string s = ss.str();
	return ss.str();
}

std::string FPSCamera::log_dir_string()
{
	std::stringstream ss;
	ss << std::setprecision(2) << std::fixed;
	ss << "Camera dir : ( X : " << LogLookDir.x << ", Y : " << LogLookDir.y << ", Z : " << LogLookDir.z << ")\n";
	//std::string s = ss.str();
	return ss.str();
}
