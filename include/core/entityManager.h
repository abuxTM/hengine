#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <memory>
#include <entity.h>

class EntityManager {
public:
  EntityManager() = default;
  ~EntityManager() = default;

  void update();
  void render();
  void refresh();

  void addEntity(Entity* n_entity);
  void removeEntity(Entity* n_entity);

private:
  std::vector<std::unique_ptr<Entity>> entities;
};

#endif
