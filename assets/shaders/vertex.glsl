#version 330
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoord;
out vec2 TexCoord;

uniform float deltatime;
uniform float time;
uniform float freq;
uniform mat4 utransform;
uniform mat4 uview;
uniform mat4 uprojection;

float absfloat(float f){
    if (f < 0){
        return f - 2*f;
    }
    return f;
}
void main()
{
    vec3 sap = aPos;
    sap.z = 1.0;
    TexCoord = texCoord;
    vec4 position = vec4(sap.x * absfloat(sin(time*freq)), sap.y * absfloat(sin(time*freq)), sap.z, 1.0);
    gl_Position = uprojection * (uview * (utransform * position));
}