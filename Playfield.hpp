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
protected:

  //Loads the background image for the level.
  int _loadBackground();
  
  //Draw the background of the level.
  void _drawBackground(sf::RenderWindow& window);
  
  std::vector<std::shared_ptr<Thing>> _thingsOnScreen;//Things currently on the screen - used for broadphase collision detection.
  std::vector<std::shared_ptr<Thing>> _getPossiblyCollidingThings();//Returns a vector of Things that *might* be colliding.
  void _cullThings();//Culls things that are flagged to be culled.
  Camera _camera;
  std::vector<std::shared_ptr<Thing>> _things;//Contains all game objects in the Playfield.  
  sf::Texture _backgroundTexture;//Used with the sprite below.
  sf::Sprite _backgroundSprite;//The current sprite (to be displayed) of the level background.
  //The path to the background image for this level.
  std::string _backgroundPath;
  //Whether or not the background and other assets have been loaded
  //for the level.
  bool _isLoaded=false;
  
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

  Playfield(){}
  Playfield(std::string backgroundPath) : _backgroundPath{backgroundPath} {}

};

extern std::shared_ptr<Playfield> playfield;

#endif
