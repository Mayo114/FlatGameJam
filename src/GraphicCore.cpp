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

  // centrer une image sur un ecran: ((res écran - res image) / 2)
  // ajouter image au bout de l ecran - 10: (res écran - (res image + 10))
  //  s_title.setTextureRect(sf::IntRect(250, 500, 500, 100));
  // setScale: redimentionne l image
  s_background.setScale(
      this->mode.width / s_background.getLocalBounds().width,
      this->mode.height / s_background.getLocalBounds().height);
  s_title.setPosition(sf::Vector2f(
      ((this->mode.width - s_title.getLocalBounds().width) / 2), 120));

  s_exit.setScale((0.3), (0.3));
  s_exit.setPosition(sf::Vector2f(
      70, (this->mode.height - ((s_play.getLocalBounds().height * 0.3) + 70))));

  s_play.setScale((0.3), (0.3));
  s_play.setPosition(sf::Vector2f(
      (this->mode.width - ((s_exit.getLocalBounds().width * 0.3) + 70)),
      (this->mode.height - ((s_exit.getLocalBounds().height * 0.3) + 70))));

  while (this->win->isOpen()) {
    sf::Event event;
    while (this->win->pollEvent(event)) {
      if ((event.type == sf::Event::KeyReleased &&
	   event.key.code == sf::Keyboard::Escape) ||
	  event.type == sf::Event::Closed) {
	this->win->close();
	exit(0);
      }
      if (event.type == sf::Event::MouseButtonReleased &&
	  event.mouseButton.button == sf::Mouse::Button::Left) {
	if (event.mouseButton.x > s_play.getPosition().x &&
	    event.mouseButton.x <
		s_play.getPosition().x + 0.3 * s_play.getLocalBounds().width &&
	    event.mouseButton.y > s_play.getPosition().y &&
	    event.mouseButton.y <
		s_play.getPosition().y + 0.3 * s_play.getLocalBounds().height)
	  return 1;
	if (event.mouseButton.x > s_exit.getPosition().x &&
	    event.mouseButton.x <
		s_exit.getPosition().x + 0.3 * s_exit.getLocalBounds().width &&
	    event.mouseButton.y > s_exit.getPosition().y &&
	    event.mouseButton.y <
		s_exit.getPosition().y + 0.3 * s_exit.getLocalBounds().height) {
	  this->win->close();
	  exit(0);
	}
      }
      if (event.type == sf::Event::KeyReleased &&
	  event.key.code == sf::Keyboard::Return)
	return 1;
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
      if ((event.type == sf::Event::KeyReleased &&
	   event.key.code == sf::Keyboard::Escape) ||
	  event.type == sf::Event::Closed) {
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

sf::String GraphicCore::wrapText(sf::String string, unsigned width,
				 const sf::Font& font, unsigned charicterSize,
				 bool bold = false) {
  unsigned currentOffset = 0;
  bool firstWord = true;
  std::size_t wordBegining = 0;

  for (std::size_t pos(0); pos < string.getSize(); ++pos) {
    auto currentChar = string[pos];
    if (currentChar == '\n') {
      currentOffset = 0;
      firstWord = true;
      continue;
    } else if (currentChar == ' ') {
      wordBegining = pos;
      firstWord = false;
    }

    auto glyph = font.getGlyph(currentChar, charicterSize, bold);
    currentOffset += glyph.advance;

    if (!firstWord && currentOffset > width) {
      pos = wordBegining;
      string[pos] = '\n';
      firstWord = true;
      currentOffset = 0;
    }
  }

  return string;
}

GraphicCore::moduleOutput GraphicCore::dispModule(Module<Text>* module) {
  std::unique_ptr<sf::Texture> bgTexture(
      this->loadSprite("modules/default.png"));
  std::unique_ptr<sf::Texture> figureTexture(
      this->loadSprite("figures/viking.png"));
  sf::Sprite bgSprite;
  sf::Sprite figureSprite;
  sf::Font font;

  if (!font.loadFromFile("./assets/modules/fonts.ttf")) {
    std::cerr << "Missing asset ./assets/modules/fonts.ttf" << std::endl;
    exit(1);
  }
  bgSprite.setTexture(*bgTexture);
  bgSprite.setScale(this->mode.width / bgSprite.getLocalBounds().width,
		    this->mode.height / bgSprite.getLocalBounds().height);
  figureSprite.setTexture(*figureTexture);

  {
    float scale =
	this->mode.width * 4 / 12 / figureSprite.getLocalBounds().height;
    figureSprite.setScale(scale, scale);
    figureSprite.setPosition(sf::Vector2f(
	this->mode.width - figureSprite.getLocalBounds().width * scale - 30,
	this->mode.height - figureSprite.getLocalBounds().height * scale));
  }

  sf::RectangleShape dialogActor(
      sf::Vector2f(this->mode.width / 12 * 8, this->mode.height / 16 * 5));
  dialogActor.setPosition(
      sf::Vector2f(this->mode.height / 16, this->mode.height / 16 * 2));

  sf::RectangleShape dialogPlayer(
      sf::Vector2f(this->mode.width / 12 * 7, this->mode.height / 16 * 5));
  dialogPlayer.setPosition(
      sf::Vector2f(this->mode.height / 16, this->mode.height / 16 * 10));

  EventAction<Text::EventType> ea;
  sf::Text text;
  try {
    ea = module->getEvent();
  } catch (int err) {
    return NULL;
  }
  text.setFont(font);
  {
    std::basic_string<sf::Uint32> utf32str;
    sf::Utf8::toUtf32(ea.action.begin(), ea.action.end(),
		      std::back_inserter(utf32str));
    sf::String sfstr = utf32str;
    sfstr = GraphicCore::wrapText(sfstr, this->mode.width / 12 * 7, font, 33,
				  false);
    text.setString(sfstr);
  }
  text.setCharacterSize(33);
  text.setColor(sf::Color::Black);
  text.setPosition(this->mode.height / 16 + 60,
		   this->mode.height / 16 * 2 + 40);

  std::vector<sf::Text*> choices;
  unsigned int selected = 0;
  int j = 0;
  {
    int nbLines = 0;

    for (auto it = ea.reactions.cbegin(); it != ea.reactions.cend(); ++it) {
      if (it->size() <= 1) continue;
      choices.push_back(new sf::Text());

      choices[j]->setPosition(this->mode.height / 16 + 60,
			      this->mode.height / 16 * 10 + 40 + nbLines * 45);
      choices[j]->setFont(font);
      {
	std::basic_string<sf::Uint32> utf32str;
	sf::Utf8::toUtf32(it->begin(), it->end(), std::back_inserter(utf32str));
	sf::String sfstr = utf32str;
	sfstr =
	    GraphicCore::wrapText(sfstr, this->mode.width / 2, font, 33, false);
	choices[j]->setString(sfstr);
	for (size_t i = 0; i < sfstr.getSize(); ++i) {
	  if (sfstr[i] == '\n') ++nbLines;
	}
      }
      choices[j]->setCharacterSize(33);
      choices[j]->setColor(sf::Color::Black);
      ++j;
      ++nbLines;
    }
  }

  while (this->win->isOpen()) {
    sf::Event event;

    this->win->draw(bgSprite);
    this->win->draw(figureSprite);
    this->win->draw(dialogActor);
    this->win->draw(dialogPlayer);
    this->win->draw(text);

    sf::FloatRect backgroundRect = choices[selected]->getLocalBounds();
    sf::RectangleShape backg(
	sf::Vector2f(backgroundRect.width + 20, backgroundRect.height + 20));
    backg.setFillColor(sf::Color::Black);
    for (int i = 0; i < j; ++i) choices[i]->setColor(sf::Color::Black);
    choices[selected]->setColor(sf::Color::White);
    this->win->draw(backg, choices[selected]->getTransform());
    for (auto it = choices.cbegin(); it != choices.cend(); ++it)
      this->win->draw(**it);
    this->win->display();

    while (this->win->pollEvent(event)) {
      if ((event.type == sf::Event::KeyReleased &&
	   event.key.code == sf::Keyboard::Escape) ||
	  event.type == sf::Event::Closed) {
	return NULL;
      }
      if (event.type == sf::Event::KeyReleased &&
	  event.key.code == sf::Keyboard::Up) {
	if (selected == 0)
	  selected = j - 1;
	else
	  --selected;
      }
      if (event.type == sf::Event::KeyReleased &&
	  event.key.code == sf::Keyboard::Down) {
	++selected;
      }
      selected %= j;
      if (event.type == sf::Event::KeyReleased &&
	  event.key.code == sf::Keyboard::Return) {
	module->setReact(selected);
	std::cout << "tol" << std::endl;
	try {
	  ea = module->getEvent();
	} catch (int err) {
	  return NULL;
	}
	std::cout << "total" << std::endl;
	{
	  std::basic_string<sf::Uint32> utf32str;
	  sf::Utf8::toUtf32(ea.action.begin(), ea.action.end(),
			    std::back_inserter(utf32str));
	  sf::String sfstr = utf32str;
	  sfstr = GraphicCore::wrapText(sfstr, this->mode.width / 12 * 7, font,
					33, false);
	  text.setString(sfstr);
	}

	int nbLines = 0;
	j = 0;
	selected = 0;

	choices.resize(0);
	for (auto it = ea.reactions.cbegin(); it != ea.reactions.cend(); ++it) {
	  if (it->size() <= 1) continue;
	  choices.push_back(new sf::Text());

	  choices[j]->setPosition(
	      this->mode.height / 16 + 60,
	      this->mode.height / 16 * 10 + 40 + nbLines * 45);
	  choices[j]->setFont(font);
	  {
	    std::basic_string<sf::Uint32> utf32str;
	    sf::Utf8::toUtf32(it->begin(), it->end(),
			      std::back_inserter(utf32str));
	    sf::String sfstr = utf32str;
	    sfstr = GraphicCore::wrapText(sfstr, this->mode.width / 2, font, 33,
					  false);
	    choices[j]->setString(sfstr);
	    for (size_t i = 0; i < sfstr.getSize(); ++i) {
	      if (sfstr[i] == '\n') ++nbLines;
	    }
	  }
	  choices[j]->setCharacterSize(33);
	  choices[j]->setColor(sf::Color::Black);
	  ++j;
	  ++nbLines;
	}
      }
      if (event.type == sf::Event::Closed) {
	this->win->close();
	return (GraphicCore::moduleOutput)-1;
      }
    }
  }
}
