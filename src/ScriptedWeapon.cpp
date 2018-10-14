#include <utility>

//
// Created by kaleado on 8/10/18.
//

#include "ScriptedWeapon.hpp"

void ScriptedWeapon::_initScript() {
    _l = luaL_newstate();
    luaL_openlibs(_l);
    luabridge::getGlobalNamespace(_l)
        .beginClass<ScriptedWeapon>("game")
            .addStaticProperty("playerX", &ScriptedWeapon::_apiGetPlayerX)
            .addStaticProperty("playerY", &ScriptedWeapon::_apiGetPlayerY)
            .addStaticProperty("playerRotation", &ScriptedWeapon::_apiGetPlayerRotation)
            .addStaticProperty("playerFacing", &ScriptedWeapon::_apiGetPlayerFacing)
            .addStaticProperty("cursorX", &ScriptedWeapon::_apiGetCursorX)
            .addStaticProperty("cursorY", &ScriptedWeapon::_apiGetCursorY)
            .addStaticFunction("addBullet", &ScriptedWeapon::_apiAddBullet)
            .addStaticFunction("createAmmoCasing", &ScriptedWeapon::_apiCreateAmmoCasing)
            .addStaticFunction("cameraKick", &ScriptedWeapon::_apiCameraKick)
            .addStaticFunction("cameraSetFocus", &ScriptedWeapon::_apiCameraSetFocus)
        .endClass();
    luaL_dofile(_l, _script.c_str());
}

void ScriptedWeapon::_apiCameraSetFocus(float x, float y){
    camera.setFocusPosition(sf::Vector2f{x, y});
}

float ScriptedWeapon::_apiGetPlayerX(){
    return player->getWorldPosition().x;
}

float ScriptedWeapon::_apiGetPlayerY(){
    return player->getWorldPosition().y;
}

float ScriptedWeapon::_apiGetPlayerRotation(){
    return player->getWorldRotation();
}

float ScriptedWeapon::_apiGetPlayerFacing(){
    return getVectorAngleDegrees(player->getFacing());
}

float ScriptedWeapon::_apiGetCursorX(){
    return cursor->getWorldPosition().x;
}

float ScriptedWeapon::_apiGetCursorY(){
    return cursor->getWorldPosition().y;
}

void ScriptedWeapon::_apiCreateAmmoCasing(std::string path, float x, float y, float dx,
        float z, float dz, float az, double bounciness){
    std::shared_ptr<AmmoCasing> casing = std::make_shared<AmmoCasing>(path, sf::Vector2f{x,y}, dx,
            z, dz, az, bounciness, FRAMERATE*3);
    playfield->addThing(casing);
}

void ScriptedWeapon::_apiAddBullet(bool isFriendly, float x, float y, int damage,
        float vx, float vy, float lifetime, std::string path){
    std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(isFriendly, sf::Vector2f{x,y}, damage, sf::Vector2f{vx,vy}, FRAMERATE*lifetime);
    playfield->addThing(bullet);
}

void ScriptedWeapon::_apiCameraKick(float dir, float vel){
    camera.kick(dir, vel);
}

//!Handles when the player presses/releases the primary/secondary fire buttons.
void ScriptedWeapon::pressPrimaryFire(sf::Vector2f target){
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
    luabridge::LuaRef dummy = luabridge::getGlobal(_l, "tick");
    dummy();
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