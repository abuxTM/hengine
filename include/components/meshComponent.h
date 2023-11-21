#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <shader.h>
#include <component.h>

class Mesh : public Component {
public:
  Mesh() {
    // Create new shader
    shader = new Shader("shaders/shader.vs", "shaders/shader.fs");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    shader->use();
    shader->setInt("texture1", 0);
    shader->setInt("texture2", 1);

    // Set up position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Set up texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // normal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
  }

  virtual ~Mesh() = default;

  void render(glm::vec3 camPos, glm::vec3 lightPos, glm::mat4 projection, glm::mat4 view) {
    // Use shader
    shader->use();
    // Set uniforms
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);

    if (texture1) { glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture1); }
    if (texture2) { glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, texture2); }

    shader->setVec3("lightColor",  1.0f, 1.0f, 1.0f);
    shader->setVec3("lightPos", lightPos);
    shader->setVec3("camPos", camPos);

    shader->setFloat("material.ambient",   material.x);
    shader->setFloat("material.diffuse",   material.y);
    shader->setFloat("material.specular",  material.z);
    shader->setFloat("material.shininess", material.w);
    shader->setVec3("skyColor",            glm::vec3(0.5f, 0.5f, 0.5f));

    // Render
    glBindVertexArray(VAO);
    glm::mat4 model = glm::mat4(1.0f);
    // GameObject position
    model = glm::translate(model, glm::vec3(0.4f, 0.4f, 0.4f));
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
    //if (rot[0] != 0 || rot[1] != 0 || rot[2] != 0) model = glm::rotate(model, 1.0f, rot);
    shader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 288);
  }

  Shader* shader = nullptr;
  unsigned int VAO, VBO;
  unsigned int texture1, texture2;

  std::string objectName;
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
