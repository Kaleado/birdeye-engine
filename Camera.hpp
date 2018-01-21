#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include "Render.hpp"
#include <cmath>

/*
  Class representing the camera position, viewing the game world.
 */
class Camera {
public:
  virtual void tick();
  virtual void handleInput(sf::Event event);  
  void setFocusPosition(sf::Vector2f pos);
  sf::Vector2f getFocusPosition();
  void setPosition(sf::Vector2f pos);
  sf::Vector2f getPosition();
  void kick(double angleDegrees, double strength);
  Camera(sf::Vector2f focusPosition) : _focusPosition{focusPosition} {};
  Camera(){};
protected:  
  void _recalculateAcceleration();
  sf::Vector2f _focusPosition;
  sf::Vector2f _position;
  sf::Vector2f _velocity;
  sf::Vector2f _shakeVelocity;
  sf::Vector2f _acceleration;
};

extern Camera camera;

#endif
