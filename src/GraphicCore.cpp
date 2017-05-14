#include "GraphicCore.hh"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

GraphicCore::GraphicCore() : mode(1920, 1080, 32) {}

GraphicCore::~GraphicCore() {}

void GraphicCore::start() {
  if (!mode.isValid()) {
    mode = mode.getFullscreenModes()[0];
  }
  this->win = new sf::RenderWindow(mode, "Skiving",
				   sf::Style::Fullscreen | sf::Style::Close);
}

// void Button::eventMouse(sf::Event * event, sf::RenderWindow * window)
// {
//   sf::FloatRect	mousePosition(event->mouseButton.x,
// 			      event->mouseButton.y, 1, 1);

//   if(m_spriteButton.getGlobalBounds().intersects(mousePosition))
//     std::cout << "Yes!" << std::endl;
// }

int GraphicCore::menu() {
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

  // centrer une image sur un écran: ((res écran - res image) / 2)
  // ajouter image au bout de l'écran - 10: (res écran - (res image + 10))
  //  s_title.setTextureRect(sf::IntRect(250, 500, 500, 100));
  s_background.setScale(
      this->mode.width / s_background.getLocalBounds().width,
      this->mode.height / s_background.getLocalBounds().height);
  s_title.setPosition(sf::Vector2f(((this->mode.width - 848) / 2), 10));

  //  s_play.setTextureRect(sf::IntRect(250, 200, 500, 100));
  s_play.setPosition(sf::Vector2f(10, (this->mode.height - (512 + 10))));

  // s_exit.setTextureRect(sf::IntRect(250, 350, 500, 100));
  s_exit.setPosition(sf::Vector2f((this->mode.width - (512 + 10)),
				  (this->mode.height - (512 + 10))));

  while (this->win->isOpen()) {
    sf::Event event;
    while (this->win->pollEvent(event)) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ||
	  event.type == sf::Event::Closed) {
	this->win->close();
	return -1;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) return 1;
    }
    this->win->clear(sf::Color(0, 0, 0));
    this->win->draw(s_background);
    this->win->draw(s_title);
    this->win->draw(s_play);
    this->win->draw(s_exit);
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

sf::Sprite	GraphicCore::loadSprite(std::string file) const {
  sf::Texture	t_image;
  sf::Sprite	s_image;

  if (!t_image.loadFromFile("./assets/modules/" + file))
  {
    std::cerr << "Missing asset " << file << std::endl;
    this->win->close();
    exit(1);
  }
  t_image.setSmooth(true);
  s_image.setTexture(t_image);
  return (s_image);
}

void		GraphicCore::dispModule(Module<Text> const & module) {
  sf::Sprite	bgSprite = this->loadSprite("default.png");

  while (this->win->isOpen()) {
    //if ((text = module.getEvent()) != NULL)
      //dispEvent(text);
    this->win->draw(bgSprite);
    this->win->display();
  }
}
