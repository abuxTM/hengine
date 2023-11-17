#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>
#include <component.h>

class Transform : public Component {
public:
  Transform() = default;
  virtual ~Transform() = default;

  glm::vec3 position = glm::vec3(0.0f);
  glm::vec3 scale    = glm::vec3(0.0f);
  glm::vec3 rotation = glm::vec3(0.0f);
};

#endif
