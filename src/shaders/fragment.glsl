#version 460 core

out vec4 FragColor;

in vec4 Color;

uniform sampler2D ourTexture;

void main() {
  FragColor = Color;
}
