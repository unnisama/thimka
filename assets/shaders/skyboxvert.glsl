#version 430
in vec3 aPos;
in vec2 texCoord;
in vec3 normal;
out vec3 TexCoord;
uniform mat4 umodel;
uniform mat4 uview;
uniform mat4 uprojection;

void main()
{
    TexCoord = aPos;
    vec4 position = uprojection * uview * umodel * vec4(aPos, 1.0);
    gl_Position = position;
}