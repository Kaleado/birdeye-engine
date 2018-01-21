#ifndef CURSOR_H
#define CURSOR_H

#include <cmath>
#include "Camera.hpp"
#include "Thing.hpp"

class Cursor : public Thing {
public:
  virtual void tick();
  virtual void handleInput(sf::Event event);
  virtual void draw(sf::RenderWindow& window);
  void kick(double angle, double strength);
  sf::Vector2f getWorldPosition();
  void moveToScreenPosition(sf::Vector2f pos);
  void moveToWorldPosition(sf::Vector2f pos);
  Cursor(std::string path) : Thing(path) {}
protected:
  double _drag = 0.5;
  virtual void _onLeftPressed(sf::Vector2f pos){};
  virtual void _onLeftReleased(sf::Vector2f pos){};
  virtual void _onRightPressed(sf::Vector2f pos){};
  virtual void _onRightReleased(sf::Vector2f pos){};
};

extern std::shared_ptr<Cursor> cursor; 

#endif
