#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#define PY_SSIZE_T_CLEAN

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <cubeObject.h>

class SceneManager {
public:
  void saveScene(const std::string& fileName, const std::vector<CubeObject*>& gameObjects) {
    std::ofstream outFile(fileName, std::ios::binary);

    if (outFile.is_open()) {
      // Save the size of the vector
      size_t size = gameObjects.size();
      outFile.write(reinterpret_cast<const char*>(&size), sizeof(size_t));

      // Save each CubeObject
      for (const CubeObject* obj : gameObjects) {
        outFile.write(reinterpret_cast<const char*>(&obj->pos), sizeof(glm::vec3));
        outFile.write(reinterpret_cast<const char*>(&obj->rot), sizeof(glm::vec3));
        outFile.write(reinterpret_cast<const char*>(&obj->size), sizeof(glm::vec3));
        outFile.write(reinterpret_cast<const char*>(&obj->texture1), sizeof(unsigned int));
        outFile.write(reinterpret_cast<const char*>(&obj->texture2), sizeof(unsigned int));
      }

    std::cout << "Scene saved to file: " << fileName << std::endl;

    outFile.close();
  } else { std::cerr << "Error opening file: " << fileName << std::endl; }
}

  void loadScene(const std::string& fileName, std::vector<CubeObject*>& gameObjects) {
    std::ifstream inFile(fileName, std::ios::binary);

    if (inFile.is_open()) {
      gameObjects.clear();

      size_t size;
      inFile.read(reinterpret_cast<char*>(&size), sizeof(size_t));

      for (size_t i = 0; i < size; ++i) {
        glm::vec3 objectPos, objectRot, objectSize;
        unsigned int objectTex1, objectTex2;
        inFile.read(reinterpret_cast<char*>(&objectPos),  sizeof(glm::vec3));
        inFile.read(reinterpret_cast<char*>(&objectRot),  sizeof(glm::vec3));
        inFile.read(reinterpret_cast<char*>(&objectSize), sizeof(glm::vec3));
        inFile.read(reinterpret_cast<char*>(&objectTex1), sizeof(unsigned int));
        inFile.read(reinterpret_cast<char*>(&objectTex2), sizeof(unsigned int));
            
        CubeObject* obj = new CubeObject(objectPos, GameObject::TEXTURED);
        obj->setTexture(objectTex1, objectTex2);
        obj->rot = objectRot;
        obj->size = objectSize;
        gameObjects.push_back(obj);
      }
      std::cout << "Scene loaded from file: " << fileName << std::endl;
      inFile.close();
    } else { std::cerr << "Error opening file: " << fileName << std::endl; }
  }
};

#endif
