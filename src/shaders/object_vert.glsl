#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Color;

void main() {
  vec3 position = vec3(aPos.x + (gl_InstanceID * 2.0f), aPos.y, aPos.z);
  gl_Position =  projection * view * model * vec4(position, 1.0);
  Color = aColor;
}
