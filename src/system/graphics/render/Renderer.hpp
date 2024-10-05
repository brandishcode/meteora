#pragma once

#include "graphics/opengl.hpp"
#include "graphics/render/ShaderProgram.hpp"
#include "graphics/render/Texture.hpp"
#include "graphics/render/VertexArray.hpp"
#include <math/matrix.hpp>

namespace Meteora {

enum RenderMode { LINES = GL_LINES, TRIANGLES = GL_TRIANGLES };

class Renderer {
public:
  static inline void render(VertexArray *vertexArray,
                            ShaderProgram *shaderProgram, Texture *texture,
                            Mat4 view, Mat4 projection, float zNear, float zFar,
                            RenderMode mode, unsigned int count) {
    if (texture != NULL)
      texture->bind();

    shaderProgram->useProgram();

    glUniform1f(glGetUniformLocation(shaderProgram->getProgram(), "zNear"),
                zNear);
    glUniform1f(glGetUniformLocation(shaderProgram->getProgram(), "zFar"),
                zFar);

    glUniformMatrix4fv(
        glGetUniformLocation(shaderProgram->getProgram(), "view"), 1, GL_FALSE,
        &(view[0].x));
    glUniformMatrix4fv(
        glGetUniformLocation(shaderProgram->getProgram(), "projection"), 1,
        GL_FALSE, &(projection[0].x));

    if (vertexArray != NULL)
      vertexArray->bind();

    glDrawArrays(mode, 0, count);

    if (vertexArray != NULL)
      vertexArray->unbind();
  }

  static inline void enableAlphaBlending() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  static inline void disableAlphaBlending() { glDisable(GL_BLEND); }
};
} // namespace Meteora
