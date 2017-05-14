#include <SFML/Graphics.hpp>
#include "GameCore.hh"

int main(int argc, char *argv[]) {
  GameCore gc;

  gc.loadStory("./assets/story/");
  gc.start();
  return (0);
}
