#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include "Render.hpp"
#include <cmath>
#include <algorithm>

/**
  Class representing the camera position, viewing the game world.
 */
class Camera {
public:
  //!Executed every frame.
  virtual void tick();

  //!Handles the given event.
  virtual void handleInput(sf::Event event);

  //!Sets the focus point of the camera - this is the point that the
  //!camera will return to if it gets kicked or moved, etc.
  void setFocusPosition(sf::Vector2f pos);

  //Duh.
  sf::Vector2f getFocusPosition();

  //!Sets the _actual_ position of the camera - the camera will return to the focus position after.
  void setPosition(sf::Vector2f pos);
  //Duh.
  sf::Vector2f getPosition();

  //!Kicks the camera in a given direction (0 degrees is straight to the right).
  void kick(double angleDegrees, double strength);
  
  Camera(sf::Vector2f focusPosition) : _focusPosition{focusPosition} {};
  Camera(){};
protected:
  //!Recalculates the camera's acceleration to ensure it always moves back to the focus position.  
  void _recalculateAcceleration();
  sf::Vector2f _focusPosition;
  sf::Vector2f _position;
  sf::Vector2f _velocity;

  //!The velocity of the camera when it is
  //!kicked has to be stored separately.
  sf::Vector2f _shakeVelocity;
  sf::Vector2f _acceleration;
};

extern Camera camera;

#endif
