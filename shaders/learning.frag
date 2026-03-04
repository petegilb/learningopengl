#version 330 core

out vec4 FragColor;
in vec3 ourColor;

uniform vec4 testColor;

void main()
{
//    FragColor = vec4(ourColor, 1.0);
    FragColor = testColor;
}