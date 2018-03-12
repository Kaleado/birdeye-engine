#include "BreakableThing.hpp"

sf::Vector2f BreakableThing::getWorldCenter(){
  return Thing::getWorldCenter();
}

void BreakableThing::_whenKilled(){
  //Emit particles.
  int numParticles = 8;
  std::array<std::string, 3> particleTypes = {
    "wood-chip-1.png",
    "wood-chip-2.png",
    "wood-chip-3.png"
  };
  for(auto i = 0; i < numParticles; ++i){
    std::shared_ptr<AmmoCasing> particle = std::make_shared<AmmoCasing>(particleTypes[i%particleTypes.size()], _position,
                                                                        2.0, 0, randDouble() * -2, 0.5, 0.9, FRAMERATE*3);
    playfield->addThing(particle);
  }
}

void BreakableThing::damage(int amount){
  _hp -= amount;
  if(_hp <= 0){
    die();
    cull();
  }
}

BreakableThing::BreakableThing(std::string path, sf::Vector2f position, int maxHp){
  _path = path;
  _position = position;
  _maxHp = maxHp;
  _hp = maxHp;
}

void BreakableThing::handleCollision(std::weak_ptr<Thing> other){
  auto otherPtr = other.lock();
  if(!otherPtr){
    return;
  }
  std::shared_ptr<Bullet> asBullet = std::dynamic_pointer_cast<Bullet>(otherPtr);
  if(!asBullet){
    otherPtr->preventOverlapping(shared_from_this(), 6.5);
  }
  _whenCollidingWith(other);
}

void BreakableThing::_whenCollidingWith(std::weak_ptr<Thing> other){
  //Do nothing.
}
