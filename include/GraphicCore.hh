#ifndef GRAPHICCORE_HH
#define GRAPHICCORE_HH
#include <SFML/Graphics.hpp>
#include <iostream>

class GraphicCore {
  sf::RenderWindow *win;
  // menu
  // mini-map
  // perso
  // dialogue player
  // dialogue clans
  // triangle competences
 public:
  GraphicCore();
  ~GraphicCore();

  void start();
  void loop();
  int menu();
};

#endif /* !GRAPHICCORE_HH */
