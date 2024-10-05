#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

#include "graphics/opengl/ShaderProgram.hpp"
#include "graphics/opengl/Texture.hpp"
#include "graphics/opengl/VertexArray.hpp"

namespace Meteora {

typedef GLint UniformLocation;

typedef vec3 CameraPosition;

typedef struct {
  mat4 matrix;
  UniformLocation location;
} View, Projection;

class Context {
public:
  Context(VertexArray *vertexArray, ShaderProgram *shaderProgram,
          Texture *texture, CameraPosition cameraPosition, float width,
          float height)
      : vertexArray(vertexArray), shaderProgram(shaderProgram),
        texture(texture), cameraPosition(cameraPosition),
        projection(
            perspective(radians(45.0f), width / height, 0.0f, 100.0f),
            glGetUniformLocation(shaderProgram->getProgram(), "projection")) {
    calculateView();
  }
  VertexArray *vertexArray;
  ShaderProgram *shaderProgram;
  Texture *texture;

  void setCameraPosition(CameraPosition cameraPosition) {
    this->cameraPosition = cameraPosition;
    calculateView();
  }
  Projection getProjection() const { return projection; }
  View getView() const { return view; }

private:
  CameraPosition cameraPosition;
  Projection projection;
  View view;
  void calculateView() {
    view = {
        lookAt(cameraPosition, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
        glGetUniformLocation(shaderProgram->getProgram(), "view")};
  }
};

class Renderer {
public:
  static inline void render(Context &context) {

    if (context.texture != NULL)
      context.texture->bind();

    context.shaderProgram->useProgram();

    glUniformMatrix4fv(context.getView().location, 1, GL_FALSE,
                       value_ptr(context.getView().matrix));
    glUniformMatrix4fv(context.getProjection().location, 1, GL_FALSE,
                       value_ptr(context.getProjection().matrix));

    if (context.vertexArray != NULL)
      context.vertexArray->bind();

    glDrawArrays(GL_LINES, 0, 6);

    if (context.vertexArray != NULL)
      context.vertexArray->unbind();
  }

private:
  Context *context;
};
} // namespace Meteora
