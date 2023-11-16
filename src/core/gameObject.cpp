#include <gameObject.h>

GameObject::GameObject(glm::vec3 pos, ObjectShader objectShader) : pos(pos), objectShader(objectShader) {
  if (objectShader == COLOR) { shader = new Shader("shaders/color_shader.vs", "shaders/color_shader.fs"); }
  else if (objectShader == TEXTURED) { shader = new Shader("shaders/shader.vs", "shaders/shader.fs"); }
  else if (objectShader == LIGHTING) { shader = new Shader("shaders/light_shader.vs", "shaders/light_shader.fs"); }

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  if (objectShader == TEXTURED) {
    shader->use();
    shader->setInt("texture1", 0);
    shader->setInt("texture2", 1);
  } else {
    texture1 = 0;
    texture2 = 0;
  }

  // Set up position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  if (objectShader == COLOR) {
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
  }
  else if (objectShader == TEXTURED) {
    // Set up texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // normal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
  }
}

void GameObject::render(glm::vec3 camPos, glm::vec3 lightPos, glm::mat4 projection, glm::mat4 view) {
  // Use shader
  shader->use();
  // Set uniforms
  shader->setMat4("projection", projection);
  shader->setMat4("view", view);

  if (objectShader == COLOR) {
    shader->setVec3("objectColor", objectColor);
    shader->setVec3("lightColor",  1.0f, 1.0f, 1.0f);
    shader->setVec3("lightPos", lightPos);
    shader->setVec3("camPos", camPos);
  }
  else if (objectShader == TEXTURED) {
    if (texture1) { glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture1); }
    if (texture2) { glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, texture2); }
    shader->setVec3("lightColor",  1.0f, 1.0f, 1.0f);
    shader->setVec3("lightPos", lightPos);
    shader->setVec3("camPos", camPos);
  }
  else if (objectShader == LIGHTING) {
    shader->setVec3("lightColor",  1.0f, 0.2f, 0.2f);
  }

  shader->setFloat("material.ambient",   material.x);
  shader->setFloat("material.diffuse",   material.y);
  shader->setFloat("material.specular",  material.z);
  shader->setFloat("material.shininess", material.w);

  // Render
  glBindVertexArray(VAO);
  glm::mat4 model = glm::mat4(1.0f);
  // GameObject position
  model = glm::translate(model, pos);
  model = glm::scale(model, size);
  if (rot[0] != 0 || rot[1] != 0 || rot[2] != 0) model = glm::rotate(model, 1.0f, rot);
  shader->setMat4("model", model);
  glDrawArrays(GL_TRIANGLES, 0, 288);
}

bool GameObject::checkCollision(GameObject& other) {
  bool collX = pos.x + size.x >= other.pos.x && other.pos.x + other.size.x >= pos.x;
  bool collY = pos.y + size.y >= other.pos.y && other.pos.y + other.size.y >= pos.y;
  bool collZ = pos.z + size.z >= other.pos.z && other.pos.z + other.size.z >= pos.z;

  return collX && collY && collZ;
}

bool GameObject::checkCollision(glm::vec3& other, glm::vec3& otherSize) {
  bool collX = pos.x + size.x >= other.x && other.x + otherSize.x >= pos.x;
  bool collY = pos.y + size.y >= other.y && other.y + otherSize.y >= pos.y;
  bool collZ = pos.z + size.z >= other.z && other.z + otherSize.z >= pos.z;

  return collX && collY && collZ;
}

void GameObject::clean() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}
