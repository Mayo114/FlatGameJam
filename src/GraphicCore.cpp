#include <GraphicCore.hh>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

GraphicCore::GraphicCore() {}

GraphicCore::~GraphicCore() {}

void GraphicCore::start() {
  this->win = new sf::RenderWindow(sf::VideoMode(1024, 768, 32), "Skiving",
				   sf::Style::Fullscreen);
}

int GraphicCore::menu() {
  sf::RenderTexture background;
  sf::Texture t_background;
  sf::Sprite s_background;
  sf::Texture t_title;
  sf::Sprite s_title;
  sf::Texture t_play;
  sf::Sprite s_play;
  sf::Texture t_exit;
  sf::Sprite s_exit;

  if (!t_background.loadFromFile("./assets/menu/background.jpg") ||
      !t_title.loadFromFile("./assets/menu/skiving_title.png") ||
      !t_play.loadFromFile("./assets/menu/play.png") ||
      !t_exit.loadFromFile("./assets/menu/quit.png")) {
    std::cout << "impossible open asset file" << std::endl;
    return (0);
  }
  t_title.setSmooth(false);
  s_title.setTexture(t_title);
  t_background.setSmooth(true);
  s_background.setTexture(t_background);
  t_play.setSmooth(true);
  s_play.setTexture(t_play);
  t_exit.setSmooth(false);
  s_exit.setTexture(t_exit);
  background.clear(sf::Color(0, 0, 0));
  background.draw(s_background);
  background.draw(s_title);
  background.draw(s_play);
  background.draw(s_exit);
  while (this->win->isOpen()) {
    sf::Event event;
    while (this->win->pollEvent(event)) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ||
	  event.type == sf::Event::Closed) {
	this->win->close();
	return -1;
      }
    }
    this->win->clear();
    this->win->draw(sf::Sprite(background.getTexture()));
    this->win->display();
  }
  return -1;
}

void GraphicCore::loop() {
  while (this->win->isOpen()) {
    sf::Event event;
    while (this->win->pollEvent(event)) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
	std::cout << "In the if :)" << std::endl;
	exit(0);
      }
      if (event.type == sf::Event::Closed) this->win->close();
    }
    this->win->clear();
    this->win->display();
  }
}
