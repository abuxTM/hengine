#include <engine.h>

Engine* engine = nullptr;

int main(int argc, char *argv[]) {

  engine = new Engine(1280, 720);

  // Main engine loop
  while (!glfwWindowShouldClose(engine->window)) {
    engine->update();
    engine->inputs(engine->window);
    engine->render();
  }

  engine->clean();
  
  return 0;
}
