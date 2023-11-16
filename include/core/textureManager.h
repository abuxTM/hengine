#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
#include <vector>

class TextureManager {
public:
  unsigned int new_texture(const char* path_to_texture, GLenum format=GL_RGB, bool flip=true);
  void resize_texture(unsigned int texture, int new_width, int new_height);

  std::vector<std::string> skyboxFaces {
    "assets/skybox/right.jpg",
    "assets/skybox/left.jpg",
    "assets/skybox/top.jpg",
    "assets/skybox/bottom.jpg",
    "assets/skybox/front.jpg",
    "assets/skybox/back.jpg",
  };

  std::vector<unsigned int> objectTextures {
    new_texture("assets/images/grass.jpg"),
    new_texture("assets/images/wall.jpg"),
    new_texture("assets/images/awesomeface.png", GL_RGBA),
    new_texture("assets/images/aot.png", GL_RGBA),
    new_texture("assets/images/bean.jpg"),
    new_texture("assets/images/brick.jpg"),
  };

  std::vector<unsigned int> btnTextures {
    new_texture("assets/images/grass.jpg", GL_RGB, false),
    new_texture("assets/images/wall.jpg", GL_RGB, false),
    new_texture("assets/images/awesomeface.png", GL_RGBA, false),
    new_texture("assets/images/aot.png", GL_RGBA, false),
    new_texture("assets/images/bean.jpg", GL_RGB, false),
    new_texture("assets/images/brick.jpg", GL_RGB, false),
  };
};

#endif
