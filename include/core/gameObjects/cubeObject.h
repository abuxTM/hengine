#ifndef CUBEOBJECT_H
#define CUBEOBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <gameObject.h>
#include <shader.h>

class CubeObject : public GameObject {
public:
  CubeObject(glm::vec3 pos, ObjectShader objectShader=COLOR) : GameObject(pos, objectShader) {}
};

#endif
