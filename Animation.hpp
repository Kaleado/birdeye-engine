#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "Render.hpp"

/**
  Class representing an animation that a Thing can display.
*/
class Animation {
public:
  /**
     Puts the next frame into a Sprite, returning whether the animation is finished or not.
     Returns false if the animation is finished, true otherwise.
  */
  bool getNextFrame(sf::Sprite& sprite);

  /**
     Returns whether the animation has finished running.
  */
  bool hasFinished();

  /**
     Sets the animation back to the start.
  */
  void reset();

  /**
     Pauses the animation at the current frame.
   */
  void pause();

  /**
     Continues the animation after pausing.
  */
  void resume();

  /**
     Sets the animation to be done.
  */
  void abort();
  
  Animation(std::vector<std::string> paths, bool isLooping=false, int frameRate=FRAMERATE) : _isLooping{isLooping}, _paths{paths}, _frameRate{frameRate} {
    unsigned int sz = _paths.size();
    _frames = std::vector<sf::Sprite>{sz};
    _textures = std::vector<sf::Texture>{sz};
  };
  Animation(){};
private:
  bool _isLooping;  
  bool _isLoaded=false;
  bool _isPaused=false;
  bool _isAborted=false;

  /**
     Loads all of the images associated with the animation.
  */
  int _load();
  
  /**
     Gets the number of frames in the animation.
  */
  int _getLength();

  
  int _curFrame=0;
  int _frameRate;  
  std::vector<sf::Sprite> _frames;
  std::vector<sf::Texture> _textures;
  std::vector<std::string> _paths;
};

#endif
