#include "Cursor.hpp"

std::shared_ptr<Cursor> cursor;

sf::Vector2f Cursor::getWorldPosition(){
  return _position + camera.getPosition();
}

void Cursor::moveToScreenPosition(sf::Vector2f pos){
  _position = pos;
}

void Cursor::moveToWorldPosition(sf::Vector2f pos){
  _position = pos - camera.getPosition();
}

void Cursor::tick(){
  _velocity.x *= _drag;
  _velocity.y *= _drag;
}

void Cursor::handleInput(sf::Event event){
  if(event.type == sf::Event::MouseMoved){
    //This is dumb but we need it as a float.
    auto p = sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
    _position = p;
  }
  
  if(event.type == sf::Event::MouseButtonPressed){
    int mx = event.mouseButton.x;
    int my = event.mouseButton.y;
    if(event.mouseButton.button == sf::Mouse::Left){
      //Left clicked - primary fire.
      _onLeftPressed(sf::Vector2f(mx, my));
    }
    if(event.mouseButton.button == sf::Mouse::Right){
      //Right clicked - secondary fire.
      _onRightPressed(sf::Vector2f(mx, my));
    }
  }

  if(event.type == sf::Event::MouseButtonReleased){
    int mx = event.mouseButton.x;
    int my = event.mouseButton.y;
    if(event.mouseButton.button == sf::Mouse::Left){
      //Left clicked - primary fire.
      _onLeftReleased(sf::Vector2f(mx, my));
    }
    if(event.mouseButton.button == sf::Mouse::Right){
      //Right clicked - secondary fire.
      _onRightReleased(sf::Vector2f(mx, my));
    }
  }
  
}

void Cursor::draw(sf::RenderWindow& window){
  _position += _velocity;
  _sprite.setPosition(_position);
  _sprite.setOrigin(16, 16);
  sf::Mouse::setPosition(sf::Vector2i(_position.x, _position.y));
  //Either show the current animation, or display the original sprite for the Thing.
  sf::Sprite animationFrame;
  if(_isAnimating && _currentAnimation.getNextFrame(animationFrame)){
    animationFrame.setPosition(_position);
    window.draw(animationFrame);
  }
  else if(_isLoaded || _load() == 0){
    _isAnimating = false;
    window.draw(_sprite);
  }
  else {
    //Got an error trying to load the original sprite.
  }  
}

void Cursor::kick(double angleDegrees, double strength){
  double angleRads = angleDegrees/180 * 3.141592653589793238;
  _velocity = sf::Vector2f(std::cos(angleRads) * strength, std::sin(angleRads) * strength);
}

