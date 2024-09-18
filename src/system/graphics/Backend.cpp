#include <cstddef>
#include <cstdio>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <logger.hpp>
#include <stdexcept>
#include <string>
#include <system.hpp>

#include "Backend.hpp"
#include "ImageLoader.hpp"
#include "ShaderProgram.hpp"
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

void Backend::run() {

  VertexArray vaos(1);
  vaos.createVAOs();
  vaos.bindVAO(0);

  VertexBuffer vbos(2);
  vbos.createVBOs();

  vbos.bindVBO(ARRAY, 0); // ABO
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
  vbos.setABOData(data, sizeof(data), 4);

  vbos.bindVBO(ELEMENT, 1); // EBO
  unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };
  vbos.setEBOData(indices, sizeof(indices));

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *textureData = stbi_load("../src/textures/shadow_chaser.png",
                                         &width, &height, &nrChannels, 0);
  if (textureData) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    LOGGER_ERROR("Failed to load texture");
  }
  stbi_image_free(textureData);

  vbos.unbindVBOs();
  vaos.unbindVAOs();

  Shader vertexShader = ShaderProgram::createShader("vertex.glsl", VERTEX);
  Shader fragmentShader =
      ShaderProgram::createShader("fragment.glsl", FRAGMENT);
  Program program = ShaderProgram::createProgram(vertexShader, fragmentShader);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, texture);

    unsigned int transformLoc = glGetUniformLocation(program, "transform");
    ShaderProgram::useProgram(program);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    trans =
        glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
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
