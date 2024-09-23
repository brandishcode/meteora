#include <cstddef>
#include <cstdio>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <logger.hpp>
#include <stdexcept>
#include <string>
#include <system.hpp>

#include "Backend.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Vertex.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

Backend::Backend() { init(); }

Backend::~Backend() {}

void Backend::init() {
  glfwSetErrorCallback(error_callback);

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VER);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VER);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Make window floating for wayland */
  glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHintString(GLFW_WAYLAND_APP_ID, PROJECT_NAME);

  unsigned int width = 480, height = 480;

  window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
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
  glEnable(GL_DEPTH_TEST);
  glDebugMessageCallback(opengl_error_callback, 0);
  glViewport(0, 0, width, height);
}

void Backend::run() {

  VertexArray vaos(1);
  vaos.createVAOs();
  vaos.bindVAO(0);

  VertexBuffer vbos(2);
  vbos.createVBOs();

  float x = 0.0f, y = 0.0f;

  Vertex vertices[] = {
      Vertex(vec3(1.0f, 1.0f, 0.0f), vec2((1.0f + x) / 16.0f, 1.0f / 10.0f)),
      Vertex(vec3(1.0f, -1.0f, 0.0f), vec2((1.0f + x) / 16.0f, 0.0f / 10.0f)),
      Vertex(vec3(-1.0f, -1.0f, 0.0f), vec2((0.0f + x) / 16.0f, 0.0f / 10.0f)),
      Vertex(vec3(-1.0f, 1.0f, 0.0f), vec2((0.0f + x) / 16.0f, 1.0f / 10.0f))};

  vbos.bindVBO(ARRAY, 0); // ABO
  unsigned int count = 4;
  unsigned int size = count * 5;
  float *data = new float[size];
  for (unsigned int i = 0; i < count; i++) {
    data[i * 5] = vertices[i].data[0];
    data[i * 5 + 1] = vertices[i].data[1];
    data[i * 5 + 2] = vertices[i].data[2];
    data[i * 5 + 3] = vertices[i].data[3];
    data[i * 5 + 4] = vertices[i].data[4];
  }

  vbos.setABOData(data, size * sizeof(float), 4);

  // vbos.setABOData(vertices, 80, sizeof(vertices) / sizeof(Vertex));

  vbos.bindVBO(ELEMENT, 1); // EBO
  unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };
  vbos.setEBOData(indices, sizeof(indices));

  Texture texture(1);
  texture.createTextures();
  texture.bindTexture(0);
  texture.setTextureData("shadow_chaser.png");

  texture.unbindTextures();
  vbos.unbindVBOs();
  vaos.unbindVAOs();

  Shader vertexShader = ShaderProgram::createShader("vertex.glsl", VERTEX);
  Shader fragmentShader =
      ShaderProgram::createShader("fragment.glsl", FRAGMENT);
  Program program = ShaderProgram::createProgram(vertexShader, fragmentShader);

  mat4 model = mat4(1.0f);
  model = translate(model, vec3(0.5f, 0.5f, 0.0f));
  model = scale(model, vec3(0.5f, 0.75f, 0.0f));
  model = scale(model, vec3(0.25f, 0.25f, 0.0f));
  mat4 view = lookAt(vec3(0.5f, 0.5f, 1.0f), vec3(0.5f, 0.5f, 0.0f),
                     vec3(0.0f, 1.0f, 0.0f));
  mat4 projection = ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

  unsigned int modelLoc = glGetUniformLocation(program, "model");
  unsigned int viewLoc = glGetUniformLocation(program, "view");
  unsigned int projectionLoc = glGetUniformLocation(program, "projection");

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture.bindTexture(0);

    ShaderProgram::useProgram(program);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));

    vaos.bindVAO(0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    vaos.unbindVAOs();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  vaos.deleteVAOs();
  vbos.deleteVBOs();
  glDeleteProgram(program);

  glfwTerminate();
}
