#include <cstddef>
#include <cstdio>
#include <fstream>
#include <ios>
#include <logger.hpp>
#include <stdexcept>
#include <string>
#include <system.hpp>

#include "Context.hpp"

using namespace Meteora;

void error_callback(int error, const char *description) {
  throw std::runtime_error(description);
}

void GLAPIENTRY opengl_error_callback(GLenum source, GLenum type, GLuint id,
                                      GLenum severity, GLsizei length,
                                      const GLchar *message,
                                      const void *userParam) {
  type == GL_DEBUG_TYPE_ERROR
      ? LOGGER_ERROR(
            "GL CALLBACK: type = 0x{:x}, severity = 0x{:x}, message = {}", type,
            severity, message)
      : LOGGER_INFO(
            "GL CALLBACK: type = 0x{:x}, severity = 0x{:x}, message = {}", type,
            severity, message);
}

Context::Context() { init(); }

Context::~Context() {}

void Context::init() {
  glfwSetErrorCallback(error_callback);

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VER);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VER);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Make window floating for wayland */
  glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHintString(GLFW_WAYLAND_APP_ID, PROJECT_NAME);

  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(window);

  GLenum err = glewInit();
  if (GLEW_OK != err) {
    std::string errMsg((char *)glewGetErrorString(err));
    throw std::runtime_error(errMsg);
  }

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(opengl_error_callback, 0);
}

void Context::run() {
  VertexArray vaos(1);
  createVAOs(&vaos);
  bindVAO(&vaos, 0);

  VertexBuffer vbos(2);
  createVBOs(&vbos);

  bindVBO(&vbos, ARRAY, 0); // ABO
  float data[] = {
      0.5f,  0.5f,  0.0f, // position
      1.0f,  1.0f,        // texture
      0.5f,  -0.5f, 0.0f, // position
      1.0f,  0.0f,        // texture
      -0.5f, -0.5f, 0.0f, // position
      0.0f,  0.0f,        // texture
      -0.5f, 0.5f,  0.0f, // position
      0.0f,  1.0f         // texture
  };
  setABOData(data, sizeof(data), 4);

  bindVBO(&vbos, ELEMENT, 1); // EBO
  unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };
  setEBOData(indices, sizeof(indices));

  unbindVBOs();
  unbindVAOs();

  Shader vertexShader = createShader("vertex.vert", VERTEX);
  Shader fragmentShader = createShader("fragment.frag", FRAGMENT);
  Program program = createProgram(vertexShader, fragmentShader);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    useProgram(program);
    bindVAO(&vaos, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbindVAOs();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  deleteVAOs(&vaos);
  deleteVBOs(&vbos);
  glDeleteProgram(program);

  glfwTerminate();
}

void Context::createVAOs(VertexArray *vaos) {
  glGenVertexArrays(vaos->size, vaos->names);
}

void Context::deleteVAOs(VertexArray *vaos) {
  glDeleteVertexArrays(vaos->size, vaos->names);
}

void Context::bindVAO(VertexArray *vaos, unsigned int index) {
  glBindVertexArray(vaos->names[index]);
}

void Context::unbindVAOs() { glBindVertexArray(0); }

void Context::createVBOs(VertexBuffer *vbos) {
  glGenBuffers(vbos->size, vbos->names);
}

void Context::deleteVBOs(VertexBuffer *vbos) {
  glDeleteBuffers(vbos->size, vbos->names);
}

void Context::bindVBO(VertexBuffer *vbos, BufferType buffType,
                      unsigned int index) {
  glBindBuffer(buffType, vbos->names[index]);
}

void Context::unbindVBOs() { glBindBuffer(ARRAY, 0); }

void Context::setABOData(float *data, std::size_t size, unsigned int count) {
  glBufferData(ARRAY, size, data, GL_STATIC_DRAW);
  unsigned int stride = size / count;

  // position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
  glEnableVertexAttribArray(0);

  // texture
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride,
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

void Context::setEBOData(unsigned int *data, std::size_t size) {
  glBufferData(ELEMENT, size, data, GL_STATIC_DRAW);
}

std::string Context::getShaderSource(std::string path) {
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

Shader Context::createShader(std::string path, ShaderType type) {
  std::string sourceContent = getShaderSource(path);
  const char *source = sourceContent.c_str();
  Shader shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);
  return shader;
}

Program Context::createProgram(Shader vertexShader, Shader fragmentShader) {
  Shader program = glCreateProgram();

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  return program;
}

void Context::useProgram(Program program) { glUseProgram(program); }
