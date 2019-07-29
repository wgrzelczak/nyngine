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
    vec4 albedo = vec4(0.5, 0.5, 0.0, 0.0);
    
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
    
    vec4 result = vec4((ambient + diffuse + specular), 0.0) * albedo;
    FragColor = result;
}