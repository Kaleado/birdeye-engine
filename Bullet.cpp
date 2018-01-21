#include "Bullet.hpp"

void Bullet::handleCollision(std::shared_ptr<Thing> other){
  std::shared_ptr<Enemy> asEnemy = std::dynamic_pointer_cast<Enemy>(other);
  if(asEnemy){
    asEnemy->damage(_damage);
    cull();
  }
  else{
    std::shared_ptr<Player> asPlayer = std::dynamic_pointer_cast<Player>(other);
    if(asPlayer){
      asPlayer->damage(_damage);
      cull();
    }
  }
}

void Bullet::tick(){
  _facing = getUnitVectorOf(_velocity);
  _sprite.setRotation(getVectorAngleDegrees(_facing));
  if(--_lifetime < 0 || !isOnScreen(*this)){cull();}
}

void Rocket::handleCollision(std::shared_ptr<Thing> other){
  std::shared_ptr<Enemy> asEnemy = std::dynamic_pointer_cast<Enemy>(other);
  std::shared_ptr<Bullet> explosion = std::make_shared<Bullet>("explosion.png", _position, _damage, sf::Vector2f(0,0), FRAMERATE/2);
  if(asEnemy){
    //asEnemy->damage(_damage);
    playfield->addThing(explosion);
    cull();
  }
  else{
    std::shared_ptr<Player> asPlayer = std::dynamic_pointer_cast<Player>(other);
    if(asPlayer){
      playfield->addThing(explosion);      
      cull();
    }
  }
}

void Rocket::tick(){
  _facing = getUnitVectorOf(_direction);
  _sprite.setRotation(getVectorAngleDegrees(_facing));  
  sf::Vector2f newVelocity = _direction;
  newVelocity.x *= _speed;
  newVelocity.y *= _speed;
  _velocity = newVelocity;
  if(--_lifetime < 0){cull();
  }
  _speed += _acceleration;
}


void HostileBullet::handleCollision(std::shared_ptr<Thing> other){
  std::shared_ptr<Player> asPlayer = std::dynamic_pointer_cast<Player>(other);
  if(asPlayer){
    asPlayer->damage(_damage);
    cull();
  }
}

void HostileBullet::tick(){
  Bullet::tick();
}

void FriendlyBullet::handleCollision(std::shared_ptr<Thing> other){
  std::shared_ptr<Enemy> asEnemy = std::dynamic_pointer_cast<Enemy>(other);
  if(asEnemy){
    asEnemy->damage(_damage);
    cull();
  }
}

void FriendlyBullet::tick(){
  Bullet::tick();
}

void HostileRocket::handleCollision(std::shared_ptr<Thing> other){
  std::shared_ptr<HostileBullet> explosion = std::make_shared<HostileBullet>("explosion.png", _position, _damage, sf::Vector2f(0,0), FRAMERATE/2);  
  std::shared_ptr<Player> asPlayer = std::dynamic_pointer_cast<Player>(other);
  if(asPlayer){
    //asPlayer->damage(_damage);
    playfield->addThing(explosion);
    cull();
  }
}

void HostileRocket::tick(){
  Rocket::tick();
}

void FriendlyRocket::handleCollision(std::shared_ptr<Thing> other){
  std::shared_ptr<FriendlyBullet> explosion = std::make_shared<FriendlyBullet>("explosion.png", _position, _damage, sf::Vector2f(0,0), FRAMERATE/2); 
  std::shared_ptr<Enemy> asEnemy = std::dynamic_pointer_cast<Enemy>(other);
  if(asEnemy){
    //asEnemy->damage(_damage);
    playfield->addThing(explosion);
    cull();
  }
}

void FriendlyRocket::tick(){
  Rocket::tick();
}
