#version 330 core
out vec4 FragColor;

uniform vec3 unlitColor;

void main()
{
    FragColor = vec4(unlitColor, 1.0);
}