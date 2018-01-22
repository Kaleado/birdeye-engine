#ifndef ENEMY_H
#define ENEMY_H

#include <cmath>
#include "Thing.hpp" 
#include "Player.hpp"
#include "Bullet.hpp"
#include "Playfield.hpp"

/*
  This enum represents the current state of an enemy:
  - ES_IDLE: the enemy has not noticed the player, and is just standing around.
  - ES_AGGO: the enemy has noticed the player.
  - ES_DEAD: the enemy is dead.
  - ES_ATTACKING: the enemy is performing an attack. This state is typically
    replaced with ES_IDLE when the attack animation has completed.
 */
enum EnemyState { ES_IDLE, ES_AGGRO, ES_DEAD, ES_ATTACKING };

/*
  This class represents a generic enemy - this enemy currently (as of
  22/1/2018) has dummy behaviour, and simply runs up to the player
  when in range and attacks with a melee attack.
 */
class Enemy : public Thing {
public:
  //The enemy's current state (described above).
  EnemyState enemyState = ES_IDLE;
  
  //This function is executed every frame, and serves as the main AI
  //function for the enemy. Calls _whenIdle(), _whenAggro(), etc.
  virtual void tick();

  //Deals damage to the enemy.
  void damage(int amount);
  
  //Responds to (but does not check for) collisions every frame. Other
  //contains a pointer to the Thing that was collided with.
  virtual void handleCollision(std::shared_ptr<Thing> other);

  //Executed when the creature dies.
  virtual void die();
  Enemy(std::string path, sf::Vector2f position, int maxHp, double speed) : Thing(path, position) {
    _maxHp = maxHp;
    _hp = _maxHp;
    _speed = speed;
  };
  Enemy(){};
protected:
  //Changes the creature's sprite based on the direction they're facing.
  void _setImageBasedOnRotation();

  //Pushes enemies away from one another so they don't crowd in one spot.
  void _preventOverlapping(std::shared_ptr<Enemy> asEnemy);

  //Executed every frame when the creature's state is ES_IDLE.
  virtual void _whenIdle();

  //Executed every frame when the creature's state is ES_AGGRO.
  virtual void _whenAggro();
  
  //Executed every frame when the creature's state is ES_ATTACKING.
  virtual void _whenAttacking();

  //Does what it says on the tin.
  double _getDistanceFromPlayer();

  //Enemy stats.
  int _hp, _maxHp;
  double _speed;//Pixels per frame the enemy can move at.
  int _attackTimer;//Adds a delay between attacking.
};

#endif
