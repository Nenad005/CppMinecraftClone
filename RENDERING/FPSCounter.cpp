#include "FPSCounter.h"
#include "GLFW/glfw3.h"
#include "iostream"
using namespace std;

FPSCounter::FPSCounter() : nbFrames(0), lastTime(glfwGetTime())
{

}

FPSCounter::~FPSCounter()
{

}

void FPSCounter::tick()
{
    float currentTime = glfwGetTime();
    nbFrames++;
    if (currentTime - lastTime >= 1.0)
    {
        if (print) cout << "FPS : " << nbFrames << endl;
        nbFrames = 0;
        lastTime += 1.0;
    }
}