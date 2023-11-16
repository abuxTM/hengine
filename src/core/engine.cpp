#include <engine.h>

int screen_width, screen_height;
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  screen_width = width; screen_height = height;
  glViewport(0, 0, screen_width, screen_height);
}

Engine::Engine(int swidth, int sheight) {
  // Initialize GLFW
  glfwInit();

  // Why this here?
  screen_width = swidth;
  screen_height = sheight;

  // Configure GLFW context
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 16);

  // Create new GLFW window
  window = glfwCreateWindow(swidth, sheight, "hengine", NULL, NULL);
  // Checks if your shity ass pc could handle window or not
  if (window == NULL) {
    std::cout << "Failed to initialize window!" << std::endl;
    glfwTerminate();
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }

  // OPENGL Config
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE);
  //glEnable(GL_CULL_FACE);

  ui = new UI(window);

  // Loads all textures
  textureManager = new TextureManager();
  // Load skybox
  skybox = new Skybox(textureManager->skyboxFaces);

  // Load some cool stuff
  player = new Player(glm::vec3(0.0f, 1.5f, 3.0f));
  lightPos = glm::vec3(12.0f, 4.0f, 12.0f);
  lightcube = new GameObject(lightPos, GameObject::LIGHTING);
  grid = new GameObject(glm::vec3(0.0f, -0.5f, 0.0f));
}

void Engine::update() {
  // per-frame time logic
  float currentFrame = static_cast<float>(glfwGetTime());
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;
  
  // Toggle wireframe 
  if (wireframeMode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // camera/view transformation
  projection = glm::perspective(glm::radians(player->cam->fov), (float)screen_width / (float)screen_height, 0.01f, 1000.0f);
  view = player->cam->GetViewMatrix();

  // IT does exactly what you think it does
  player->update(deltaTime);
}

void Engine::inputs(GLFWwindow* window) {
  // How about allowing player to use their inputs?
  player->inputs(window, gameobjects);

  // IF you dont ever want to exit engine remove this line so you cant close engine
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); }
  // Quality of life toggles
  if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) { player->mouseLocked = false; showUI = true; }
  if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) { player->mouseLocked = true; showUI = false; }
}

void Engine::render() {
  // NewFrame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  
  // Allow ImGui to steal our window so you can dock windows
  ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
 
  // Show UI
  if (showUI) {
    ui->worldUI(player, gameobjects, skyboxEnabled, wireframeMode, background, lightPos);
    ui->gameobjectsUI(textureManager, gameobjects);
    ui->inspectUI(textureManager, gameobjects);
    ui->toolkitUI(player->cam);
    ui->consoleUI();
  }

  // Set background color if you dont like skybox
  glClearColor(background[0], background[1], background[2], background[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Render all of ur gameobjects that ur heart desires :)
  for (CubeObject* obj : gameobjects) { obj->render(player->cam->pos, lightPos, projection, view); }
  // Self explanatory
  if (skyboxEnabled) skybox->render(player->cam, projection, view);

  // Render some light represented by cube cos why not
  lightcube->render(player->cam->pos, lightPos, projection, view);
  lightcube->pos = lightPos;

  // Create some shity ahh grid thing
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  grid->render(player->cam->pos, lightPos, projection, view);
  grid->size = glm::vec3(12, 0, 12);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // Check all events and swap buffers
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void Engine::clean() {
  // Shut your self down
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  // Clean ur shity ahh cubes
  for (CubeObject* obj : gameobjects) {
    obj->clean();
  }
  // Same here
  skybox->clean();

  // Yup u guessed right, same here, except its ur window and not gameobjects, preaty much same thing
  glfwTerminate();
}
