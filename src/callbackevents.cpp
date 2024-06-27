#include "callbackevents.h"

std::vector<std::function<void(int,int)>> resizeCallbacks;

void WindowResizeCallBack(GLFWwindow* window, int width, int height)
{
	for(auto callback : resizeCallbacks){
        callback(width, height);
    }
}

void AddResizeCallback(std::function<void(int,int)> func){
    resizeCallbacks.push_back(func);
}