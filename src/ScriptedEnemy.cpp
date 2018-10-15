#include <utility>

//
// Created by kaleado on 14/10/18.
//

#include "ScriptedEnemy.hpp"

void ScriptedEnemy::_initScript(){
    _l = luaL_newstate();
    luaL_openlibs(_l);
    luabridge::getGlobalNamespace(_l)
        .beginClass<ScriptedEnemy>("Enemy")
            .addProperty("position", &ScriptedEnemy::_apiGetPosition, &ScriptedEnemy::_apiSetPosition)
            .addProperty("velocity", &ScriptedEnemy::_apiGetVelocity, &ScriptedEnemy::_apiSetVelocity)
            .addFunction("getVectorToPlayer", &ScriptedEnemy::_apiGetVectorToPlayer)
            .addFunction("getDistanceFromPlayer", &ScriptedEnemy::_apiGetDistanceFromPlayer)
            .addFunction("finishedAnimation", &ScriptedEnemy::_apiFinishedAnimation)
            .addFunction("stopAnimation", &ScriptedEnemy::_apiStopAnimation)
            .addFunction("startAnimation", &ScriptedEnemy::_apiStartAnimation)
            .addFunction("setAnimation", &ScriptedEnemy::_apiSetAnimation)
            .addStaticFunction("addBullet", &ScriptedEnemy::_apiAddBullet)
        .endClass()
        .beginClass<sf::Vector2f>("Vector")
            .addConstructor<void(*)(float, float)>()
            .addProperty("x", &Vector2fHelper::getX, &Vector2fHelper::setX)
            .addProperty("y", &Vector2fHelper::getY, &Vector2fHelper::setY)
        .endClass();
    luabridge::setGlobal(_l, this, "enemy");
    luaL_dofile(_l, _script.c_str());
}

sf::Vector2f ScriptedEnemy::_apiGetPosition() const {
    return this->getWorldPosition();
}

sf::Vector2f ScriptedEnemy::_apiGetVelocity() const {
    return this->_velocity;
}

void ScriptedEnemy::_apiSetPosition(sf::Vector2f pos){
    this->setWorldPosition(pos);
}

void ScriptedEnemy::_apiSetVelocity(sf::Vector2f vel){
    _velocity = vel;
//    std::cout << _velocity.x << " " << _velocity.y << "\n";
}

float ScriptedEnemy::_apiGetDistanceFromPlayer(){
    return static_cast<float>(_getDistanceFromPlayer());
}

sf::Vector2f ScriptedEnemy::_apiGetVectorToPlayer(){
    return getUnitVectorBetween(this->getWorldPosition(), player->getWorldPosition());
}

void ScriptedEnemy::_apiAddBullet(bool isFriendly, float x, float y, int damage,
                                   float vx, float vy, float lifetime, std::string path){
    std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(isFriendly, sf::Vector2f{x,y}, damage, sf::Vector2f{vx,vy}, FRAMERATE*lifetime);
    playfield->addThing(bullet);
}

bool ScriptedEnemy::_apiFinishedAnimation(){
    return this->_currentAnimation.hasFinished();
}

void ScriptedEnemy::_apiStartAnimation(){
    this->_isAnimating = true;
}

void ScriptedEnemy::_apiStopAnimation(){
    this->_isAnimating = false;
}

void ScriptedEnemy::_apiSetAnimation(luabridge::LuaRef listOfFramePaths, bool isLooping, int frameRate){
    auto length = static_cast<unsigned long>(listOfFramePaths.length());
    std::vector<std::string> paths = {};
    paths.reserve(length);
    for(int i = 1; i < length; ++i){
        paths.push_back(listOfFramePaths[i]);
    }
    this->_currentAnimation = Animation(paths, isLooping, frameRate);
}

//!Executed every frame when the creature's state is ES_IDLE.
void ScriptedEnemy::_whenIdle(){
    luabridge::LuaRef func = luabridge::getGlobal(_l, "whenIdle");
    func();
}

//!Executed every frame when the creature's state is ES_AGGRO.
void ScriptedEnemy::_whenAggro(){
    luabridge::LuaRef func = luabridge::getGlobal(_l, "whenAggro");
    func();
}

//!Executed every frame when the creature's state is ES_ATTACKING.
void ScriptedEnemy::_whenAttacking(){
    luabridge::LuaRef func = luabridge::getGlobal(_l, "whenAttacking");
    func();
}

//!Executed when the creature collides with something - this is for enemy-specific logic.
void ScriptedEnemy::_whenCollidingWith(std::weak_ptr<Thing> other){
    luabridge::LuaRef func = luabridge::getGlobal(_l, "whenCollidingWith");
    //TODO: how to pass another Thing in as a pointer?
    func();
}

//!Executed every tick the creature is alive for.
void ScriptedEnemy::_whenTick(){
    luabridge::LuaRef func = luabridge::getGlobal(_l, "whenTick");
    func();
}

//!Executed when the creature dies.
void ScriptedEnemy::_whenKilled(){
    luabridge::LuaRef func = luabridge::getGlobal(_l, "whenKilled");
    func();
}

//!Executed when the creature takes damage.
void ScriptedEnemy::_whenDamaged(int amt){
    luabridge::LuaRef func = luabridge::getGlobal(_l, "whenDamaged");
    func(amt);
}

ScriptedEnemy::ScriptedEnemy(std::array<std::string, FACING_MAX> facingPaths, sf::Vector2f position, int maxHp,
        sf::FloatRect hitboxAtZeroZero, std::string script) : Enemy(std::move(facingPaths), position, maxHp, hitboxAtZeroZero) {
    _script = std::move(script);
    _initScript();
}