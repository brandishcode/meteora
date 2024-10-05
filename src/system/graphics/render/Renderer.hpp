#pragma once

#include "../opengl.hpp"
#include "render.hpp"
#include <math/matrix.hpp>

namespace Meteora {

enum RenderMode { LINES = GL_LINES, TRIANGLES = GL_TRIANGLES };

class Renderer {
public:
  static inline void render(Context &context, RenderMode mode) {

    if (context.texture != NULL)
      context.texture->bind();

    context.shaderProgram->useProgram();

    glUniformMatrix4fv(context.getView().location, 1, GL_FALSE,
                       &(context.getView().matrix[0].x));
    glUniformMatrix4fv(context.getProjection().location, 1, GL_FALSE,
                       &(context.getProjection().matrix[0].x));

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
