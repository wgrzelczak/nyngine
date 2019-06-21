#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = (vec4(abs(Normal), 1.0) + texture(ourTexture, TexCoord))* 0.5 ;
}