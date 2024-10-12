#pragma once

#include "opengl.hpp"
#include "render/Texture.hpp"
#include "render/VertexArray.hpp"
#include <math/matrix.hpp>
#include <string>

namespace Meteora {

class Renderer {
public:
  static void sample(void *(setUniform)(std::string, float)) {}
  static inline void render(VertexArray *vertexArray, Texture *texture,
                            Render::Mode mode, unsigned int count,
                            Render::Method drawMethod,
                            unsigned int instanceCount = 0) {
    if (texture != NULL)
      texture->bind();

    if (vertexArray != NULL)
      vertexArray->bind();

    switch (drawMethod) {
    case Render::ARRAY:
      glDrawArrays(mode, 0, count);
      break;
    case Render::ELEMENT:
      glDrawElements(mode, count, GL_UNSIGNED_INT, 0);
      break;
    case Render::ELEMENT_INSTANCED:
      glDrawElementsInstanced(mode, count, GL_UNSIGNED_INT, 0, instanceCount);
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

  static inline void enableDepthTesting() { glEnable(GL_DEPTH_TEST); }
  static inline void disableDepthTesting() { glDisable(GL_DEPTH_TEST); }
};
} // namespace Meteora
