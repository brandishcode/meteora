#pragma once

#include "opengl.hpp"
#include "render/ShaderProgram.hpp"
#include "render/Texture.hpp"
#include "render/VertexArray.hpp"
#include <math/matrix.hpp>

namespace Meteora {

class Renderer {
public:
  static inline void render(VertexArray *vertexArray,
                            ShaderProgram *shaderProgram, Texture *texture,
                            Mat4 &model, Mat4 &view, Mat4 &projection,
                            float zNear, float zFar, Render::Mode mode,
                            unsigned int count, Render::Method drawMethod) {
    if (texture != NULL)
      texture->bind();

    shaderProgram->useProgram();

    glUniform1f(glGetUniformLocation(shaderProgram->getProgram(), "zNear"),
                zNear);
    glUniform1f(glGetUniformLocation(shaderProgram->getProgram(), "zFar"),
                zFar);

    glUniformMatrix4fv(
        glGetUniformLocation(shaderProgram->getProgram(), "model"), 1, GL_FALSE,
        &(model[0].x));
    glUniformMatrix4fv(
        glGetUniformLocation(shaderProgram->getProgram(), "view"), 1, GL_FALSE,
        &(view[0].x));
    glUniformMatrix4fv(
        glGetUniformLocation(shaderProgram->getProgram(), "projection"), 1,
        GL_FALSE, &(projection[0].x));

    if (vertexArray != NULL)
      vertexArray->bind();

    switch (drawMethod) {
    case Render::ARRAY:
      glDrawArrays(mode, 0, count);
      break;
    case Meteora::Render::ELEMENT:
      glDrawElements(mode, count, GL_UNSIGNED_INT, 0);
      break;
    }

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
