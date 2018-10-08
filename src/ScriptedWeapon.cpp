#include <utility>

//
// Created by kaleado on 8/10/18.
//

#include "ScriptedWeapon.hpp"

void ScriptedWeapon::_initScript() {
    _l = luaL_newstate();
    luaL_dofile(_l, _script.c_str());
    luaL_openlibs(_l);
}

//!Handles when the player presses/releases the primary/secondary fire buttons.
void ScriptedWeapon::pressPrimaryFire(sf::Vector2f target){
    float x = player->getWorldPosition().x;
    float y = player->getWorldPosition().y;
    float tx = target.x;
    float ty = target.y;

    luabridge::getGlobalNamespace(_l)
        .beginNamespace("myPos")
            .addVariable("x", &x, false)
            .addVariable("y", &y, false)
            .endNamespace();

    luabridge::getGlobalNamespace(_l)
        .beginNamespace("myPos")
            .addVariable("x", &x, false)
            .addVariable("y", &y, false)
            .endNamespace();

    luabridge::LuaRef dummy = luabridge::getGlobal(_l, "pressPrimaryFire");
    dummy();
}

void ScriptedWeapon::pressSecondaryFire(sf::Vector2f target){
    luabridge::LuaRef dummy = luabridge::getGlobal(_l, "pressSecondaryFire");
    dummy();
}

void ScriptedWeapon::releasePrimaryFire(sf::Vector2f target){
    luabridge::LuaRef dummy = luabridge::getGlobal(_l, "releasePrimaryFire");
    dummy();
}

void ScriptedWeapon::releaseSecondaryFire(sf::Vector2f target){
    luabridge::LuaRef dummy = luabridge::getGlobal(_l, "releaseSecondaryFire");
    dummy();
}

//!Executed every frame - implement weapon logic in this function.
void ScriptedWeapon::tick(){
}

//!Executed when the weapon is (un)equipped in the player's weapon bar.
void ScriptedWeapon::onEquip(){
    luabridge::LuaRef dummy = luabridge::getGlobal(_l, "onEquip");
    dummy();
}

void ScriptedWeapon::onUnequip(){
    luabridge::LuaRef dummy = luabridge::getGlobal(_l, "onUnequip");
    dummy();
}

//!Executed when the player switches to and away from the weapon.
void ScriptedWeapon::onStow(){
    luabridge::LuaRef dummy = luabridge::getGlobal(_l, "onStow");
    dummy();
}

void ScriptedWeapon::onUnstow(){
    luabridge::LuaRef dummy = luabridge::getGlobal(_l, "onUnstow");
    dummy();
}

ScriptedWeapon::ScriptedWeapon(std::string script) {
    _script = std::move(script);
    _initScript();
}