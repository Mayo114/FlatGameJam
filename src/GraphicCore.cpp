#include <GraphicCore.hh>

GraphicCore::GraphicCore() {}

GraphicCore::~GraphicCore() {}

void		GraphicCore::start()
{
  this->win = new sf::RenderWindow (sf::VideoMode(1024, 768, 32), "Skiving", sf::Style::Fullscreen);
}

void		GraphicCore::loop()
{
  while (this->win->isOpen())
    {
      sf::Event         event;
      while (this->win->pollEvent(event))
        {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	    {
	      std::cout << "In the if :)" << std::endl;
	      exit(0);
	    }
          if (event.type == sf::Event::Closed) this->win->close();
        }
      this->win->clear();
      this->win->display();
    }
}
