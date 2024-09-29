#include <cstddef>
#include <cstdio>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
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

#include "graphics/Backend.hpp"
#include "graphics/Mesh.hpp"
#include "graphics/glm/TexturedVertex.hpp"
#include "graphics/opengl/Renderer.hpp"
#include "graphics/opengl/ShaderProgram.hpp"
#include "graphics/opengl/Texture.hpp"
#include "graphics/opengl/TexturedVertexBuffer.hpp"
#include "graphics/opengl/VertexArray.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define RESET_INDEX 999

using namespace Meteora;

void error_callback(int error, const char *description) {
  throw std::runtime_error(description);
}

void GLAPIENTRY opengl_error_callback(GLenum source, GLenum type, GLuint id,
                                      GLenum severity, GLsizei length,
                                      const GLchar *message,
                                      const void *userParam) {
  std::string messageType;
  switch (type) {
  case GL_DEBUG_TYPE_ERROR:
    char buffer[100];
    sprintf(buffer, "GL CALLBACK: severity = 0x%x, message = %s", severity,
            message);
    throw std::runtime_error(buffer);
    return;
  case GL_DEBUG_TYPE_PERFORMANCE:
    messageType = "Performance";
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    messageType = "Deprecated";
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    messageType = "Undefined behavior";
    break;
  default:
    return;
  }
  LOGGER_WARN("GL CALLBACK: type = {}, severity = 0x{:x}, message ={} ",
              messageType, severity, message);
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

  window = glfwCreateWindow(width, height, "Game", NULL, NULL);
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

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(RESET_INDEX);

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(opengl_error_callback, 0);
  glViewport(0, 0, width, height);
}

void Backend::run() {

  Mesh mesh(Position{1.0f, 1.0f, 1.0f});

  LOGGER_INFO("Mesh x{} y{} z{}", mesh.position.x, mesh.position.y,
              mesh.position.z);

  VertexArray vaos(1);
  vaos.generate();
  vaos.bind();

  TexturedVertexBuffer vbos(2);
  vbos.generate();

  float x = 0.0f, y = 0.0f;

  TexturedVertex vertices[] = {
      TexturedVertex(vec3(100.0f, 100.0f, 0.0f), vec2(1.0f, 1.0f)),
      TexturedVertex(vec3(100.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)),
      TexturedVertex(vec3(0.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)),
      TexturedVertex(vec3(0.0f, 100.0f, 0.0f), vec2(0.0f, 1.0f)),
      // second tile
      TexturedVertex(vec3(200.0f, 100.0f, 0.0f), vec2(1.0f, 1.0f)),
      TexturedVertex(vec3(200.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)),
      TexturedVertex(vec3(100.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)),
      TexturedVertex(vec3(100.0f, 100.0f, 0.0f), vec2(0.0f, 1.0f)),
      // third tile
      TexturedVertex(vec3(300.0f, 100.0f, 0.0f), vec2(1.0f, 1.0f)),
      TexturedVertex(vec3(300.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)),
      TexturedVertex(vec3(200.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)),
      TexturedVertex(vec3(200.0f, 100.0f, 0.0f), vec2(0.0f, 1.0f)),

  };

  vbos.bind(ARRAY, 0); // ABO
  vbos.setArrayBuffer(vertices, sizeof(vertices), sizeof(TexturedVertex));

  vbos.bind(ELEMENT, 1); // EBO
  unsigned int indices[] = {
      0,           1,  3,     // first triangle
      1,           2,  3,     // second triangle
      RESET_INDEX,            // restart
      4,           5,  7,     // third triangle
      5,           6,  7,     // fourth triangle
      RESET_INDEX, 8,  9, 11, // fifth triangle
      9,           10, 11     // sixth triangle
  };
  vbos.setElementBuffer(indices, sizeof(indices));

  Texture texture(1);
  texture.generate();
  texture.bind();
  texture.setTextureData("rock_wall_tileset.png");

  texture.unbind();
  vbos.unbind();
  vaos.unbind();

  ShaderProgram shaderProgram = ShaderProgram("vertex.glsl", "fragment.glsl");
  Context context(window, &vaos, &vbos, &shaderProgram, &texture);

  Renderer renderer(&context);
  renderer.render();

  vaos.destroy();
  vbos.destroy();
  texture.destroy();
  shaderProgram.destroy();

  glfwTerminate();
}
