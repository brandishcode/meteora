#version 460

in vec3 nearPoint;
in vec3 farPoint;

out vec4 FragColor;

uniform mat4 view;
uniform mat4 projection;
uniform float zNear;
uniform float zFar;

vec4 grid(vec3 fragPos3D, float scale, bool drawAxis) {
  vec2 coord = fragPos3D.xz * scale;
  vec2 derivative = fwidth(coord);
  vec2 grid = abs(fract(coord - 0.5) - 0.5) / derivative;
  float line = min(grid.x, grid.y);
  float minimumz = min(derivative.y, 1);
  float minimumx = min(derivative.x, 1);
  vec4 color = vec4(0.2, 0.2, 0.2, 1.0 - min(line, 1.0));

  if(fragPos3D.x > -0.1 * minimumx && fragPos3D.x < 0.1 * minimumx)
    color.z = 1.0;
  
  if(fragPos3D.z > -0.1 * minimumz && fragPos3D.z < 0.1 * minimumz)
    color.x = 1.0;

  return color;
}

float computeDepth(vec3 pos) {
  vec4 clipSpacePos = projection * view * vec4(pos.xyz, 1.0);
  return (clipSpacePos.z / clipSpacePos.w);
}

float computeLinearDepth(vec3 pos) {
  vec4 clipSpacePos = projection * view * vec4(pos.xyz, 1.0);
  float clipSpaceDepth = (clipSpacePos.z / clipSpacePos.w) * 2.0 - 1.0;
  float linearDepth = (2.0 * zNear * zFar) /
    (zFar + zNear - clipSpaceDepth * (zFar - zNear));
  return linearDepth / zFar;
}

void main() {
  float t = -nearPoint.y / (farPoint.y - nearPoint.y);
  vec3 fragPos3D = nearPoint + t * (farPoint - nearPoint);
  gl_FragDepth = computeDepth(fragPos3D);
  float linearDepth = computeLinearDepth(fragPos3D);
  float fading = max(0, (0.5 - linearDepth));
  FragColor = (grid(fragPos3D, 10, true) + grid(fragPos3D, 1, true)) * float(t > 0);
  FragColor.a *= fading;
}
