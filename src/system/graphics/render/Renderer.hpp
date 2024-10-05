#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

#include "graphics/render/ShaderProgram.hpp"
#include "graphics/render/Texture.hpp"
#include "graphics/render/VertexArray.hpp"

namespace Meteora {

typedef GLint UniformLocation;

typedef struct {
  mat4 matrix;
  UniformLocation location;
} View, Projection;

class Context {
public:
  Context(VertexArray *vertexArray, ShaderProgram *shaderProgram,
          Texture *texture, Position cameraPosition, Position targetPosition,
          float width, float height)
      : vertexArray(vertexArray), shaderProgram(shaderProgram),
        texture(texture), cameraPosition(cameraPosition),
        targetPosition(targetPosition),
        projection(
            perspective(radians(45.0f), width / height, 0.01f, 100.0f),
            glGetUniformLocation(shaderProgram->getProgram(), "projection")) {
    calculateView();
  }
  VertexArray *vertexArray;
  ShaderProgram *shaderProgram;
  Texture *texture;

  void setPosition(Position cameraPosition, Position targetPosition) {
    this->cameraPosition = cameraPosition;
    this->targetPosition = targetPosition;
    calculateView();
  }

  inline void enableAlphaBlending() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  inline void disableAlphaBlending() { glDisable(GL_BLEND); }

  Projection getProjection() const { return projection; }
  View getView() const { return view; }

private:
  Position cameraPosition;
  Position targetPosition;
  Projection projection;
  View view;
  void calculateView() {
    view = {lookAt(cameraPosition, targetPosition, vec3(0.0f, 1.0f, 0.0f)),
            glGetUniformLocation(shaderProgram->getProgram(), "view")};
  }
};

enum RenderMode { LINES = GL_LINES, TRIANGLES = GL_TRIANGLES };

class Renderer {
public:
  static inline void render(Context &context, RenderMode mode) {

    if (context.texture != NULL)
      context.texture->bind();

    context.shaderProgram->useProgram();

    glUniformMatrix4fv(context.getView().location, 1, GL_FALSE,
                       value_ptr(context.getView().matrix));
    glUniformMatrix4fv(context.getProjection().location, 1, GL_FALSE,
                       value_ptr(context.getProjection().matrix));

    if (context.vertexArray != NULL)
      context.vertexArray->bind();

    glDrawArrays(mode, 0, 6);

    if (context.vertexArray != NULL)
      context.vertexArray->unbind();
  }

private:
  Context *context;
};
} // namespace Meteora
