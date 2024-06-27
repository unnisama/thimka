#pragma once
#include <GLFW/glfw3.h>
#include <functional>
#include <vector>
#include <stdio.h>

void WindowResizeCallBack(GLFWwindow* window, int width, int height);

void AddResizeCallback(std::function<void(int,int)> func);