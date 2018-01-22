#ifndef UI_H
#define UI_H

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Render.hpp"
#include "Thing.hpp"
#include "Cursor.hpp"

/*
  Class representing a single UI element.
 */
class Widget : public Thing {
protected:
  bool _mouseOver=false;

  //These will be called when the left mouse button is pressed, released, etc.
  virtual void _onLeftClickPress(){}
  virtual void _onLeftClickRelease(){}
  virtual void _onRightClickPress(){}
  virtual void _onRightClickRelease(){}
  virtual void _onMouseOver(){}
  virtual void _onMouseOff(){}
  virtual void _onKeyPress(sf::Event event){}
  virtual void _onKeyRelease(sf::Event event){}
public:
  //Returns whether the mouse is over this UI element.
  bool isMouseOver();
  
  //Does game-logic related things every frame.
  virtual void tick();
  
  //Handles and responds to input every frame.
  virtual void handleInput(sf::Event event);

  //Draws the widget on the screen.
  virtual void draw(sf::RenderWindow& window);
  
  Widget(std::string path, sf::Vector2f position) : Thing(path, position) {};
  Widget(std::string path) : Thing(path) {};
  Widget(){};
};

/*
  A horizontal bar on the screen, tracking some value vs. its maximum
  value - think something like a health bar.
 */
template <typename T>
class HorizontalBar : public Widget {
protected:
  std::function<T()> _curVal;
  std::function<T()> _maxVal;
  int _height = 15;
  int _width = 100;
  sf::Color _color;
public:
  virtual void tick();
  virtual void draw(sf::RenderWindow& window);
  HorizontalBar(std::function<T()> curVal, std::function<T()> maxVal, sf::Vector2f position, sf::Color color, int width, int height) : _curVal{curVal}, _maxVal{maxVal} {
    _position = position;
    _color = color;
    _width = width;
    _height = height;
  }
  HorizontalBar(){}
  
};

template <typename T>
void HorizontalBar<T>::tick(){
  //Do nothing for now.
}

template <typename T>
void HorizontalBar<T>::draw(sf::RenderWindow& window){
  double proportion = (static_cast<double>(_curVal()))/(_maxVal());
  static sf::RectangleShape bar(sf::Vector2f(_height*proportion, _width));
  bar.setFillColor(_color);
  bar.setSize(sf::Vector2f(_width*proportion, _height));
  bar.setPosition(_position);
  window.draw(bar);
}


#endif
