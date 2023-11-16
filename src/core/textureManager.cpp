#include <textureManager.h>

unsigned int TextureManager::new_texture(const char* path_to_texture, GLenum format, bool flip) {
  int t_width, t_height, nrChannels;
  stbi_set_flip_vertically_on_load(flip);
  unsigned char *data = stbi_load(path_to_texture, &t_width, &t_height, &nrChannels, 0);

  if (!data) {
    std::cout << "Failed to load texture" << std::endl;
    return 0;
  }

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  // Set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // Set the texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Load and generate the texture with the initial size
  if (format == GL_RGBA) { glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t_width, t_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); }
  else if (format == GL_RGB) { glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t_width, t_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); }
  else { std::cout << "Invalid format" << std::endl; stbi_image_free(data); return 0; }

  glGenerateMipmap(GL_TEXTURE_2D);

  // Unbind the texture
  glBindTexture(GL_TEXTURE_2D, 0);

  // Free the initial image data
  stbi_image_free(data);

  return texture;
}
