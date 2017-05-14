#ifndef GRAPHICCORE_HH
#define GRAPHICCORE_HH

#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include "Module.hpp"

class GraphicCore {
  sf::RenderWindow *win;
  sf::VideoMode mode;
  sf::Texture *loadSprite(std::string) const;

 public:
  using moduleOutput = std::tuple<std::string, Consequence> *;

  GraphicCore();
  ~GraphicCore();

  sf::String wrapText(sf::String, unsigned int, const sf::Font &, unsigned int,
		      bool);
  void start();
  void loop();
  int menu();
  moduleOutput dispModule(Module<Text> &);
};

#endif /* !GRAPHICCORE_HH */
