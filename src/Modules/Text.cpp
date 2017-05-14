#include "Module.hpp"

Text::Text(YExcel::BasicExcelWorksheet const* ws) {}

Text& Text::setDefault() {
  std::tuple<std::string, Consequence> e1_1;
  std::get<0>(e1_1) = "Bien";
  std::get<1>(e1_1) = {{"good", 10}, {"polite", 1}};

  std::tuple<std::string, Consequence> e2_1;
  std::get<0>(e2_1) = "Mal";
  std::get<1>(e2_1) = {{"good", -10}, {"polite", 1}};

  std::tuple<std::string, Consequence> e3_1;
  std::get<0>(e3_1) = "...";
  std::get<1>(e3_1) = {{"polite", -5}};

  std::vector<std::tuple<std::string, Consequence>> v_1 = {e1_1, e2_1, e3_1};
  Unit u("Bonjour, comment allez-vous ?", v_1);

  std::tuple<std::string, Consequence> e1_2;
  std::get<0>(e1_2) = "C'est comme ça.";
  std::get<1>(e1_2) = {{"polite", -1}};

  std::tuple<std::string, Consequence> e2_2;
  std::get<0>(e2_2) = "Il s'est passé quelque chose ce matin";
  std::get<1>(e2_2) = {{"polite", 1}};

  std::vector<std::tuple<std::string, Consequence>> v_2 = {e1_2, e2_2};
  Unit u_2("Pourquoi donc ?", v_2);

  this->scenario = {u, u_2};
  return *this;
}

Text& Text::setEvents() {
  for (auto i = this->scenario.cbegin(); i != this->scenario.cend(); ++i) {
    EventAction<EventType> ea;
    std::vector<std::string> reactions;

    for (auto j = std::get<1>(*i).cbegin(); i != this->scenario.cend(); ++i) {
      reactions.push_back(std::get<0>(*j));
    }

    ea.action = std::get<0>(*i);
    ea.reactions = reactions;
    this->events.push_back(ea);
  }
  return *this;
}
