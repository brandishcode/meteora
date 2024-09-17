#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#define SHADER_PATH "../src/shaders/"
#define TEXTURE_PATH "../src/textures/"

namespace Meteora {

typedef GLFWwindow Window;
typedef GLuint Shader;
typedef GLuint Program;

enum ShaderType { VERTEX = GL_VERTEX_SHADER, FRAGMENT = GL_FRAGMENT_SHADER };

class Backend {
public:
  Backend();
  ~Backend();
  void run();

private:
  Window *window;
  void init();
  [[nodiscard]] std::string getShaderSource(std::string path);
  inline Shader createShader(std::string path, ShaderType type);
  inline Program createProgram(Shader vertexShader, Shader fragmentShader);
  inline void useProgram(Program program);
};
}; // namespace Meteora
