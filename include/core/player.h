#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <glm/glm.hpp>
#include <camera.h>

class Player {
public:
  Player(glm::vec3 pos);

  void update(float deltaTime);
  void render();
  void inputs(GLFWwindow* window, std::vector<CubeObject*>& gameobjects);

  void mouse_callback(GLFWwindow* window);
  
  Camera* cam;
  glm::vec3 pos;
  glm::vec3 velocity;
  bool mouseLocked = true;
  float speed;
  float d_speed;
  float sprint;

private:
  // Camera
  float lastX = 1280 / 2.0f;
  float lastY = 720 / 2.0f;
  bool firstMouse = true;
};

#endif
