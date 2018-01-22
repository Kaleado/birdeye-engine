#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include "Thing.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

/*
  Class representing a game area.
 */
class Playfield {
public:
  //Add a new thing to the playfield.
  void addThing(std::shared_ptr<Thing> thing);

  //Draw everything in the playfield.
  void draw(sf::RenderWindow& window);

  //Executed every frame. If you want to implement something
  //particular to one map (like a global countdown or something), this
  //is the place to implement that logic. You should subclass
  //Playfield to do that.
  virtual void tick();

  //Responds to a given event.
  virtual void handleInput(sf::Event event);

  //Kick the camera in a given direction.
  void kickCamera(double angleDegrees, double strength);
private:
  std::vector<std::shared_ptr<Thing>> _thingsOnScreen;//Things currently on the screen - used for broadphase collision detection.
  std::vector<std::shared_ptr<Thing>> _getPossiblyCollidingThings();//Returns a vector of Things that *might* be colliding.
  void _cullThings();//Culls things that are flagged to be culled.
  Camera _camera;
  std::vector<std::shared_ptr<Thing>> _things;//Contains all game objects in the Playfield.
};

extern std::shared_ptr<Playfield> playfield;

#endif
