#include "Enemy.hpp"

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

void Enemy::_preventOverlapping(std::shared_ptr<Enemy> asEnemy){
    //We get the unit vector between the two centers of the enemies -
    //this will point away from the center of one of the enemies.
    float pushFactor = 1.0; //The strength of the 'push' out of an enemy there is.
    sf::Vector2f centerVector = { _position.x - asEnemy->_position.x,
                                  _position.y - asEnemy->_position.y};
    float length = std::sqrt(centerVector.x*centerVector.x + centerVector.y*centerVector.y);
    centerVector = {centerVector.x / length, centerVector.y / length};
    //We then add this vector to the enemy's current velocity.
    _velocity += {centerVector.x*pushFactor, centerVector.y*pushFactor};  
}

void Enemy::handleCollision(std::shared_ptr<Thing> other){
  std::shared_ptr<Enemy> asEnemy = std::dynamic_pointer_cast<Enemy>(other);
  if(asEnemy){
    _preventOverlapping(asEnemy);
  }
}


void Enemy::_whenAggro(){
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
  if(enemyState == ES_IDLE){
    enemyState = ES_AGGRO;
  }
  _hp -= amount;
  if(_hp <= 0){
    die();
    cull();
  }
}
