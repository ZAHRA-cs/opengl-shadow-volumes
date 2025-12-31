#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec3 Normal;
in vec3 PixelPos;

uniform vec3 LightPos;
uniform vec3 ViewPos;

void main()
{
    // Ambient light only
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * ourColor;
    
    FragColor = vec4(ambient, 1.0);
}
