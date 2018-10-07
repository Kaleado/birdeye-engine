#ifndef CURSOR_H
#define CURSOR_H

#include <cmath>
#include "Camera.hpp"
#include "Thing.hpp"

/**
  Class representing the mouse cursor in the game.
 */
class Cursor : public Thing {
public:
  //!Executed every frame.
  virtual void tick();

  //!Responds to a given event.
  virtual void handleInput(sf::Event event);

  //!Draws the cursor at its current position.
  virtual void draw(sf::RenderWindow& window);
  
  //!Kicks the cursor at a given angle (in DEGREES) to simulate recoil.
  void kick(double angle, double strength);

  //!Gets the position the cursor is currently over IN THE GAME WORLD.
  sf::Vector2f getWorldPosition();

  //!Moves the cursor to a given position on the screen.
  void moveToScreenPosition(sf::Vector2f pos);

  //!Moves the cursor to a given position in the world.
  void moveToWorldPosition(sf::Vector2f pos);
  
  Cursor(std::string path) : Thing(path) {}
protected:
  //!The amount of drag on the mouse cursor (for when it is kicked).
  double _drag = 0.5;

  //!These are executed when the left and right mouse buttons are
  //!pressed and released.
  virtual void _onLeftPressed(sf::Vector2f pos){};
  virtual void _onLeftReleased(sf::Vector2f pos){};
  virtual void _onRightPressed(sf::Vector2f pos){};
  virtual void _onRightReleased(sf::Vector2f pos){};
};

//!This is _the_ cursor.
extern std::shared_ptr<Cursor> cursor; 

#endif
