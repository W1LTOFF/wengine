#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
// layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 normalMat;

// out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
    gl_Position =  projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos,1.0));
    Normal = mat3(normalMat) * aNormal;
    // TexCoord = aTexCoord;
}
