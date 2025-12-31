#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec3 Normal;
in vec3 PixelPos;

uniform vec3 LightPos;
uniform vec3 ViewPos;

void main()
{
    // Diffuse lighting calculation
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - PixelPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);
    
    // Specular component
    vec3 viewDir = normalize(ViewPos - PixelPos);
    vec3 halfAngle = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfAngle), 0.0), 32);
    vec3 specular = spec * vec3(0.5, 0.5, 0.5);
    
    // Final color
    vec3 result = (diffuse + specular) * ourColor;
    FragColor = vec4(result, 1.0);
}
