#include <UI.h>
#include <vector>

UI::UI(GLFWwindow* window) {
  // Setup imgui
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO &io = ImGui::GetIO();(void)io;
  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 8.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 8.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 8.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

  ImGuiStyle& style = ImGui::GetStyle();
  style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330 core");

  sceneManager = new SceneManager();
}

void UI::worldUI(Player* player, std::vector<CubeObject*>& gameobjects, bool& skyboxEnabled, bool& wireframeMode, float background[4], glm::vec3& lightPos) {
  ImGui::Begin("World");

  ImGui::Checkbox("Skybox", &skyboxEnabled);
  ImGui::Checkbox("Wireframe mode", &wireframeMode);
  ImGui::SliderFloat("FOV", &player->cam->fov, 45.0f, 120.0f);
  ImGui::InputFloat("Speed", &player->d_speed);
  if (!skyboxEnabled) ImGui::ColorEdit4("Background", background);
  ImGui::InputFloat3("Light pos", &lightPos[0]);

  ImGui::Spacing();
 
  ImGui::TextColored(ImVec4(0, 1, 1, 1), "Scene");
  // Save & Load -----------------
  if (ImGui::Button("Save")) { sceneManager->saveScene("scene", gameobjects); }
  ImGui::SameLine();
  if (ImGui::Button("Load")) { sceneManager->loadScene("scene", gameobjects); }
  // Save & Load -----------------

  ImGui::End();
}

void UI::gameobjectsUI(TextureManager* textureManager, std::vector<CubeObject*>& gameobjects) {
  ImGui::Begin("World-GameObjects");
  ImGui::BeginChild("GameObjects");
  ImGui::TextColored(ImVec4(1,1,0,1), "GameObjects");

  ImGui::Text("Selected shader: %i", currentShader);
  if (ImGui::Button("Textured")) currentShader = 0;
  ImGui::SameLine();
  if (ImGui::Button("Colored")) currentShader = 1;

  if (ImGui::Button("Add gameobject")) {
    if (currentShader == 0) {
      CubeObject* n_cb = new CubeObject(glm::vec3(0.0f, 0.0f, 0.0f), GameObject::TEXTURED);
      n_cb->setTexture(textureManager->objectTextures[0], textureManager->objectTextures[0]);
      gameobjects.push_back(n_cb);
    } else {
      CubeObject* n_cb = new CubeObject(glm::vec3(0.0f, 0.0f, 0.0f), GameObject::COLOR);
      gameobjects.push_back(n_cb);
    }
  }

  for (int i = 0; i < gameobjects.size(); ++i) {
    ImGui::TextColored(ImVec4(0, 1, 1, 1), "ID: %i", i);
    ImGui::SameLine();

    char selectButtonLabel[32];
    snprintf(selectButtonLabel, sizeof(selectButtonLabel), "Select##%d", i);

    if (ImGui::Button(selectButtonLabel)) { objectSelected = i; }
  }

  ImGui::EndChild();
  ImGui::End();

}

void UI::toolkitUI(Camera* camera) {
  ImGui::Begin("Toolkit");
  ImGui::End();
}

void UI::inspectUI(TextureManager* textureManager, std::vector<CubeObject*>& gameobjects) {
  ImGui::Begin("Inspect");
  if (objectSelected != -1) {
    ImGui::TextColored(ImVec4(0, 1, 1, 1), "Selected Object ID: %i", objectSelected);
    // Set position -----------------
    glm::vec3 pos = gameobjects[objectSelected]->transform->position;
    if (ImGui::InputFloat3("Position", glm::value_ptr(pos))) { gameobjects[objectSelected]->transform->position = pos; }
    // Set position -----------------

    // Set rotation -----------------
    glm::vec3 set_rot = gameobjects[objectSelected]->transform->rotation;
    if (ImGui::InputFloat3("Rotation", glm::value_ptr(set_rot))) { gameobjects[objectSelected]->transform->rotation = set_rot; }
    // Set rotation -----------------

    // Set size ---------------------
    glm::vec3 size = gameobjects[objectSelected]->transform->scale;
    if (ImGui::InputFloat3("Size", glm::value_ptr(size))) { gameobjects[objectSelected]->transform->scale = size; }
    // Set size ---------------------

    // Set material -----------------
    ImGui::TextColored(ImVec4(0, 1, 1, 1), "Material");
    glm::vec4 material = gameobjects[objectSelected]->material;
    if (ImGui::InputFloat4("Material", glm::value_ptr(material))) { gameobjects[objectSelected]->material = material; }
    // Set material -----------------

    // Set color --------------------
    glm::vec3 material_color = gameobjects[objectSelected]->objectColor;
    if (ImGui::ColorEdit3("Color", glm::value_ptr(material_color))) { gameobjects[objectSelected]->objectColor = material_color; }
    // Set color --------------------

    // Set shaders ------------------
    ImGui::TextColored(ImVec4(0, 1, 1, 1), "Shaders");
    ImGui::Text("Current shader: %i", gameobjects[objectSelected]->objectShader);
    ImGui::Text("Shader: ");
    ImGui::SameLine();
    if (ImGui::Button("Textured")) gameobjects[objectSelected]->objectShader = GameObject::TEXTURED;
    ImGui::SameLine();
    if (ImGui::Button("Colored")) gameobjects[objectSelected]->objectShader = GameObject::COLOR;
    // Set shaders ------------------

    if (gameobjects[objectSelected]->objectShader == GameObject::TEXTURED) {
    static unsigned int seltex;
    ImGui::TextColored(ImVec4(0, 1, 1, 1), "Current object textures");
    ImGui::Image((void*)(intptr_t)gameobjects[objectSelected]->texture1, ImVec2(60.0f, 60.0f));
    ImGui::SameLine();
    ImGui::Image((void*)(intptr_t)gameobjects[objectSelected]->texture2, ImVec2(60.0f, 60.0f));
    ImGui::Spacing();
    ImGui::TextColored(ImVec4(0, 1, 1, 1), "Textures");

    for (int i = 0; i < textureManager->btnTextures.size(); ++i) {
      if (ImGui::ImageButton((void*)(intptr_t)textureManager->btnTextures[i], ImVec2(60.0f, 60.0f))) seltex = textureManager->objectTextures[i];
      ImGui::SameLine();
    }
    ImGui::Spacing();

    if (ImGui::Button("Texture")) gameobjects[objectSelected]->texture1 = seltex;
    ImGui::SameLine();
    if (ImGui::Button("Texture2")) gameobjects[objectSelected]->texture2 = seltex;
    }
  }

  ImGui::End();
}

void UI::consoleUI() {
  ImGui::Begin("Console");
  ImGui::End();
}
