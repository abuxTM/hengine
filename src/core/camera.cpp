#include <camera.h>

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch)
    : pos(pos), worldUp(up), front(glm::vec3(0.0f, 0.0f, -1.0f)), mouseSensitivity(SENSITIVITY), fov(FOV), yaw(yaw), pitch(pitch) {
  updateCameraVectors();
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
  xoffset *= mouseSensitivity;
  yoffset *= mouseSensitivity;

  yaw   += xoffset;
  pitch += yoffset;

  if (constrainPitch) {
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
  }

  updateCameraVectors();
}

void Camera::updateCameraVectors() {
  // Calculate some new front vector
  glm::vec3 n_front;
  n_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  n_front.y = sin(glm::radians(pitch));
  n_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front = glm::normalize(n_front);

  right = glm::normalize(glm::cross(front, worldUp));
  up    = glm::normalize(glm::cross(right, front));
}
