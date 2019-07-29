#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 8) in vec4 aJoint;
layout (location = 9) in vec4 aWeight;

uniform uint time;
uniform mat4 M;
uniform mat4 MVP;
uniform mat4 jointMatirx[100];

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
    FragPos = vec3(M * vec4(aPos, 1.0));
    Normal = normalize(mat3(transpose(inverse(M))) * aNormal);
    TexCoord = aTexCoord;
    
    mat4 skinMatrix = mat4(
        aWeight.x * jointMatirx[int(aJoint.x)]
        + aWeight.y * jointMatirx[int(aJoint.y)]
        + aWeight.z * jointMatirx[int(aJoint.z)]
        + aWeight.w * jointMatirx[int(aJoint.w)]);
        
    gl_Position = MVP * skinMatrix * vec4(aPos, 1.0);
}