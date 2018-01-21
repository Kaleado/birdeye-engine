#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "Render.hpp"

/*
  Class representing an animation that a Thing can display.
*/
class Animation {
public:
  //Puts the next frame into a Sprite, returning whether the animation is finished or not.
  //Returns false if the animation is finished, true otherwise.
  bool getNextFrame(sf::Sprite& sprite);
  bool hasFinished(); 
  void reset();//Sets the animation back to the start.
  void pause();//Pauses the animation at the current frame.
  void resume();//Continues the animation after pausing.
  void abort();//Sets the animation to be done.
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
  int _load();
  int _getLength();
  int _curFrame=0;
  int _frameRate;
  std::vector<sf::Sprite> _frames;
  std::vector<sf::Texture> _textures;
  std::vector<std::string> _paths;
};

#endif
