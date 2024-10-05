#version 460 core

out vec4 Color;

uniform mat4 view;
uniform mat4 projection;

vec3 axis[6] = vec3[](
  vec3(0, 0, 0), vec3(1, 0, 0),
  vec3(0, 0, 0), vec3(0, 1, 0),
  vec3(0, 0, 0), vec3(0, 0, 1)
);

vec3 axisColor[3] = vec3[](
  vec3(1, 0, 0),
  vec3(0, 1, 0),
  vec3(0, 0, 1)
);

void main() {
  vec4 color;

  if(gl_VertexID <= 1)
    color = vec4(axisColor[0].xyz, 1.0);
  else if(gl_VertexID <= 3)
    color = vec4(axisColor[1].xyz, 1.0);
  else
    color = vec4(axisColor[2].xyz, 1.0);

  gl_Position = projection * view * vec4(axis[gl_VertexID].xyz, 1.0);
  Color = color;
}
