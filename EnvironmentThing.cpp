#include "EnvironmentThing.hpp"

void EnvironmentThing::handleCollision(std::weak_ptr<Thing> other){
  auto otherPtr = other.lock();
  if(!otherPtr){
    return;
  }
  std::shared_ptr<Bullet> asBullet = std::dynamic_pointer_cast<Bullet>(otherPtr);
  std::shared_ptr<EnvironmentThing> asEnvironmentThing = std::dynamic_pointer_cast<EnvironmentThing>(otherPtr);
  if(!_canWalkThrough && !asBullet && !asEnvironmentThing){
    otherPtr->preventOverlapping(shared_from_this(), 6.5);
  }
  if(!_canShootThrough){
    if(asBullet){
      asBullet->cull();
    }
  }
  _whenCollidingWith(other);
}

void EnvironmentThing::_whenCollidingWith(std::weak_ptr<Thing> other){
  //Do nothing.
}
