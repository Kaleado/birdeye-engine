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
  void addThing(std::shared_ptr<Thing> thing);
  void draw(sf::RenderWindow& window);
  void tick();
  void handleInput(sf::Event event);
  void kickCamera(double angleDegrees, double strength);
private:
  std::vector<std::shared_ptr<Thing>> _thingsOnScreen;//Things currently on the screen - used for broadphase collision detection.
  std::vector<std::shared_ptr<Thing>> _getPossiblyCollidingThings();
  void _cullThings();
  Camera _camera;
  std::vector<std::shared_ptr<Thing>> _things;
};

extern std::shared_ptr<Playfield> playfield;

#endif
