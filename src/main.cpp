//
// main.cpp for FlatGameJam in /home/boulag_l/rendu/FlatGameJam/src
//
// Made by Luka Boulagnon
// Login   <luka.boulagnon@epitech.eu@epitech.net>
//
// Started on  sam. mai 13 14:41:16 2017 Luka Boulagnon
// Last update Sat May 13 16:32:35 2017 Boris ROUGAGNOU
//

#include <iostream>
#include <SFML/Graphics.hpp>

int main(int argc, char *argv[])
{
  sf::RenderWindow	window(sf::VideoMode(1024, 768, 32), "Skiving", sf::Style::Fullscreen);
  sf::CircleShape	shape(100.f);

  shape.setFillColor(sf::Color::Green);
  while (window.isOpen())
    {
      sf::Event		event;
      while (window.pollEvent(event))
	{
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	    exit(0);
	  if (event.type == sf::Event::Closed) window.close();
	}
      window.clear();
      window.draw(shape);
      window.display();
    }
  return (0);
}
