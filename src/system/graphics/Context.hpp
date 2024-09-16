#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <string>

#define SHADER_PATH "/development/nixos/meteora/src/shaders/"

namespace Meteora {

typedef GLFWwindow Window;
typedef GLsizei Size;
typedef GLuint GenName;
typedef GLuint Shader;
typedef GLuint Program;

class VertexArray {
public:
  VertexArray(Size size) : size(size) { names = new GenName[size]; }
  ~VertexArray() { delete names; }
  GenName *names;
  Size size;
}; // namespace Meteora

class VertexBuffer {
public:
  VertexBuffer(Size size) : size(size) { names = new GenName[size]; }
  ~VertexBuffer() { delete names; }
  GenName *names;
  Size size;
};

enum BufferType { ARRAY = GL_ARRAY_BUFFER, ELEMENT = GL_ELEMENT_ARRAY_BUFFER };
enum ShaderType { VERTEX = GL_VERTEX_SHADER, FRAGMENT = GL_FRAGMENT_SHADER };

class Context {
public:
  Context();
  ~Context();
  void run();

private:
  Window *window;
  void init();
  [[nodiscard]] std::string getShaderSource(std::string path);
  inline void createVAOs(VertexArray *vaos);
  inline void deleteVAOs(VertexArray *vaos);
  inline void bindVAO(VertexArray *vaos, unsigned int index);
  inline void unbindVAOs();
  inline void createVBOs(VertexBuffer *vbos);
  inline void deleteVBOs(VertexBuffer *vbos);
  inline void bindVBO(VertexBuffer *vbos, BufferType buffType,
                      unsigned int index);
  inline void unbindVBOs();
  inline void setABOData(float *data, std::size_t size, unsigned int count);
  inline void setEBOData(unsigned int *data, std::size_t size);
  inline Shader createShader(std::string path, ShaderType type);
  inline Program createProgram(Shader vertexShader, Shader fragmentShader);
  inline void useProgram(Program program);
};
}; // namespace Meteora
