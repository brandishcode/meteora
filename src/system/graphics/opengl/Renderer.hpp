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
#include "graphics/opengl/VertexBuffer.hpp"
namespace Meteora {

typedef GLint UniformLocation;

typedef struct {
  mat4 matrix;
  UniformLocation location;
} Model, View, Projection;

struct Context {
  VertexArray *vertexArray;
  VertexBuffer *vertexBuffer;
  ShaderProgram *shaderProgram;
  Texture *texture;
  Model *model;
  View view;
  Projection projection;
};

class Renderer {
public:
  static inline void render(Context &context) {

    if (context.texture != NULL) {
      context.texture->bind();
    }

    context.shaderProgram->useProgram();

    glUniformMatrix4fv(context.model->location, 1, GL_FALSE,
                       value_ptr(context.model->matrix));
    glUniformMatrix4fv(context.view.location, 1, GL_FALSE,
                       value_ptr(context.view.matrix));
    glUniformMatrix4fv(context.projection.location, 1, GL_FALSE,
                       value_ptr(context.projection.matrix));

    context.vertexArray->bind();
    // glDrawElements(GL_TRIANGLE_STRIP, 20, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_LINES, 0, 6);
    context.vertexArray->unbind();
  }

private:
  Context *context;
};
} // namespace Meteora
