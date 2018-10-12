#ifndef THING_H
#define THING_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <functional>
#include "Render.hpp"
#include "Animation.hpp"
#include "Camera.hpp"

/**
  Class representing an object in the game.
  Create actual objects by subclassing this.
 */
class Thing {
protected:
    //!The name for this thing.
    std::string _name;

    //!The path to the Thing's original sprite.
    std::string _path;

    //!Whether or not the Thing's image has been loaded - if false, it will load on the next frame.
    bool _isLoaded = false;

    //!Whether or not the Thing is currently displaying an animation instead of its usual image.
    bool _isAnimating = false;

    //!Used with the sprite.
    sf::Texture _texture;

    //!The current sprite (to be displayed) of the Thing.
    sf::Sprite _sprite;

    //!The _original_ sprite of the Thing. Displayed by default.
    sf::Sprite _originalSprite;

    //!Where the thing is in the playfield (i.e. its world position).
    sf::Vector2f _position;

    //!The direction the thing is facing in the playfield.
    sf::Vector2f _facing;

    //!Self-explanatory.
    sf::Vector2f _velocity;

    //!The direction the thing is facing, in _degrees_.
    double _rotation = 0;

    //!If this is true, this Thing should be culled (i.e. removed permanently) from the playfield.
    bool _cullMe = false;

    //!Loads the Thing's sprite.
    int _load();

    //!The current animation being played by the Thing.
    Animation _currentAnimation;

    //!The hitbox of the Thing if it were at (0,0).
    sf::FloatRect _hitboxAtZeroZero;
public:

    //!Returns the center of the sprite (in world coordinates)
    virtual sf::Vector2f getWorldCenter();

    //!Returns the center of the hitbox (in world coordinates)
    virtual sf::Vector2f getHitboxWorldCenter();

    //!Pushes Things away from one another so they don't crowd in one
    //!spot. This accepts a location rather than a Thing pointer so we
    //!can use it to prevent collisions with anything.
    void preventOverlapping(std::weak_ptr<Thing> otherThing, double strength);

    //!Does game-logic related things every frame. This is the core function that defines the behaviour of the game object.
    virtual void tick();

    //!Handles and responds to input every frame. The event is the event to respond to.
    virtual void handleInput(sf::Event event);

    //!Responds to (but does not check for) collisions every frame.
    virtual void handleCollision(std::weak_ptr<Thing> other);

    //!Play an animation in the current Thing.
    void playAnimation(Animation& animation);

    //!Remove the thing from the playfield.
    virtual void cull();

    //!Sets the thing's facing.
    void setFacing(sf::Vector2f facing);

    //!Sets the thing's rotation.
    void setRotation(double rotation);

    //!Gets the rotation of the thing.
    float getWorldRotation();

    //!Sets the colour to tint the thing.
    void setColor(sf::Color c);

    //!Returns whether the thing is to be imminently culled.
    bool isCulled();

    //!Gets a rectangle representing the bounding box (the hitbox) of the thing.
    virtual sf::FloatRect getBounds();

    //!Draw the thing on the screen.
    virtual void draw(sf::RenderWindow& window);

    //!Duh.
    void setXVelocity(float dx);
    void setYVelocity(float dy);
    void setVelocity(sf::Vector2f v);

    //!Gets the _world_ position of the thing - NOT THE SCREEN POSITION.
    sf::Vector2f getWorldPosition();

    //!Gets the position of the thing ON THE SCREEN (not the world position).
    sf::Vector2f getScreenPosition();

    //!Sets the _in-world_ position of the thing.
    void setWorldPosition(sf::Vector2f newPos);

    //! hitboxAtZeroZero is where the hitbox would be at position (0,0).
    Thing(Animation& anim, sf::Vector2f position, sf::FloatRect hitboxAtZeroZero) : _path{""}, _position{position}, _hitboxAtZeroZero{hitboxAtZeroZero} {
      _currentAnimation = anim;
      _isAnimating = true;
    };
    //! hitboxAtZeroZero is where the hitbox would be at position (0,0).
    Thing(std::string path, sf::Vector2f position, sf::FloatRect hitboxAtZeroZero) : _path{path}, _position{position}, _hitboxAtZeroZero{hitboxAtZeroZero} { };
    Thing(Animation& anim, sf::Vector2f position) : _path{""}, _position{position}, _hitboxAtZeroZero{0,0,0,0} {
      _currentAnimation = anim;
      _isAnimating = true;
    };
    Thing(std::string path, sf::Vector2f position) : _path{path}, _position{position}, _hitboxAtZeroZero{0,0,0,0} {};
    Thing(std::string path) : _path{path}, _position{0,0}, _hitboxAtZeroZero{0,0,0,0} {};
    Thing(){};
};

/**
  A class representing an ephemeral particle to be used when
  generating particle effects. In retrospect, I probably didn't need
  to subclass this from Thing, but if optimisation-related behaviour
  is to be added to particle effects specifically, we could implement
  them as part of this class.
 */
class Particle : public Thing {
protected:
public:
    virtual void tick() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    Particle(std::string path, sf::Vector2f position) : Thing(path, position) {};
    Particle(Animation& anim, sf::Vector2f position) : Thing(anim, position) {};
};

//!Represents an animation that plays and then vanishes.
class EphemeralAnimation : public Particle {
protected:
public:
    virtual void tick();
    virtual void draw(sf::RenderWindow& window);
    EphemeralAnimation(Animation& anim, sf::Vector2f position) : Particle(anim, position) {};
};

//!Represents an ammo casing particle expelled by a gun.
class AmmoCasing : public Particle {
private:
    int _lifetime;
    double _z;
    double _dz;
    double _az;
    double _bounciness;
public:
    virtual void tick();
    virtual void draw(sf::RenderWindow& window);
    AmmoCasing(std::string path, sf::Vector2f position, double dx,
               double z, double dz, double az, double bounciness, int lifetime) : Particle(path, position) {
      _name = "AmmoCasing";
      _velocity.x = dx;
      _z = z;
      _dz = dz;
      _az = az;
      _bounciness = bounciness;
      _lifetime = lifetime;
    };
    AmmoCasing(Animation& anim, sf::Vector2f position, double dx,
               double z, double dz, double az, double bounciness, int lifetime) : Particle(anim, position) {
      _name = "AmmoCasing";
      _velocity.x = dx;
      _z = z;
      _dz = dz;
      _az = az;
      _bounciness = bounciness;
      _lifetime = lifetime;
    };
};

#endif
