#ifndef ENEMY_H
#define ENEMY_H

#include <cmath>
#include "Thing.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Playfield.hpp"

const int FACING_UP         = 0;
const int FACING_DOWN       = 1;
const int FACING_LEFT       = 2;
const int FACING_RIGHT      = 3;
const int FACING_UP_LEFT    = 4;
const int FACING_UP_RIGHT   = 5;
const int FACING_DOWN_LEFT  = 6;
const int FACING_DOWN_RIGHT = 7;
const int FACING_MAX        = 8;

/**
  This enum represents the current state of an enemy:
  - ES_IDLE: the enemy has not noticed the player, and is just standing around.
  - ES_AGGRO: the enemy has noticed the player.
  - ES_DEAD: the enemy is dead.
  - ES_ATTACKING: the enemy is performing an attack. This state is typically
    replaced with ES_IDLE when the attack animation has completed.
  - ES_FLEE: the enemy is fleeing - currently only used for EnemyLegion.
 */
enum EnemyState { ES_IDLE, ES_AGGRO, ES_DEAD, ES_ATTACKING, ES_FLEE };

/**
  This class represents a generic enemy - this enemy currently (as of
  22/1/2018) has dummy behaviour, and simply runs up to the player
  when in range and attacks with a melee attack.
 */
class Enemy : public Thing {
public:
  //!Get maximum HP.
  int getMaxHp();

  //!Get current HP.
  int getHp();

  //!Returns the center of the sprite (in world coordinates)
  sf::Vector2f getWorldCenter();

  //!The enemy's current state (described above).
  EnemyState enemyState = ES_IDLE;

  //!This function is executed every frame, and serves as the main AI
  //!function for the enemy. Calls _whenIdle(), _whenAggro(), etc.
  //!Don't override this if you can use _whenTick() instead!
  virtual void tick();

  //!Deals damage to the enemy.
  virtual void damage(int amount);

  //!Responds to (but does not check for) collisions every frame. Other
  //!contains a pointer to the Thing that was collided with.
  virtual void handleCollision(std::weak_ptr<Thing> other);

  //!Executed when the creature dies.
  virtual void die();

  Enemy(std::string path, sf::Vector2f position, int maxHp, double speed, sf::FloatRect hitboxAtZeroZero) : Enemy{path, position, maxHp, speed} {
    _hitboxAtZeroZero = hitboxAtZeroZero;
  };
  Enemy(std::array<std::string, FACING_MAX> facingPaths, sf::Vector2f position, int maxHp, double speed, sf::FloatRect hitboxAtZeroZero) : Enemy{facingPaths, position, maxHp, speed} {
    _hitboxAtZeroZero = hitboxAtZeroZero;
  };

  Enemy(std::string path, sf::Vector2f position, int maxHp, double speed) : Thing(path, position) {
    _maxHp = maxHp;
    _hp = _maxHp;
    _speed = speed;
    for(auto i = 0; i < FACING_MAX; ++i){
      _facingPaths[i] = path;
    }
  };
  Enemy(std::array<std::string, FACING_MAX> facingPaths, sf::Vector2f position, int maxHp, double speed) : Thing(facingPaths[0], position) {
    _maxHp = maxHp;
    _hp = _maxHp;
    _speed = speed;
    _facingPaths = facingPaths;
  };
  Enemy(){};

protected:
  //!Changes the creature's sprite based on the direction they're facing.
  void _setImageBasedOnFacing();

  //These methods should be overriden for different enemies.

  //!Executed every frame when the creature's state is ES_IDLE.
  virtual void _whenIdle();

  //!Executed every frame when the creature's state is ES_AGGRO.
  virtual void _whenAggro();

  //!Executed every frame when the creature's state is ES_ATTACKING.
  virtual void _whenAttacking();

  //!Executed when the creature collides with something - this is for enemy-specific logic.
  virtual void _whenCollidingWith(std::weak_ptr<Thing> other);

  //!Executed every tick the creature is alive for.
  virtual void _whenTick();

  //!Executed when the creature dies.
  virtual void _whenKilled();

  //!Does what it says on the tin.
  double _getDistanceFromPlayer();

  //!Enemy stats.
  int _hp, _maxHp;

  //!Pixels per frame the enemy can move at.
  double _speed;

  //!Adds a delay between attacking.
  int _attackTimer;

  //!Paths to images to be displayed when the Enemyis facing in different directions.
  std::array<std::string, FACING_MAX> _facingPaths;
};

#endif
