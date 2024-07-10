#version 430
in vec3 aPos;
in vec2 texCoord;
in vec3 Normal;
out vec3 apos;
out vec2 TexCoord;
out vec3 vnormal;
layout (binding = 3) readonly buffer ModelMatrices {
    mat4 umodel[];
};
uniform float deltatime;
uniform float time;
uniform float freq;
uniform mat4 uview;
uniform mat4 uprojection;


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
    vnormal = (umodel[gl_InstanceID] * vec4(Normal, 1.0)).xyz;
    vec4 position = umodel[gl_InstanceID] * vec4(aPos, 1.0);
    apos = position.xyz;
    gl_Position = uprojection * uview * (position);
}