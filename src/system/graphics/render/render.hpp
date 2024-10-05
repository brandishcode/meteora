#pragma once

#include "../opengl.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "math/matrix.hpp"

typedef GLint UniformLocation;

typedef struct {
  Mat4 matrix;
  UniformLocation location;
} View, Projection;

namespace Meteora {

typedef GLsizei Size;
typedef GLuint Name;

typedef Vec3 Position;

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
    view = {lookAt(cameraPosition, targetPosition, Vec3(0.0f, 1.0f, 0.0f)),
            glGetUniformLocation(shaderProgram->getProgram(), "view")};
  }
};
} // namespace Meteora
