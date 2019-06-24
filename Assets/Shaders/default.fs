#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 ViewPos;

uniform vec3 DirLightPos;
uniform vec3 DirLightColor;
uniform float DirLightAmbientStrength;
uniform float DirLightSpecularStrength;
uniform uint DirLightSpecularShininess;

uniform sampler2D ourTexture;

void main()
{
    vec3 objColor = vec3(1, 1, 1); //(vec4(abs(Normal), 1.0) + texture(ourTexture, TexCoord)) * 0.5;
    
    //Ambient
    vec3 ambient = DirLightAmbientStrength * DirLightColor;

    //Diffuse
    vec3 lightDir = normalize(DirLightPos - FragPos);
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * DirLightColor;

    //Specular
    vec3 viewDir = normalize(ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), DirLightSpecularShininess);
    vec3 specular = DirLightSpecularStrength * spec * DirLightColor;
    
    vec3 result = (ambient + diffuse + specular) * objColor;
    FragColor = vec4(result, 1.0);
}