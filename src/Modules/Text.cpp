#include <iostream>
#include <sstream>
#include "Module.hpp"
#include "csv.h"

Text::Text(std::string const& file) {
  size_t i = 0;
  size_t k;
  int cons = 0;
  std::string event;
  std::vector<std::string> reactions;
  EventAction<std::string> ea;

  if (!file.size() || file[16] == '.') throw io::error::can_not_open_file();
  io::CSVReader<4, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '"'>>
      csv(file);
  std::string line;
  this->f = file;

  while (reactions.resize(3),
	 csv.read_row(event, reactions[0], reactions[1], reactions[2])) {
    std::vector<std::string> segments;
    std::string segment;

    if (cons) {
      for (int l = 0; l < cons; ++l) {
	Consequence c;
	std::stringstream ss(reactions[l]);
	while (std::getline(ss, segment, ';')) {
	  std::stringstream spaces(segment);
	  std::string key;
	  std::string value;

	  spaces >> key;
	  std::transform(key.begin(), key.end(), key.begin(), ::tolower);

	  spaces >> value;
	  std::transform(value.begin(), value.end(), value.begin(), ::tolower);
	  c[key] = value;
	}
	ea.cons.push_back(c);
      }
      events.push_back(ea);
      ea = EventAction<std::string>();
      reactions.resize(0);
      cons = false;
    } else {
      std::stringstream ss(event);
      while (std::getline(ss, segment, ';')) {
	segments.push_back(segment);
      }
      if (segments.size() < 3) continue;
      ea.actor = segments[0];
      ea.actorAsset = segments[0] + ".png";
      ea.action = segments[2];

      for (k = 0; k < 3 && segments[k].size(); ++k)
	;
      reactions.resize(k);
      ea.reactions = reactions;
      ea.line = i;

      cons = k;
    }
    ++i;
  }
}

/*
Text& Text::setDefault() {
  Unit v_1 = {{"Bien, bien...Enfin maintenant que vous avez dit ça....j'avoue
avoir bien envie de vous brosser!", {{"good", 10}, {"polite", 1}}},
	      {"Mal", {{"good", -10}, {"polite", 1}}},
	      {"...", {{"polite", -5}}}};

  this->scenario
      ["Bonjour, comment allez-vous ? Je vous demande car je suis poli, "
       "voyez-vous. Si ça ne tenais qu'à moi je vous ignorerais. Mais en "
       "suivant ce chemin, je ne pourrais jamais conquérir le monde...Dommage
colatéraux voyez-vous!"] =
      v_1;

  Unit v_2 = {{"C'est comme ça.", {{"polite", -1}}},
	      {"Il s'est passe quelque chose ce matin", {{"polite", 1}}}};

  this->scenario["Pourquoi donc ?"] = v_2;

  return *this;
}
*/

/*
Text& Text::setEvents() {
  for (auto i = this->scenario.cbegin(); i != this->scenario.cend(); ++i) {
    EventAction<EventType> ea;
    std::vector<std::string> reactions;

    for (auto j = i->second.cbegin(); j != i->second.cend(); ++j) {
      reactions.push_back(j->first);
    }

    ea.action = i->first;
    ea.reactions = reactions;
    this->events.push_back(ea);
  }
  return *this;
}*/
