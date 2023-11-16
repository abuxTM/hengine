#ifndef PLANEOBJECT_H
#define PLANEOBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader.h>

class PlaneObject {
public:
  enum ObjectShader {
    COLOR,
    TEXTURED,
  };
  PlaneObject(glm::vec3 pos, ObjectShader objectShader=COLOR);
  void clean();

  void update();
  void render(glm::mat4 projection, glm::mat4 view);

  void setPos(glm::vec3 pos) { this->pos = pos; }
  glm::vec3 getPos() { return pos; }
  void setTexture(unsigned int texture1, unsigned int texture2) { this->texture1 = texture1; this->texture2 = texture2; }

private:
  Shader* shader;
  ObjectShader objectShader;
  unsigned int VAO, VBO;
  unsigned int verticesSize;
  unsigned int texture1, texture2;
  glm::vec3 pos;
  float vertices[180] = {
    // Pos                // Tex
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f
  };
};

#endif
