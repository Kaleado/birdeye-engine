#include "Bullet.hpp"

void Bullet::handleCollision(std::weak_ptr<Thing> other){
  std::shared_ptr<Enemy> asEnemy = std::dynamic_pointer_cast<Enemy>(other.lock());
  if(asEnemy && _isFriendly){
    asEnemy->damage(_damage);
    cull();
  }
  std::shared_ptr<Player> asPlayer = std::dynamic_pointer_cast<Player>(other.lock());
  if(asPlayer && !_isFriendly){
    asPlayer->damage(_damage);
    cull();
  }
}

bool Bullet::isFriendly(){
  return _isFriendly;
}

void Bullet::tick(){
  _facing = getUnitVectorOf(_velocity);
  _rotation = getVectorAngleDegrees(_facing);
  if(--_lifetime < 0 || !isOnScreen(*this)){cull();}
}

void Rocket::handleCollision(std::weak_ptr<Thing> other){
  float explosionRadius = 32;
  std::shared_ptr<Enemy> asEnemy = std::dynamic_pointer_cast<Enemy>(other.lock());

  std::shared_ptr<Bullet> explosion = std::make_shared<Bullet>(_isFriendly, "explosion.png", sf::Vector2f{_position.x - explosionRadius, _position.y - explosionRadius}, _damage, sf::Vector2f(0,0), FRAMERATE/2);
  if(_isFriendly && asEnemy){
    //asEnemy->damage(_damage);
    playfield->addThing(explosion);
    cull();
  }
  std::shared_ptr<Player> asPlayer = std::dynamic_pointer_cast<Player>(other.lock());
  if(!_isFriendly && asPlayer){
    playfield->addThing(explosion);
    cull();
  }
}

void Rocket::tick(){
  _rotation = getVectorAngleDegrees(getUnitVectorOf(_direction));
  _sprite.setRotation(getVectorAngleDegrees(_facing));
  sf::Vector2f newVelocity = _direction;
  newVelocity.x *= _speed;
  newVelocity.y *= _speed;
  _velocity = newVelocity;
  if(--_lifetime < 0){
    cull();
  }
  _speed += _acceleration;
}
