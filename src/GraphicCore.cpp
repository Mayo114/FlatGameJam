#include "GraphicCore.hh"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>

GraphicCore::GraphicCore() : mode(1920, 1080, 32) {}

GraphicCore::~GraphicCore() {
  if (this->win->isOpen()) this->win->close();
  delete this->win;
}

void GraphicCore::start() {
  if (!mode.isValid()) {
    mode = mode.getFullscreenModes()[0];
  }
  this->win = new sf::RenderWindow(mode, "Skiving",
				   sf::Style::Fullscreen | sf::Style::Close);
  this->win->setFramerateLimit(60);
  this->win->setVerticalSyncEnabled(true);
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
	exit(0);
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
	this->win->close();
	return;
      }
      if (event.type == sf::Event::Closed) {
	exit(0);
      }
    }
    this->win->clear();
    this->win->display();
  }
}

sf::Texture* GraphicCore::loadSprite(std::string file) const {
  sf::Texture* t_image = new sf::Texture();

  if (!t_image->loadFromFile("./assets/" + file)) {
    std::cerr << "Missing asset " << file << std::endl;
    this->win->close();
    exit(1);
  }
  t_image->setSmooth(true);
  return (t_image);
}

GraphicCore::moduleOutput GraphicCore::dispModule(Module<Text> const& module) {
  std::unique_ptr<sf::Texture> bgTexture(
      this->loadSprite("modules/default.png"));
  std::unique_ptr<sf::Texture> figureTexture(
      this->loadSprite("figures/viking.png"));
  sf::Sprite bgSprite;
  sf::Sprite figureSprite;

  bgSprite.setTexture(*bgTexture);
  bgSprite.setScale(this->mode.width / bgSprite.getLocalBounds().width,
		    this->mode.height / bgSprite.getLocalBounds().height);
  figureSprite.setTexture(*figureTexture);
  figureSprite.setScale(
      this->mode.height * 0.7 / figureSprite.getLocalBounds().height,
      this->mode.height * 0.7 / figureSprite.getLocalBounds().height);
  figureSprite.setPosition(sf::Vector2f(
      ((this->mode.width - figureSprite.getLocalBounds().width - 100)),
      this->mode.height - figureSprite.getLocalBounds().height));

  while (this->win->isOpen()) {
    sf::Event event;

    this->win->draw(bgSprite);
    this->win->draw(figureSprite);
    this->win->display();
    while (this->win->pollEvent(event)) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
	return NULL;
      }
      if (event.type == sf::Event::Closed) {
	this->win->close();
	return (GraphicCore::moduleOutput)-1;
      }
    }
  }
}
