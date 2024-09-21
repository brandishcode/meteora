#pragma once

#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "graphics/Buffer.hpp"
#include <logger.hpp>

#define TEXTURE_PATH "../src/textures/"

namespace Meteora {

class Texture : public Buffer {

  typedef typeof(GL_TEXTURE0) ActiveTexture;

public:
  inline void createTextures() { glGenTextures(size, names); }

  inline void bindTexture(unsigned int index) {
    ActiveTexture activeTexture;

    switch (index) {
    case 0:
    default:
      activeTexture = GL_TEXTURE0;
      break;
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, index);
    setFilteringParameters();
  }

  inline void unbindTextures() { glBindTexture(GL_TEXTURE_2D, 0); }

  inline void setTextureData(std::string name) {
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *textureData = stbi_load((TEXTURE_PATH + name).c_str(),
                                           &width, &height, &nrChannels, 4);
    if (textureData) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, textureData);
      glGenerateMipmap(GL_TEXTURE_2D);
    } else {
      LOGGER_ERROR("Failed to load texture");
    }
    stbi_image_free(textureData);
  }

private:
  inline void setFilteringParameters() {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }
};

} // namespace Meteora
