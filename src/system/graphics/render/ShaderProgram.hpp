#pragma once

#include "../opengl.hpp"
#include <fstream>
#include <ios>
#include <string>

#define SHADER_PATH "../src/shaders/"

namespace Meteora {

enum ShaderType { VERTEX = GL_VERTEX_SHADER, FRAGMENT = GL_FRAGMENT_SHADER };

typedef GLuint Shader;
typedef GLuint Program;

class ShaderProgram {
public:
  ShaderProgram(std::string vertexShaderSource,
                std::string fragmentShaderSource) {
    vertexShader = createShader(vertexShaderSource, VERTEX);
    fragmentShader = createShader(fragmentShaderSource, FRAGMENT);
    program = createProgram(vertexShader, fragmentShader);
  }
  inline void destroy() { glDeleteProgram(program); }

  inline void useProgram() { glUseProgram(program); }

  const Program getProgram() const { return program; }

private:
  std::string getShaderSource(std::string path) {
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
  inline Shader createShader(std::string path, ShaderType type) {
    std::string sourceContent = getShaderSource(path);
    const char *source = sourceContent.c_str();
    Shader shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    return shader;
  }
  inline Program createProgram(Shader vertexShader, Shader fragmentShader) {
    Shader program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    return program;
  }

  Shader vertexShader;
  Shader fragmentShader;
  Program program;
};
} // namespace Meteora
