#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <shader.h>

class GameObject {
public:
  enum ObjectShader {
    COLOR,
    TEXTURED,
    LIGHTING,
  };
  GameObject(glm::vec3 pos, ObjectShader objectShader=COLOR);
  void clean();

  void update();
  void render(glm::vec3 camPos, glm::vec3 lightPos, glm::mat4 projection, glm::mat4 view);

  void setTexture(unsigned int texture1, unsigned int texture2) { this->texture1 = texture1; this->texture2 = texture2; }
  bool checkCollision(glm::vec3& other, glm::vec3& otherSize);
  bool checkCollision(GameObject& other);

  Shader* shader;
  ObjectShader objectShader;
  unsigned int VAO, VBO;
  unsigned int texture1, texture2;

  std::string objectName;
  glm::vec3 pos;
  glm::vec3 rot = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f);
  glm::vec3 objectColor = glm::vec3(0.4f, 0.4f, 0.4f);

  // Material
  glm::vec4 material = glm::vec4(0.4f, 0.4f, 1.0f, 8.0f);

  float vertices[288] = {
    // Pos                   // Light                // Tex
    -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,     0.0f, 0.0f,

     0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     0.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     0.0f, 0.0f,
  };
};


#endif
