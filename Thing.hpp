#ifndef THING_H
#define THING_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <functional>
#include "Render.hpp"
#include "Animation.hpp"
#include "Camera.hpp"

/*
  Class representing an object in the game.
  Create actual objects by subclassing this.
 */
class Thing {
protected:
  std::string _path;//The path to the Thing's original sprite.
  bool _isLoaded = false;
  bool _isAnimating = false;
  sf::Texture _texture;//Used with the sprite.
  sf::Sprite _sprite;//The current sprite of the Thing.
  sf::Sprite _originalSprite;//The _original_ sprite of the Thing.
  sf::Vector2f _position;//Where the thing is in the playfield.
  sf::Vector2f _facing;//The direction the thing is facing in the playfield.
  sf::Vector2f _velocity;//Self-explanatory.
  double _rotation = 0;
  bool _cullMe = false;//If this is true, this Thing should be culled from the playfield.
  int _load();//Loads the Thing's original sprite.
  Animation _currentAnimation;//The current animation being played by the Thing.
public:
  virtual void tick();//Does game-logic related things every frame.
  virtual void handleInput(sf::Event event);//Handles and responds to input every frame.
  virtual void handleCollision(std::shared_ptr<Thing> other);//Responds to (but does not check for) collisions every frame.
  void playAnimation(Animation& animation);//Play an animation in the current Thing.
  void cull();//Remove the thing from the playfield.
  float getWorldRotation();
  void setColor(sf::Color c);
  bool isCulled();//Returns whether the thing is to be imminently culled.
  sf::FloatRect getBounds();
  virtual void draw(sf::RenderWindow& window);  
  void setXVelocity(float dx);
  void setYVelocity(float dy);
  void setVelocity(sf::Vector2f v);
  sf::Vector2f getPosition();
  sf::Vector2f getScreenPosition();
  Thing(Animation& anim, sf::Vector2f position) : _path{""}, _position{position} {
    _currentAnimation = anim;
    _isAnimating = true;
  };
  Thing(std::string path, sf::Vector2f position) : _path{path}, _position{position} {};
  Thing(std::string path) : _path{path} {};
  Thing(){};
};

class Particle : public Thing {
protected:
public:
  virtual void tick() = 0;
  virtual void draw(sf::RenderWindow& window) = 0;
  Particle(std::string path, sf::Vector2f position) : Thing(path, position) {};
  Particle(Animation& anim, sf::Vector2f position) : Thing(anim, position) {};
};

class AmmoCasing : public Particle {
private:
  int _lifetime;
  double _z;
  double _dz;
  double _az;
  double _bounciness;
public:
  virtual void tick();
  virtual void draw(sf::RenderWindow& window);
  AmmoCasing(std::string path, sf::Vector2f position, double dx,
             double z, double dz, double az, double bounciness, int lifetime) : Particle(path, position) {
    _velocity.x = dx;
    _z = z;
    _dz = dz;
    _az = az;
    _bounciness = bounciness;
    _lifetime = lifetime;
  };
  AmmoCasing(Animation& anim, sf::Vector2f position, double dx,
             double z, double dz, double az, double bounciness, int lifetime) : Particle(anim, position) {
    _velocity.x = dx;
    _z = z;
    _dz = dz;
    _az = az;
    _bounciness = bounciness;
    _lifetime = lifetime;
  };
};

#endif
