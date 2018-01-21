#ifndef ENEMY_H
#define ENEMY_H

#include <cmath>
#include "Thing.hpp" 
#include "Player.hpp"
#include "Bullet.hpp"
#include "Playfield.hpp"

enum EnemyState { ES_IDLE, ES_AGGRO, ES_DEAD, ES_ATTACKING };

class Enemy : public Thing {
public:
  EnemyState enemyState = ES_IDLE;
  virtual void tick();
  void damage(int amount);
  virtual void handleCollision(std::shared_ptr<Thing> other);//Responds to (but does not check for) collisions every frame.
  virtual void die();
  Enemy(std::string path, sf::Vector2f position, int maxHp, double speed) : Thing(path, position) {
    _maxHp = maxHp;
    _hp = _maxHp;
    _speed = speed;
  };
  Enemy(){};
protected:
  void _preventOverlapping(std::shared_ptr<Enemy> asEnemy);
  int _hp, _maxHp;
  double _speed;
  virtual void _whenIdle();
  virtual void _whenAggro();
  virtual void _whenAttacking();
  double _getDistanceFromPlayer();
  int _attackTimer;
};

#endif
