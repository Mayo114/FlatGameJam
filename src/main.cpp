//
// main.cpp for FlatGameJam in /home/boulag_l/rendu/FlatGameJam/src
//
// Made by Luka Boulagnon
// Login   <luka.boulagnon@epitech.eu@epitech.net>
//
// Started on  sam. mai 13 14:41:16 2017 Luka Boulagnon
// Last update Sat May 13 22:03:05 2017 lacomm_m
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GraphicCore.hh"

int main(int argc, char *argv[])
{
  GraphicCore	gc;

  gc.start();
  gc.loop();
  return (0);
}
