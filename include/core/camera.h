#ifndef CAMERA_H
#define CAMERA_H

#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <cubeObject.h>

enum Camera_Movement {
  UP,
  DOWN,
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float FOV         =  90.0f;

class Camera {
public:
  Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

  glm::mat4 GetViewMatrix() { return glm::lookAt(pos, pos + front, up); }

  void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

  // camera Attributes
  glm::vec3 pos;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 right;
  glm::vec3 worldUp;
  // euler Angles
  float yaw;
  float pitch;
  // camera options
  bool moveFly = false;
  bool sprinting = false;
  float mouseSensitivity;
  float fov;
  glm::vec3 size = glm::vec3(0.5f, 0.5f, 0.5f);

private:
  void updateCameraVectors();
};
#endif
