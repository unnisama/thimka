#version 330
in vec3 aPos;
in vec2 texCoord;
out vec2 TexCoord;

uniform float deltatime;
uniform float time;
uniform float freq;
uniform mat4 uview;
uniform mat4 uprojection;
uniform mat4 umodel;

float map(float value, float min1, float max1, float min2, float max2) {
    return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

float mapsin(float v){
    return map(sin(v), -1.0, 1.0, 0.2, 0.8);
}
float absfloat(float f){
    if (f < 0){
        return f - 2*f;
    }
    return f;
}
void main()
{
    TexCoord = texCoord;
    vec4 position = vec4(aPos, 1.0);
    gl_Position = uprojection * uview * (umodel * position);
}