#include "Ui.hpp"

bool Widget::isMouseOver(){
  auto vec = sf::Mouse::getPosition();
  bool isOver = getBounds().contains(vec.x, vec.y);
  return isOver;
}

void Widget::tick(){
  //Do nothing.
}

void Widget::handleInput(sf::Event event){
  if(!_mouseOver && isMouseOver()){
    _mouseOver = true;
    _onMouseOver();
  }
  if(_mouseOver && !isMouseOver()){
    _mouseOver = false;
    _onMouseOff();
  }
  if(event.type == sf::Event::KeyPressed){
    _onKeyPress(event);
  }
  if(event.type == sf::Event::KeyReleased){
    _onKeyRelease(event);
  }
  if(event.type == sf::Event::MouseButtonPressed && isMouseOver()){
    if(event.mouseButton.button == sf::Mouse::Left){
      _onLeftClickPress();
    }
    if(event.mouseButton.button == sf::Mouse::Right){
      _onRightClickPress();
    }    
  }
  if(event.type == sf::Event::MouseButtonReleased && isMouseOver()){
    if(event.mouseButton.button == sf::Mouse::Left){
      _onLeftClickRelease();
    }
    if(event.mouseButton.button == sf::Mouse::Right){
      _onRightClickRelease();
    }    
  }
}

void Widget::draw(sf::RenderWindow& window){
  _position += _velocity;
  //Either show the current animation, or display the original sprite for the Thing.  
  if(_isAnimating){
    //If animating, get the next frame.    
    bool moreFramesToGo = _currentAnimation.getNextFrame(_sprite);
    if(!moreFramesToGo){
      _isAnimating = false;
      _isLoaded = false;
    }
  }
  else if(!_isLoaded){
    if(_load()){
      std::cerr << "Could not load image at path '" << _path << "'\n";
      return;
    }
  }
  _sprite.setPosition(_position);
  window.draw(_sprite);  
}
