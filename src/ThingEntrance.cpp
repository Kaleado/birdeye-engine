#include "ThingEntrance.hpp"
#include "Playfield.hpp"
#include "Camera.hpp"

std::string ThingMarker::getId(){
    return _id;
}

sf::FloatRect ThingEntrance::getBounds(){
    auto camPos = camera.getPosition();
    return sf::FloatRect{_position.x - camPos.x, _position.y - camPos.y, _dimensions.x, _dimensions.y};
}

//Draw nothing, entrances are invisible.
void ThingEntrance::draw(sf::RenderWindow& window){
    return;
}

void ThingEntrance::handleCollision(std::weak_ptr<Thing> other){
    auto otherPtr = other.lock();
    if(!otherPtr){
        return;
    }
    std::shared_ptr<Player> asPlayer = std::dynamic_pointer_cast<Player>(otherPtr);
    if(asPlayer){
        // * vomits *
        newPlayfield = std::make_shared<Playfield>(_playfieldFile);
        newPlayfield ->addThing(player);
        //Update position here.
        auto marker = newPlayfield->findMarker(_destinationMarkerId);
        player->setWorldPosition(marker->getWorldPosition());
    }
}
