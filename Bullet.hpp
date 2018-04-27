#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include "Thing.hpp"
#include "Enemy.hpp"

/**
  A class representing a bullet fired by a gun, _OR AN ATTACK
  ANIMATION_. Use this for melee attacks as well. Important point -
  this represents an UNALIGNED BULLET, that will damage FRIEND AND FOE
  ALIKE. To make bullets for player guns, subclass this into a
  friendly bullet (see FriendlyBullet for an example). I realise this
  is probably needlessly complicated but it was a graceful way to
  minimising code repetition.
 */
class Bullet : public Thing {
protected:
  //!Damage dealt by the bullet when it comes into contact with something.
  int _damage;

  //!The number of frames before the bullet is automatically culled.
  int _lifetime;

  //!Whether the bullet will harm the player or if it will harm enemies.
  bool _isFriendly;
public:
  //!Returns the bounds of the bullet.
  sf::FloatRect getBounds();

  //!Executed every frame, but you should know this by now.
  virtual void tick();

  //!Returns whether the bullet is friendly or not.
  bool isFriendly();

  //!If you want your bullet to explode or do something when it hits a
  //!game object, your subclass should override this!
  virtual void handleCollision(std::weak_ptr<Thing> other);

  //Sorry for all these constructors.
  Bullet(bool isFriendly, std::string path, sf::Vector2f position, int damage) : Thing(path, position) {
    _name = "Bullet";
    _isFriendly = isFriendly;
    _damage = damage;
  };
  Bullet(bool isFriendly, Animation& anim, sf::Vector2f position, int damage) : Thing("", position) {
    _name = "Bullet";
    _isFriendly = isFriendly;
    _currentAnimation = anim;
    _isAnimating = true;
    _damage = damage;
  };
  Bullet(bool isFriendly, std::string path, sf::Vector2f position, int damage, sf::Vector2f velocity, int lifetime=FRAMERATE/3) : Thing(path, position) {
    _name = "Bullet";
    _isFriendly = isFriendly;
    _damage = damage;
    _velocity = velocity;
    _lifetime = lifetime;
    _facing = getUnitVectorOf(_velocity);
  };
  Bullet(bool isFriendly, Animation& anim, sf::Vector2f position, int damage, sf::Vector2f velocity, int lifetime=FRAMERATE/3) : Thing("", position) {
    _name = "Bullet";
    _isFriendly = isFriendly;
    _currentAnimation = anim;
    _isAnimating = true;
    _damage = damage;
    _velocity = velocity;
    _lifetime = lifetime;
    _facing = getUnitVectorOf(_velocity);
  };
  //!This is the constructor most weapons will use.
  Bullet(bool isFriendly, sf::Vector2f position, int damage,
         sf::Vector2f velocity, int lifetime) :  Bullet(isFriendly, "bullet-final.png", position, damage, velocity, lifetime) {
    _name = "Bullet";
    _facing = getUnitVectorOf(_velocity);
  }
  Bullet(){};
};

//!Represents a rocket.
class Rocket : public Bullet {
protected:
  sf::Vector2f _direction;
  double _speed = -5.0;
  double _blastRadius;
  double _acceleration;
public:
  virtual void tick();
  virtual void handleCollision(std::weak_ptr<Thing> other);
  //!This is the constructor most weapons will use.
  Rocket(bool isFriendly, sf::Vector2f position, int damage,
         sf::Vector2f velocity, int lifetime) :  Bullet(isFriendly, "rocket-final.png", position, damage, velocity, lifetime) {
    _name = "Rocket";
    _blastRadius = 15.0;
    _acceleration = 1.0;
    _direction = getUnitVectorOf(velocity);
  }
  Rocket(){}
};

#endif
