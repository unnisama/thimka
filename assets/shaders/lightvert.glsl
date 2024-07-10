#version 430
in vec3 aPos;
in vec2 texCoord;
in vec3 normal;
uniform mat4 umodel;
uniform mat4 uview;
uniform mat4 uprojection;

void main()
{
    vec4 position = vec4(aPos, 1.0);
    gl_Position = uprojection * uview * (umodel * position);
}