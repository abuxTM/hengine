#include <entityManager.h>

void EntityManager::update() {
  for (auto& entity : entities) entity->update();
}

void EntityManager::render() {
  for (auto& entity : entities) entity->render();
}

void EntityManager::refresh() {

}


void EntityManager::addEntity(Entity* n_entity) {
  std::unique_ptr<Entity> uniquePtr { n_entity };
  entities.emplace_back(std::move(uniquePtr));
}

void EntityManager::removeEntity(Entity* n_entity) {

}
