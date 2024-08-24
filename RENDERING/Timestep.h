#pragma once
#define DT_MS 0
#define DT_SEC 1

class Timespep
{
private:
	float m_Time;
public:
	Timespep(float time = 0.0f) : m_Time(time) {}
	inline float get_time_ms() { return m_Time * 1000; }
	inline float get_time_s() { return m_Time; }

	template<typename T>
	inline T deltaTime(T value, char type) { return type == DT_MS ? value * m_Time * 1000 : value * m_Time; }
};
