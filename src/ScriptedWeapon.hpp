//
// Created by kaleado on 8/10/18.
//

#ifndef TOP_DOWN_SHOOTER_SCRIPTEDWEAPON_HPP
#define TOP_DOWN_SHOOTER_SCRIPTEDWEAPON_HPP

#ifdef __cplusplus
# include <lua5.2/lua.hpp>
#else
# include <lua5.2/lua.h>
# include <lua5.2/lualib.h>
# include <lua5.2/lauxlib.h>
#endif

#include "LuaBridge/LuaBridge.h"
#include "Weapon.hpp"

class ScriptedWeapon : public Weapon {
private:
    lua_State* _l = nullptr;
    std::string _script;
    void _initScript();
    static float _apiGetPlayerX();
    static float _apiGetPlayerY();
    static float _apiGetPlayerRotation();
    static float _apiGetCursorX();
    static float _apiGetCursorY();
    static void _apiAddBullet(bool isFriendly, float x, float y,
                              int damage, float vx, float vy, float lifetime, std::string path);
    static void _apiCreateAmmoCasing(std::string path, float x, float y, float dx,
                                     float z, float dz, float az, double bounciness);
    static void _apiCameraKick(float dir, float vel);
    static void _apiCameraSetFocus(float x, float y);
    static float _apiGetPlayerFacing();

public:
    //!Handles when the player presses/releases the primary/secondary fire buttons.
    virtual void pressPrimaryFire(sf::Vector2f target);
    virtual void pressSecondaryFire(sf::Vector2f target);
    virtual void releasePrimaryFire(sf::Vector2f target);
    virtual void releaseSecondaryFire(sf::Vector2f target);

    //!Executed every frame - implement weapon logic in this function.
    virtual void tick();

    //!Executed when the weapon is (un)equipped in the player's weapon bar.
    virtual void onEquip();
    virtual void onUnequip();

    //!Executed when the player switches to and away from the weapon.
    virtual void onStow();
    virtual void onUnstow();

    ScriptedWeapon() = default;
    explicit ScriptedWeapon(std::string script);
};


#endif //TOP_DOWN_SHOOTER_SCRIPTEDWEAPON_HPP
