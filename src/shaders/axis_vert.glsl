#version 460 core

out vec4 Color;

uniform mat4 view;
uniform mat4 projection;

vec3 pos[6] = vec3[](
  vec3(0.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0),
  vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0),
  vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0)
);

vec3 col[3] = vec3[](
  vec3(1.0, 0.0, 0.0),
  vec3(0.0, 1.0, 0.0),
  vec3(0.0, 0.0, 1.0)
);

void main() {
  gl_Position = projection * view * vec4(pos[gl_VertexID], 1.0);

  vec4 color;

  if(gl_VertexID <= 1)
    color = vec4(col[0].xyz, 1.0);
  else if(gl_VertexID <= 3)
    color = vec4(col[1].xyz, 1.0);
  else
    color = vec4(col[2].xyz, 1.0);

  Color = color;
}
