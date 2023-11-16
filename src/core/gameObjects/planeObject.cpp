#include <planeObject.h>

PlaneObject::PlaneObject(glm::vec3 pos, ObjectShader objectShader) : pos(pos), objectShader(objectShader) {
  if (objectShader == COLOR) { shader = new Shader("shaders/color_shader.vs", "shaders/color_shader.fs"); }
  else if (objectShader == TEXTURED) { shader = new Shader("shaders/shader.vs", "shaders/shader.fs"); }

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  verticesSize = sizeof(vertices);
  glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

  if (objectShader == TEXTURED) {
    shader->use();
    shader->setInt("texture1", 0);
    shader->setInt("texture2", 1);
  } else {
    texture1 = 0;
    texture2 = 0;
  }
  
  // Set up position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  if (objectShader == TEXTURED) {
    // Set up texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
  }
}

void PlaneObject::render(glm::mat4 projection, glm::mat4 view) {
  // Use shader
  shader->use();
  // Set uniforms
  shader->setMat4("projection", projection);
  shader->setMat4("view", view);
  if (objectShader == COLOR) {
    shader->setVec3("objectColor", 1.0f, 1.0f, 1.0f);
    shader->setVec3("lightColor",  1.0f, 1.0f, 1.0f);
  }
  else if (objectShader == TEXTURED) {
    if (texture1) { glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture1); }
    if (texture2) { glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, texture2); }
    shader->setVec3("lightColor",  1.0f, 1.0f, 1.0f);
  }

  // Render
  glBindVertexArray(VAO);
  glm::mat4 model = glm::mat4(1.0f);
  // GameObject position
  model = glm::translate(model, pos);
  shader->setMat4("model", model);
  glDrawArrays(GL_TRIANGLES, 0, verticesSize);
}

void PlaneObject::clean() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}
