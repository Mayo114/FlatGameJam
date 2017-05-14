#include "Module.hpp"

Text::Text(YExcel::BasicExcelWorksheet* ws) {
  if (!ws) return;

  for (size_t i = 0; i < ws->GetTotalRows(); ++i) {
    YExcel::BasicExcelCell* cell = ws->Cell(i, 0);

    if (cell->Type() == YExcel::BasicExcelCell::STRING) {
      std::cout << cell->GetString() << std::endl;
    }
  }
}

Text& Text::setDefault() {
  Unit v_1 = {{"Bien, bien...Enfin maintenant que vous avez dit ça....j'avoue avoir bien envie de vous brosser!", {{"good", 10}, {"polite", 1}}},
	      {"Mal", {{"good", -10}, {"polite", 1}}},
	      {"...", {{"polite", -5}}}};

  this->scenario
      ["Bonjour, comment allez-vous ? Je vous demande car je suis poli, "
       "voyez-vous. Si ça ne tenais qu'à moi je vous ignorerais. Mais en "
       "suivant ce chemin, je ne pourrais jamais conquérir le monde...Dommage colatéraux voyez-vous!"] =
      v_1;

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
