#version 460 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main() {
  // FragColor = vec4(0.3f, 1.0f, 0.5f, 1.0f);
  FragColor = texture(ourTexture, TexCoord);
}
