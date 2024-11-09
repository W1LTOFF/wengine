#version 460 core

// in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
// uniform sampler2D ourTexture;
uniform vec3 lightColor;

out vec4 FragColor;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;


    vec3 result = (ambient + diffuse) * vec3(1.0,0.0,1.0);
    FragColor = vec4(result, 1.0);
    // FragColor = vec4(1,1,1,1);
}
