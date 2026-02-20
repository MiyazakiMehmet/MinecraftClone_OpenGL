#version 330 core

out vec4 FragColor;

in vec3 FragPos;

uniform sampler2D uTexture;

void main()
{
    FragColor = vec4(0.6, 0.8, 1.0, 1.0);
}
