#pragma once

#include "graphics.hpp"
#include "opengl.hpp"
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <logger.hpp>

#define TEXTURE_PATH "../src/textures/"

namespace Meteora {

typedef typeof(GL_TEXTURE0) ActiveTexture;

class Texture : public Bindings {

public:
  Texture(Size size) : Bindings(size) {}
  inline void generate() override { glGenTextures(size, names); }

  inline void destroy() override { glDeleteTextures(size, names); }

  inline void bind(BindType type = NONE, unsigned int index = 0) override {
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

  inline void unbind() override { glBindTexture(GL_TEXTURE_2D, 0); }

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
