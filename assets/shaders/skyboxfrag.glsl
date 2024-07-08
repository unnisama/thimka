#version 430
out vec4 FragColor;
uniform sampler2D u_texture;
in vec2 TexCoord;

void main()
{
    vec4 color1 = texture(u_texture, TexCoord);
    
    FragColor = color1;
}
