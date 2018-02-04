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

void Enemy::_whenIdle(){
  double aggroThreshold = 350;  
  if(_getDistanceFromPlayer() < aggroThreshold){
    enemyState = ES_AGGRO;
  }  
}

void Enemy::handleCollision(std::weak_ptr<Thing> other){
  std::shared_ptr<Enemy> asEnemy = std::dynamic_pointer_cast<Enemy>(other.lock());
  if(asEnemy){
    preventOverlapping(asEnemy, 1.0);
  }
}

void Enemy::_setImageBasedOnFacing(){
  std::string newPath;
  float facingDegrees = getVectorAngleDegrees(_facing);    
  //Change sprite based on the eight directions.
  if(-22.5 < facingDegrees && facingDegrees < 22.5){
    //Right
    newPath = "enemy-right.png";
      
  }
  else if(22.5 < facingDegrees && facingDegrees < 67.5){
    //Down-right
    newPath = "enemy-downright.png";
      
  }
  else if(67.5 < facingDegrees && facingDegrees < 112.5){
    //Down
    newPath = "enemy-down.png";
      
  }
  else if(112.5 < facingDegrees && facingDegrees < 157.5){
    //Down-left
    newPath = "enemy-downleft.png";
      
  }
  else if(-67.5 < facingDegrees && facingDegrees < -22.5){
    //Up-right
    newPath = "enemy-upright.png";
      
  }
  else if(-112.5 < facingDegrees && facingDegrees < -67.5){
    //Up
    newPath = "enemy-up.png";
      
  }
  else if(-157.5 < facingDegrees && facingDegrees < -112.5){
    //Up-left
    newPath = "enemy-upleft.png";
      
  }
  else {
    //Left
    newPath = "enemy-left.png";      
  }
  if(_path != newPath){
    _path = newPath;
    _isLoaded = false;
  }  
}

void Enemy::_whenAggro(){
  _facing = getUnitVectorBetween(_position, player->getPosition());
  _setImageBasedOnFacing();
  double dist = _getDistanceFromPlayer();
  double attackRange = 30;  
  if(dist > attackRange){
    auto target = player->getPosition();

    auto unitVector = getUnitVectorBetween(_position, target);
    
    float vx = unitVector.x * _speed;
    float vy = unitVector.y * _speed;

    setXVelocity(vx);
    setYVelocity(vy);
  }
  else {
    enemyState = ES_ATTACKING;
  }
  
}

void Enemy::_whenAttacking(){
  static bool hasAttacked = false;
  setXVelocity(0);
  setYVelocity(0);    
  if(!hasAttacked){
    _currentAnimation = Animation({"anim0.png", "anim1.png", "anim2.png", "anim1.png", "anim0.png"}, false, 10);
    _isAnimating = true;
    auto attackAnimation = Animation({"atk0.png", "atk1.png", "atk2.png", "atk3.png", "atk4.png"}, false, 30);
    std::shared_ptr<Bullet> attack = std::make_shared<HostileBullet>(attackAnimation, _position, 20, sf::Vector2f(0,0));
    playfield->addThing(attack);
    hasAttacked = true;
  }
  if(_currentAnimation.hasFinished()){
    hasAttacked = false;
    enemyState = ES_AGGRO;
  }
}

void Enemy::die(){
  //No on-death effects yet.
}

void Enemy::tick(){
  _sprite.setColor(sf::Color(255 - 255*(static_cast<double>(_hp)/_maxHp), 255 * (static_cast<double>(_hp)/_maxHp), 0));
  if(enemyState == ES_IDLE){
    _whenIdle();
  }
  if(enemyState == ES_AGGRO){
    _whenAggro();
  }

  if(enemyState == ES_ATTACKING){
    _whenAttacking();
  }
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
