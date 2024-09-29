#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/opengl/ShaderProgram.hpp"
#include "graphics/opengl/Texture.hpp"
#include "graphics/opengl/VertexArray.hpp"
#include "graphics/opengl/VertexBuffer.hpp"
namespace Meteora {

typedef GLFWwindow Window;

struct Context {
  Window *window;
  VertexArray *vertexArray;
  VertexBuffer *vertexBuffer;
  ShaderProgram *shaderProgram;
  Texture *texture;
};

class Renderer {
public:
  explicit Renderer(Context *context) : context(context) {}
  inline void render() {
    mat4 model = mat4(1.0f);
    // model = translate(model, vec3(0.5f, 0.5f, 0.0f));
    // model = rotate(model, radians(-55.0f), vec3(1.0f, 0.0f, 0.0f));
    model = scale(model, vec3(1.0f / 480.0f, 1.0f / 480.0f, 0.0f));

    // mat4 view = lookAt(vec3(0.5f, 0.5f, 1.0f), vec3(0.5f, 0.5f, 0.0f),
    //                    vec3(0.0f, 1.0f, 0.0f));
    mat4 view = mat4(1.0f);
    view = translate(view, vec3(0.0f, 0.0f, -3.0f));
    // mat4 projection = ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
    // mat4 projection = ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
    mat4 projection = mat4(1.0f);
    projection =
        perspective(glm::radians(45.0f), (float)480 / (float)480, 0.1f, 100.0f);

    unsigned int modelLoc =
        glGetUniformLocation(context->shaderProgram->getProgram(), "model");
    unsigned int viewLoc =
        glGetUniformLocation(context->shaderProgram->getProgram(), "view");
    unsigned int projectionLoc = glGetUniformLocation(
        context->shaderProgram->getProgram(), "projection");

    while (!glfwWindowShouldClose(context->window)) {
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      context->texture->bind();
      context->shaderProgram->useProgram();
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
      glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
      glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));

      context->vertexArray->bind();
      glDrawElements(GL_TRIANGLE_STRIP, 20, GL_UNSIGNED_INT, 0);
      context->vertexArray->unbind();

      glfwSwapBuffers(context->window);
      glfwPollEvents();
    }
  }

private:
  Context *context;
};
} // namespace Meteora
