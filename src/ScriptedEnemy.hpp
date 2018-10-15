//
// Created by kaleado on 14/10/18.
//

#ifndef TOP_DOWN_SHOOTER_SCRIPTEDENEMY_HPP
#define TOP_DOWN_SHOOTER_SCRIPTEDENEMY_HPP

#ifdef __cplusplus
# include <lua5.2/lua.hpp>
#else
# include <lua5.2/lua.h>
# include <lua5.2/lualib.h>
# include <lua5.2/lauxlib.h>
#endif

#include "LuaBridge/LuaBridge.h"
#include "Enemy.hpp"

class Vector2fHelper {
public:
    static float getX(sf::Vector2f const* vec){
        return vec->x;
    }

    static float getY(sf::Vector2f const* vec){
        return vec->y;
    }

    static void setX(sf::Vector2f* vec, float value){
        vec->x = value;
    }

    static void setY(sf::Vector2f* vec, float value){
        vec->y = value;
    }
};

class ScriptedEnemy : public Enemy {
private:
    lua_State* _l = nullptr;
    std::string _script;

    //!Executed when the object is created.
    void _initScript();

    //!Executed every frame when the creature's state is ES_IDLE.
    void _whenIdle();

    //!Executed every frame when the creature's state is ES_AGGRO.
    void _whenAggro();

    //!Executed every frame when the creature's state is ES_ATTACKING.
    void _whenAttacking();

    //!Executed when the creature collides with something - this is for enemy-specific logic.
    void _whenCollidingWith(std::weak_ptr<Thing> other);

    //!Executed every tick the creature is alive for.
    void _whenTick();

    //!Executed when the creature dies.
    void _whenKilled();

    //!Executed when the creature takes damage.
    void _whenDamaged(int amt);

    sf::Vector2f _apiGetVectorToPlayer();
    sf::Vector2f _apiGetPosition() const;
    sf::Vector2f _apiGetVelocity() const;
    void _apiSetPosition(sf::Vector2f pos);
    void _apiSetVelocity(sf::Vector2f vel);
    float _apiGetDistanceFromPlayer();
    void _apiSetAnimation(luabridge::LuaRef listOfFramePaths, bool isLooping, int frameRate);
    bool _apiFinishedAnimation();
    void _apiStopAnimation();
    void _apiStartAnimation();
    static void _apiAddBullet(bool isFriendly, float x, float y,
                              int damage, float vx, float vy, float lifetime, std::string path);

public:
    ScriptedEnemy() = default;
    ScriptedEnemy(std::array<std::string, FACING_MAX> facingPaths, sf::Vector2f position, int maxHp,
            sf::FloatRect hitboxAtZeroZero, std::string script);
};


#endif //TOP_DOWN_SHOOTER_SCRIPTEDENEMY_HPP
