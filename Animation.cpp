#include "Animation.hpp"

//Loads the animation's frames.
int Animation::_load(){
  for(int s = 0; s < _paths.size(); ++s){
    if(_paths[s] == ""){continue;}
    if(!_textures[s].loadFromFile(_paths[s])){
      _isLoaded = false;
      return 1;
    }
    _frames[s].setTexture(_textures[s]);
  }
  _isLoaded = true;
}

//Returns the number of frames in the animation.
int Animation::_getLength(){
  return _paths.size();
}

/*
  This function returns false if there are no more frames to play.
 */
bool Animation::getNextFrame(sf::Sprite& sprite){
  if(hasFinished()){
    return false;
  }
  if(_curFrame >= _getLength() && _isLooping){
    _curFrame=0;
  }
  if(!_isLoaded){
    _load();
  }
  static int frameCounter = 0;
  //We proceed to the next frame based on the framerate.
  if(frameCounter++ < FRAMERATE/_frameRate){
    sprite = _frames[_curFrame];
    return true;
  }
  frameCounter = 0;
  sprite = _frames[_curFrame];
  _curFrame++;
  return true;
}

void Animation::reset(){
  _curFrame = 0;
}

void Animation::pause(){
  _isPaused = true;
}

//Stop the animation and terminate it.
void Animation::abort(){
  _isAborted = true;
}

bool Animation::hasFinished(){
  return _isAborted || (_curFrame >= _getLength() && !_isLooping);
}
