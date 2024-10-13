#version 460

in vec3 Color;

out vec4 FragColor;

uniform vec3 lightColor;


void main() {
  float ambientStrength = 0.3;
  vec3 ambient = ambientStrength * lightColor;
  FragColor = vec4(ambient * Color, 1.0);
}
