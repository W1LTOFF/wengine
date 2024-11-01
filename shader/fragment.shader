#version 460 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec4 lightColor;

void main()
{
    FragColor = lightColor * texture(ourTexture, TexCoord);
}
