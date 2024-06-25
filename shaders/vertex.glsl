#version 330
layout (location = 0) in vec3 aPos;

uniform float deltatime;
uniform float time;
uniform float freq;

float absfloat(float f){
    if (f < 0){
        return f - 2*f;
    }
    return f;
}
void main()
{
    gl_Position = vec4(aPos.x * absfloat(sin(time*freq)), aPos.y * absfloat(sin(time*freq)), aPos.z, 1.0);
}