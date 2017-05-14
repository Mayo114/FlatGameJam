#ifndef GRAPHICCORE_HH
#define GRAPHICCORE_HH

#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include "Module.hpp"

class GraphicCore {
  sf::RenderWindow *win;
  sf::VideoMode mode;
  // menu
  // mini-map
  // perso
  // dialogue player
  // dialogue clans
  // triangle competences
  
  sf::Sprite loadSprite(std::string) const;

 public:
  GraphicCore();
  ~GraphicCore();

  void start();
  void loop();
  int menu();
  void dispModule(Module<Text> const &);
};

#endif /* !GRAPHICCORE_HH */
