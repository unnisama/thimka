#version 430
out vec4 FragColor;
uniform vec3 lightcolor = vec3(1.0, 1.0, 1.0);

void main()
{
    FragColor = vec4(lightcolor, 1.0);
}
