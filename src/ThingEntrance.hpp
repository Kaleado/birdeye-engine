#ifndef THING_ENTRANCE_HPP
#define THING_ENTRANCE_HPP

#include "Thing.hpp"
#include "Playfield.hpp"

//!Represents a point in the playfield, with a unique ID.
class ThingMarker : public Thing {
public:
  //!Retrieves the marker's ID.
  std::string getId();

  ThingMarker(sf::Vector2f position, std::string id) : Thing("", position) {
    _id = id;
  }

protected:
  //!The unique ID identifying this marker.
  std::string _id;

};

class ThingEntrance : public Thing {
public:
  //!Gets a rectangle representing the bounding box (the hitbox) of the thing.
  virtual sf::FloatRect getBounds();

  //!Draw nothing.
  virtual void draw(sf::RenderWindow& window);

  //!Move the player to the new map.
  void handleCollision(std::weak_ptr<Thing> other);

  ThingEntrance(sf::Vector2f position, sf::Vector2f dimensions,
                std::string playfieldFile, std::string destinationMarkerId) : Thing("", position){
    _dimensions = dimensions;
    _playfieldFile = playfieldFile;
    _destinationMarkerId = destinationMarkerId;
  }
protected:
  //!The size of the entrance.
  sf::Vector2f _dimensions;

  //!The destination playfield file.
  std::string _playfieldFile;

  //!The unique ID identifying this entrance.
  std::string _destinationMarkerId;

};

#endif
