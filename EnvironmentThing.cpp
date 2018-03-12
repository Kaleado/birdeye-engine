#include "EnvironmentThing.hpp"

void EnvironmentThing::handleCollision(std::weak_ptr<Thing> other){
  auto otherPtr = other.lock();
  if(!otherPtr){
    return;
  }
  if(!_canWalkThrough){
    otherPtr->preventOverlapping(shared_from_this(), 6.5);
  }
  if(!_canShootThrough){
    std::shared_ptr<Bullet> asBullet = std::dynamic_pointer_cast<Bullet>(otherPtr);
    if(asBullet){
      asBullet->cull();
    }
  }
  _whenCollidingWith(other);
}

void EnvironmentThing::_whenCollidingWith(std::weak_ptr<Thing> other){
  //Do nothing.
}
