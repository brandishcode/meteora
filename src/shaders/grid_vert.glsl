#version 460

out vec3 nearPoint;
out vec3 farPoint;

uniform mat4 view;
uniform mat4 projection;

const vec3 pos[4] = vec3[4](
  vec3(-1.0, -1.0, 0.0),
  vec3(1.0, -1.0, 0.0),
  vec3(1.0, 1.0, 0.0),
  vec3(-1.0, 1.0, 0.0)
);

const int idx[6] = int[6](0, 2, 1, 2, 0, 3);

vec3 unprojectPoint(float x, float y, float z) {
  mat4 viewInv = inverse(view);
  mat4 projectionInv = inverse(projection);
  vec4 unprojectedPoint = viewInv * projectionInv * vec4(x, y, z, 1.0);
  return unprojectedPoint.xyz / unprojectedPoint.w;
}



void main() {
  int index = idx[gl_VertexID];

  vec3 position = pos[index];

  nearPoint = unprojectPoint(position.x, position.y, 0.0).xyz;
  farPoint = unprojectPoint(position.x, position.y, 1.0).xyz;

  gl_Position = vec4(position, 1.0);
}
