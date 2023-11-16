#include <player.h>

Player::Player(glm::vec3 pos) : pos(pos) {
  cam = new Camera(pos);

  speed = 6.0;
  d_speed = speed;
  sprint = 12.0;
  velocity = glm::vec3(0.0f);
}

void Player::update(float deltaTime) {
  pos += velocity * speed * deltaTime;
  cam->pos = pos;
}

void Player::render() {}

void Player::inputs(GLFWwindow* window, std::vector<CubeObject*>& gameobjects) {
  // Del this line and camera will be fast as f
  velocity = glm::vec3(0.0f);

  // Takes your key combos so you can move
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) velocity += cam->front;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) velocity -= cam->front;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) velocity -= cam->right;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) velocity += cam->right;

  // Be faster while holding LSHIFT
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) speed = sprint; else speed = d_speed;
  // Fly up
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)        velocity.y++;
  // Fly down
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) velocity.y--;

  // Toggle mouse
  if (mouseLocked) { mouse_callback(window); glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); } else glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Player::mouse_callback(GLFWwindow* window) {
  double xposIn, yposIn;
  // Gets cursor pos obv
  glfwGetCursorPos(window, &xposIn, &yposIn);

  // Checks if you are a locked
  if (!mouseLocked) return;

  // Some random variables dont worry about it :)
  float xpos = static_cast<float>(xposIn);
  float ypos = static_cast<float>(yposIn);

  // Check if your mouse is first
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  // Very advanced variables
  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;

  // Same here
  lastX = xpos;
  lastY = ypos;

  // Why update cam pos here?
  cam->ProcessMouseMovement(xoffset, yoffset);
}
