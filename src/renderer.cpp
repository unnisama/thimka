#include <renderer.h>

void glClearError(){
    while(GLenum err = glGetError()){
    }
}

void glLogError(const char *func, const char* file, int line){
    while(GLenum err = glGetError()){
        printf("%s:%d %s\n", file, line, func);
        printf("    [OpenGL Error] (%d)\n", err);
    }
}
