#ifndef GRAPHICCORE_HH
# define GRAPHICCORE_HH
# include <iostream>
# include <SFML/Graphics.hpp>

class		GraphicCore
{
  sf::RenderWindow	*win;
  // menu
  // mini-map
  // perso
  // dialogue player
  // dialogue clans
  // triangle competences
public:
  GraphicCore();
  ~GraphicCore();

  void		start();
  void		loop();
};

#endif /* !GRAPHICCORE_HH */
