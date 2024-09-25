#include "texture2D.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

polygon::Texture2D::Texture2D(const char* filename) {

    this->filename = filename;

    // Generate the texture
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    // Set texture wrapping and filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Load and generate the texture
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

    if (data) {
        // Choose the correct format based on the number of channels
        GLenum format;
        if (nrChannels == 1) {
            format = GL_RED;
        }
        else if (nrChannels == 3) {
            format = GL_RGB;
        }
        else if (nrChannels == 4) {
            format = GL_RGBA;
        }
        else {
            std::cerr << "Unsupported number of channels: " << nrChannels << std::endl;
            stbi_image_free(data);
            return;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        // Optionally generate mipmaps (if used)
        // glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }
    else {
        std::cerr << "Failed to load texture" << std::endl;
    }
}