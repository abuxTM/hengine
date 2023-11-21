#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>

class Transform {
public:
  Transform() {
    position = glm::vec3(0.0f);
    scale    = glm::vec3(1.0f);
    rotation = glm::vec3(0.0f);
  }
  ~Transform() = default;

  glm::vec3 position;
  glm::vec3 scale;
  glm::vec3 rotation;
};

#endif
