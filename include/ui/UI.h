#ifndef UI_H
#define UI_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <sceneManager.h>
#include <textureManager.h>
#include <cubeObject.h>
#include <player.h>

class UI {
public:
  UI(GLFWwindow* window);

  void worldUI(Player* player, std::vector<CubeObject*>& gameobjects, bool& skyboxEnabled, bool& wireframeMode, float background[4], glm::vec3& lightPos);
  void gameobjectsUI(TextureManager* textureManager, std::vector<CubeObject*>& gameobjects);
  void toolkitUI(Camera* camera);
  void inspectUI(TextureManager* textureManager, std::vector<CubeObject*>& gameobjects);
  void consoleUI();

private:
  SceneManager* sceneManager = nullptr;

  unsigned int objectSelected = -1;
  unsigned int currentShader = 0;
};

#endif
