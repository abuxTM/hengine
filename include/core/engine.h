#ifndef ENGINE_H
#define ENGINE_H 

#include <glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include <shader.h>
#include <textureManager.h>
#include <UI.h>
#include <skybox.h>
#include <player.h>
#include <cubeObject.h>
#include <planeObject.h>

class Engine {
public:
  Engine(int swidth, int sheight);

  void init_res();

  void update();
  void inputs(GLFWwindow* window);
  void render();

  void clean();

  GLFWwindow* window;

private:
  float background[4] = { 0.912f, 0.912f, 0.912f, 1.0f };

  // Instance
  TextureManager* textureManager = nullptr;
  UI* ui = nullptr;
  Player* player = nullptr;
  GameObject* lightcube = nullptr;
  GameObject* grid = nullptr;
  Skybox* skybox = nullptr;

  // UI
  bool showUI = false;

  // Map
  unsigned int skyboxTex;
  std::vector<CubeObject*> gameobjects;
  bool showObjectNameInput = false;
  bool skyboxEnabled = true;

  // Lighting
  glm::vec3 lightPos;

  // Timing
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  bool wireframeMode = false;
  glm::mat4 projection, view;
};

#endif
