#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

void main()
{
    // Simple lighting: diffuse with a fixed light direction
    vec3 lightDir = normalize(vec3(-0.2, -1.0, -0.3));
    float diff = max(dot(normalize(Normal), -lightDir), 0.0);
    vec3 baseColor = vec3(0.6, 0.8, 1.0);
    vec3 color = (0.2 + 0.8 * diff) * baseColor;
    FragColor = vec4(color, 1.0);
}
