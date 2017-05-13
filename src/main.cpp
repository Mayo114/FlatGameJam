//
// main.cpp for FlatGameJam in /home/boulag_l/rendu/FlatGameJam/src
//
// Made by Luka Boulagnon
// Login   <luka.boulagnon@epitech.eu@epitech.net>
//
// Started on  sam. mai 13 14:41:16 2017 Luka Boulagnon
// Last update sam. mai 13 14:41:16 2017 Luka Boulagnon
//

#include <SFML/Graphics.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    window.clear();
    window.draw(shape);
    window.display();
  }

  return 0;
}
