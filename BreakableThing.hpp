#ifndef BREAKABLE_THING_H
#define BREAKABLE_THING_H

#include "Enemy.hpp"

class BreakableThing : public Enemy, public std::enable_shared_from_this<BreakableThing> {
protected:
  //!This will cause particles to fly everywhere.
  void _whenKilled();
  
  //!Executed when something collides with the thing.
  virtual void _whenCollidingWith(std::weak_ptr<Thing> other);

public:
  //!Deals damage to the breakable thing.
  void damage(int amount);

  //!Responds to (but does not check for) collisions every
  //!frame. Collision logic between enemies and bullets and this object
  //!is implemented here.
  void handleCollision(std::weak_ptr<Thing> other);

  BreakableThing(){}
  BreakableThing(std::string path, sf::Vector2f position, int maxHp);
};

#endif
