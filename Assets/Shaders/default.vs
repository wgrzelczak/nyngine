#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform uint time;
uniform mat4 M;
uniform mat4 MVP;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
    FragPos = vec3(M * vec4(aPos, 1.0));
    Normal = normalize(mat3(transpose(inverse(M))) * aNormal);
    TexCoord = aTexCoord;

    gl_Position = MVP * vec4(aPos, 1.0);
}