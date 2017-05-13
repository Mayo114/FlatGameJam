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
	    this->win->close();
	    return ;
	  }
          if (event.type == sf::Event::Closed) this->win->close();
        }
      this->win->clear();
      this->win->display();
    }
}

//class Event
//Reaction
//Consequence

void		GraphicCore::dispModule(Module<Text> const & m)
{
  // getEvent --> dispEvent if not null

  // si action --> m.setReact(size_t);
  //
  // m.getCnsq() const;
}

void		GraphicCore::dialogPlayer() const
{
}

void		GraphicCore::dialogBoxes() const
{

}
