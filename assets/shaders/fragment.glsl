#version 330
out vec4 FragColor;
uniform float deltatime;
uniform float time;
uniform sampler2D u_texture;
in vec2 TexCoord;

float map(float value, float min1, float max1, float min2, float max2) {
    return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

float mapsin(float v){
    return map(sin(v), -1.0, 1.0, 0.2, 0.8);
}
void main()
{
    FragColor = texture(u_texture, TexCoord);
}