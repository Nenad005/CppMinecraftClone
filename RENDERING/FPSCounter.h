#pragma once


class FPSCounter
{
private:
	float lastTime;
	int nbFrames;
public:
	bool print;
	FPSCounter();
	~FPSCounter();
	void tick();
};