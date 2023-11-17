#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component {
public:
  Component() = default;
  virtual ~Component() = default;

  Entity* entity;
  virtual bool init() { return true; }
  virtual void update() {}
  virtual void render() {}
};

#endif
