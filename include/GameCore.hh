#ifndef GAMECORE_HH
#define GAMECORE_HH

#include <map>
#include <memory>
#include <string>
#include <vector>
#include "GraphicCore.hh"
#include "Module.hpp"
#include "Timeline.hh"

class GameCore {
 public:
  GameCore();
  ~GameCore();
  int loadStory(std::string);
  void start();

 private:
  std::shared_ptr<IModule> head;
  std::map<std::string, std::shared_ptr<IModule>> storyLines;
  GraphicCore graphics;
  Timeline tl;
};

#endif /* !GAMECORE_HH */
