#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <ios>
#include <string>

#define SHADER_PATH "../src/shaders/"
#define TEXTURE_PATH "../src/textures/"

namespace Meteora {

enum ShaderType { VERTEX = GL_VERTEX_SHADER, FRAGMENT = GL_FRAGMENT_SHADER };

typedef GLuint Shader;
typedef GLuint Program;

class ShaderProgram {
public:
  [[nodiscard]] static std::string getShaderSource(std::string path) {
    std::ifstream fs(SHADER_PATH + path, std::ios::in);

    if (!fs.is_open()) {
      std::runtime_error("Shader source read failed");
    }

    std::string content;

    std::string line = "";
    while (!fs.eof()) {
      std::getline(fs, line);
      content.append(line + "\n");
    }

    fs.close();
    return content;
  }
  inline static Shader createShader(std::string path, ShaderType type) {
    std::string sourceContent = getShaderSource(path);
    const char *source = sourceContent.c_str();
    Shader shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    return shader;
  }
  inline static Program createProgram(Shader vertexShader,
                                      Shader fragmentShader) {
    Shader program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    return program;
  }
  inline static void useProgram(Program program) { glUseProgram(program); }
};
} // namespace Meteora
