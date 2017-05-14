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

  sf::Texture *loadSprite(std::string) const;

 public:
  using moduleOutput = std::tuple<std::string, Consequence> *;

  GraphicCore();
  ~GraphicCore();

  void start();
  void loop();
  int menu();
  moduleOutput dispModule(Module<Text> const &);
};

#endif /* !GRAPHICCORE_HH */
