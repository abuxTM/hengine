cmake_minimum_required(VERSION 3.0)

project(engine)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add executable target
file(
  GLOB SOURCES
  "src/core/*.cpp"
  "src/core/gameObjects/*.cpp"
  "src/essentials/*.cpp"
  "src/essentials/*.c"
  "src/graphics/*.cpp"
  "src/ui/*.cpp"
  "src/ui/imgui/*.cpp"
  "src/gameObjects/*.cpp")

add_executable(engine ${SOURCES})

# Include directories
target_include_directories(engine PRIVATE
  "include/components"
  "include/core"
  "include/core/gameObjects"
  "include/essentials"
  "include/essentials/glad"
  "include/graphics"
  "include/ui"
  "include/ui/imgui"
  "include/glad"
  "libs/glm")

# Link libraries
target_link_libraries(engine PRIVATE imgui glfw assimp GL X11 pthread Xrandr Xi dl)

# Copy shaders to build directory
file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
