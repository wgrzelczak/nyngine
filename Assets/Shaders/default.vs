#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTexCoord;

uniform uint time;
uniform mat4 MVP;

out vec3 outColor;
out vec2 TexCoord;

void main()
{
    gl_Position = MVP * vec4(aPos, 1.0);
    //gl_Position = vec4(aPos, 1.0);

	TexCoord = aTexCoord;
	outColor = aCol * (sin(time / 1000000.0f) + 1.0f) * 0.5f;
}