#include "callbackevents.h"

std::vector<std::function<void(int,int)>> resizeCallbacks;

std::vector<std::function<void(int,int)>> mousewheelCallbacks;

void WindowResizeCallBack(GLFWwindow* window, int width, int height)
{
	for(auto callback : resizeCallbacks){
        callback(width, height);
    }
}

void AddResizeCallback(std::function<void(int,int)> func){
    resizeCallbacks.push_back(func);
}

void MouseWheelCallBack(GLFWwindow *window, double xoff, double yoff)
{
    for(auto callback : mousewheelCallbacks){
        callback(xoff, yoff);
    }
}

void AddMouseWheelCallback(std::function<void(double, double)> func)
{
    mousewheelCallbacks.push_back(func);
}
