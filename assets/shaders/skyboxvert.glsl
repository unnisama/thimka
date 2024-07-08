#version 430
in vec3 aPos;
in vec2 texCoord;
out vec2 TexCoord;
uniform mat4 umodel;
uniform mat4 uview;
uniform mat4 uprojection;

void main()
{
    TexCoord = texCoord;
    vec4 position = vec4(aPos, 1.0);
    gl_Position = uprojection * uview * (umodel * position);
}