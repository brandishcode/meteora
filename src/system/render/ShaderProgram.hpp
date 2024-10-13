#pragma once

#include "math/matrix.hpp"
#include "opengl.hpp"
#include <fstream>
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

  template <typename T> void setUniform(std::string name, T value);
  template <> void setUniform(std::string name, float value) {
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
  }
  template <> void setUniform(std::string name, Mat4 value) {
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE,
                       &(value[0].x));
  }
  template <> void setUniform(std::string name, Vec3 value) {
    glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &(value.x));
  }

  inline void destroy() { glDeleteProgram(program); }

  inline void useProgram() { glUseProgram(program); }

  inline void unuseProgram() { glUseProgram(0); }

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
