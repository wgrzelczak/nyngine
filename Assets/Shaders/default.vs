#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform uint time;

out vec3 outColor;


void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	outColor = aColor * (sin(time / 1000000.0f) + 1.0f) * 0.5f;
}