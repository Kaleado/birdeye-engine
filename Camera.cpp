#include "Camera.hpp"
#include "Playfield.hpp"
#include <iostream>

Camera camera;

void Camera::_recalculateAcceleration(){
  auto target = _focusPosition;
  auto pos = _position;
  float opp = target.y - pos.y;
  float adj = target.x - pos.x;
  float hyp = std::sqrt(opp*opp + adj*adj);

  float ax = (adj/(hyp));
  float ay = (opp/(hyp));

  _acceleration = sf::Vector2f(ax, ay);
}

void Camera::tick(){
  double drag = 0.9;
  double shakeDrag = 0.7;
  //Set the acceleration to move back to the focus point.
  _recalculateAcceleration();
  auto dx = _position.x - _focusPosition.x;
  auto dy = _position.y - _focusPosition.y;
  if(std::sqrt(dx*dx + dy*dy) > 100){
    _velocity = sf::Vector2f((_velocity.x) * drag + _acceleration.x, (_velocity.y) * drag + _acceleration.y);
  }
  else {
    _velocity = sf::Vector2f(0,0);
  }
  _shakeVelocity = sf::Vector2f((_shakeVelocity.x) * shakeDrag, (_shakeVelocity.y) * shakeDrag);
  _position = sf::Vector2f(_position.x + _velocity.x + _shakeVelocity.x, _position.y + _velocity.y + _shakeVelocity.y);
  _position = sf::Vector2f(std::max<float>(_position.x, float(0.0)), std::max(_position.y, float(0.0)));
  _position = sf::Vector2f(std::min<float>(_position.x, float(playfield->getBounds().width - SCREEN_WIDTH)), std::min(_position.y, float(playfield->getBounds().height - SCREEN_HEIGHT)));
}

void Camera::handleInput(sf::Event event){
  //Nothing to do at the moment.
}

void Camera::setFocusPosition(sf::Vector2f pos){
  _focusPosition = sf::Vector2f(pos.x - window.getSize().x/2, pos.y - window.getSize().y/2);
}

sf::Vector2f Camera::getFocusPosition(){
  return _focusPosition;
}

void Camera::setPosition(sf::Vector2f pos){
  _position = pos;
}

sf::Vector2f Camera::getPosition(){
  return _position;
}

void Camera::kick(double angleDegrees, double strength){
  double angleRads = angleDegrees/180 * 3.141592653589793238;
  _shakeVelocity = sf::Vector2f(std::cos(angleRads) * strength, std::sin(angleRads) * strength);
}
