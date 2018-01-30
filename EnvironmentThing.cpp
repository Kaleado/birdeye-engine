#include "EnvironmentThing.hpp"

void EnvironmentThing::handleCollision(std::shared_ptr<Thing> other){
  if(!_canWalkThrough){
    std::shared_ptr<Enemy> asEnemy = std::dynamic_pointer_cast<Enemy>(other);
    std::shared_ptr<Player> asPlayer = std::dynamic_pointer_cast<Player>(other);
    if(asEnemy || asPlayer){
      //Push them away.
    }
  }
  
  if(!_canShootThrough){
    std::shared_ptr<Bullet> asBullet = std::dynamic_pointer_cast<Bullet>(other);
    if(asBullet){
      asBullet->cull();
    }
  }  
}
