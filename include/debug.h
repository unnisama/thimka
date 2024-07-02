#pragma once
#include <GL/glew.h>
#include <stdio.h>
#define GLM_ENABLE_EXPERIMENTAL

#define GLDEBUGCALL(f) glClearError();\
    f;\
    glLogError(#f, __FILE__, __LINE__)

void glClearError();
void glLogError(const char *func, const char* file, int line);
