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
