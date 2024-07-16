#version 430
out vec4 FragColor;
in vec3 TexCoord;
uniform samplerCube skybox;

void main()
{
    vec4 color1 = texture(skybox, TexCoord);
    
    FragColor = color1;
}
