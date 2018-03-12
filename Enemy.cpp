#include "Enemy.hpp"

sf::Vector2f Enemy::getWorldCenter(){
  return _position;
}

double Enemy::_getDistanceFromPlayer(){
  if(player->isCulled()){
    return std::numeric_limits<double>::infinity();
  }
  auto playerPos = player->getPosition();
  double dx = _position.x - playerPos.x;
  double dy = _position.y - playerPos.y;
  return std::sqrt(dx*dx + dy*dy);
}

void Enemy::handleCollision(std::weak_ptr<Thing> other){
  std::shared_ptr<Enemy> asEnemy = std::dynamic_pointer_cast<Enemy>(other.lock());
  if(asEnemy){
    preventOverlapping(asEnemy, 1.0);
  }
  _whenCollidingWith(other);
}

void Enemy::_setImageBasedOnFacing(){
  std::string newPath;
  float facingDegrees = getVectorAngleDegrees(_facing);
  //Change sprite based on the eight directions.
  if(-22.5 < facingDegrees && facingDegrees < 22.5){
    //Right
    newPath = _facingPaths[FACING_RIGHT];
  }
  else if(22.5 < facingDegrees && facingDegrees < 67.5){
    //Down-right
    newPath = _facingPaths[FACING_DOWN_RIGHT];
  }
  else if(67.5 < facingDegrees && facingDegrees < 112.5){
    //Down
    newPath = _facingPaths[FACING_DOWN];
  }
  else if(112.5 < facingDegrees && facingDegrees < 157.5){
    //Down-left
    newPath = _facingPaths[FACING_DOWN_LEFT];
  }
  else if(-67.5 < facingDegrees && facingDegrees < -22.5){
    //Up-right
    newPath = _facingPaths[FACING_UP_RIGHT];
  }
  else if(-112.5 < facingDegrees && facingDegrees < -67.5){
    //Up
    newPath = _facingPaths[FACING_UP];
  }
  else if(-157.5 < facingDegrees && facingDegrees < -112.5){
    //Up-left
    newPath = _facingPaths[FACING_UP_LEFT];
  }
  else {
    //Left
    newPath = _facingPaths[FACING_LEFT];
  }
  if(_path != newPath){
    _path = newPath;
    _isLoaded = false;
  }
}

void Enemy::die(){
  _whenKilled();
  //No on-death effects yet.
}

void Enemy::_whenIdle(){
  //Do nothing.
}

void Enemy::_whenAggro(){
  //Do nothing.
}

void Enemy::_whenAttacking(){
  //Do nothing.
}

void Enemy::_whenTick(){
  //Do nothing.
}

void Enemy::_whenKilled(){
  //Do nothing.
}

void Enemy::_whenCollidingWith(std::weak_ptr<Thing> other){
  //Do nothing.
}

void Enemy::tick(){
  //_sprite.setColor(sf::Color(255 - 255*(static_cast<double>(_hp)/_maxHp), 255 * (static_cast<double>(_hp)/_maxHp), 0));
  if(enemyState == ES_IDLE){
    _whenIdle();
  }
  if(enemyState == ES_AGGRO){
    _whenAggro();
  }

  if(enemyState == ES_ATTACKING){
    _whenAttacking();
  }
  _whenTick();
}

void Enemy::damage(int amount){
  if(amount > 0){
    auto anim = Animation{{"blood1.png", "blood2.png", "blood3.png", "blood4.png"}, false, FRAMERATE/2};
    auto bloodAnimation = std::make_shared<Thing>(anim, _position);
    bloodAnimation->setRotation(randDouble() * 360);
    playfield->addThing(bloodAnimation);
  }
  if(enemyState == ES_IDLE){
    enemyState = ES_AGGRO;
  }
  _hp -= amount;
  if(_hp <= 0){
    die();
    cull();
  }
}
