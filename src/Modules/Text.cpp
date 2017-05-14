#include "Module.hpp"

Text::Text(YExcel::BasicExcelWorksheet* ws)
    : scenario({{"toto", {{"oui", {{"toto", -1}}}, {"non", {{"toto", 1}}}}}}) {
  size_t i = 0;

  while (i) {
    YExcel::BasicExcelCell* cell = ws->Cell(i, 0);

    if (cell->Type() != YExcel::BasicExcelCell::STRING) break;
  }
}

Text& Text::setDefault() {
  Unit v_1 = {{"Bien", {{"good", 10}, {"polite", 1}}},
	      {"Mal", {{"good", -10}, {"polite", 1}}},
	      {"...", {{"polite", -5}}}};

  this->scenario["Bonjour, comment allez-vous ?"] = v_1;

  Unit v_2 = {{"C'est comme ça.", {{"polite", -1}}},
	      {"Il s'est passe quelque chose ce matin", {{"polite", 1}}}};

  this->scenario["Pourquoi donc ?"] = v_2;

  return *this;
}

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
}
