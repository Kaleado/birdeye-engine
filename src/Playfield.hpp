#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <algorithm>
#include "Thing.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "EnvironmentThing.hpp"

class ThingMarker;

/**
  Class representing a game area.
 */
class Playfield {
protected:
    //!Loads the overlay image for the level.
    int _loadOverlay();

    //!Draw the overlay of the level.
    void _drawOverlay(sf::RenderWindow& window);

    //!Loads the background image for the level.
    int _loadBackground();

    //!Draw the background of the level.
    void _drawBackground(sf::RenderWindow& window);

    //!Things currently on the screen - used for broadphase collision detection.
    std::vector<std::shared_ptr<Thing>> _thingsOnScreen;

    //!Returns a vector of Things that *might* be colliding.
    std::vector<std::shared_ptr<Thing>> _getPossiblyCollidingThings();

    //!Culls things that are flagged to be culled.
    void _cullThings();

    Camera _camera;

    //!Contains all game objects in the Playfield.
    std::vector<std::shared_ptr<Thing>> _things;

    //!Used with the sprite below.
    sf::Texture _overlayTexture;

    //!The current sprite (to be displayed) as the level overlay (like a filter).
    sf::Sprite _overlaySprite;

    //!The path to the overlay image for this level.
    std::string _overlayPath;

    //!Used with the sprite below.
    sf::Texture _backgroundTexture;

    //!The current sprite (to be displayed) of the level background.
    sf::Sprite _backgroundSprite;

    //!The path to the background image for this level.
    std::string _backgroundPath;

    //!Whether or not the background and other assets have been loaded
    //!for the level.
    bool _isLoaded=false;

    bool _cancelCollisionDetection=false;

public:
    void cancelCollisionDetection();

    //!Finds a marker containing the given ID. This assumes that the marker exists.
    std::shared_ptr<ThingMarker> findMarker(std::string id);

    //!Gets the boundary of the playfield.
    sf::FloatRect getBounds();

    //!Add a new thing to the playfield.
    void addThing(std::shared_ptr<Thing> thing);

    //!Draw everything in the playfield.
    void draw(sf::RenderWindow& window);

    //!Executed every frame. If you want to implement something
    //!particular to one map (like a global countdown or something), this
    //!is the place to implement that logic. You should subclass
    //!Playfield to do that.
    virtual void tick();

    //!Responds to a given event.
    virtual void handleInput(sf::Event event);

    //!Kick the camera in a given direction.
    void kickCamera(double angleDegrees, double strength);

    Playfield(){}

    //!This constructor loads a playfield from a file.
    Playfield(std::string playfieldPath);

};

extern std::shared_ptr<Playfield> playfield;
extern std::shared_ptr<Playfield> newPlayfield;

#endif
