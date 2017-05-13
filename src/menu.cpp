//
// main.cpp for cpp_arcade in /home/rougag_b/rendu/cpp_arcade/src/sfml
// 
// Made by Boris ROUGAGNOU
// Login   <rougag_b@epitech.net>
// 
// Started on  Sat Apr  8 18:27:17 2017 Boris ROUGAGNOU
// Last update Sat May 13 22:33:41 2017 Boris ROUGAGNOU
//

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp> 

//using namespace std;
//using namespace sf;

int	menu()
{
  sf::Texture		t_background;
  sf::Sprite		s_background;
  sf::Texture		t_title;
  sf::Sprite		s_title;
  sf::Texture		t_play;
  sf::Sprite		s_play;
  sf::Texture		t_exit;
  sf::Sprite		s_exit;


  if (!t_background.loadFromFile("./assets/menu/background.jpg") ||
      !t_title.loadFromFile("./assets/ui/skiving_title.png") ||
      !t_play.loadFromFile("./assets/weapons/axe.png") ||
      !t_exit.loadFromFile("./assets/menu/quit.png"))
    {
      std::cout << "impossible open asset file" << std::endl;
      return (0);
    }
      t_title.setSmooth(false);
      s_title.setTexture(t_title);
      t_background.setSmooth(true);
      s_background.setTexture(t_background);
      // on nettoie l ecran
      app.clear(sf::Color(0, 0, 0));

      app.draw(s_background);
      app.draw(s_title);
      // app.draw(play);
      // app.draw(exit);
      app.display();
    }

  return (0);
}
