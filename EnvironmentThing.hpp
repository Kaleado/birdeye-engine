#ifndef ENVIRONMENT_THING_H
#define ENVIRONMENT_THING_H

#include <memory>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Thing.hpp"

/**
  Class representing a static environmental feature like a rock or a
  tree. This can be subclassed to give more complex behaviour to
  things like totems, etc.
 */
class EnvironmentThing : public Thing, public std::enable_shared_from_this<EnvironmentThing> {
protected:
  //!Whether or not the thing can be walked through by player or enemy
  //!alike.
  bool _canWalkThrough=false;

  //!Whether or not bullets pass through the thing, or if they are
  //!culled upon impact.
  bool _canShootThrough=false;

  //!Executed when something collides with the thing.
  virtual void _whenCollidingWith(std::weak_ptr<Thing> other);
public:
  //!We make the assumption that most environmental things are just
  //!static features that don't need to do anything. Of course, if you
  //!want to implement something different, then you would override
  //!this method in a subclass.
  virtual void tick(){}

  //!Handles and responds to input every frame.
  virtual void handleInput(sf::Event event){}

  //!Responds to (but does not check for) collisions every
  //!frame. Collision logic between enemies and bullets and this object
  //!is implemented here.
  void handleCollision(std::weak_ptr<Thing> other);

  EnvironmentThing(Animation& anim, sf::Vector2f position, bool canShootThrough, bool canWalkThrough) : Thing(anim, position) {
    _canShootThrough = canShootThrough;
    _canWalkThrough = canWalkThrough;
  }
  EnvironmentThing(std::string path, sf::Vector2f position, bool canShootThrough, bool canWalkThrough) : Thing(path, position) {
    _canShootThrough = canShootThrough;
    _canWalkThrough = canWalkThrough;
  }
  EnvironmentThing(std::string path, bool canShootThrough, bool canWalkThrough) : Thing(path) {
    _canShootThrough = canShootThrough;
    _canWalkThrough = canWalkThrough;
  }
  EnvironmentThing() : Thing() {}
};

#endif
