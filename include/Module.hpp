#ifndef MODULE_HPP
#define MODULE_HPP

#include <iostream>
#include <map>
#include <tuple>
#include <vector>

using Consequence = std::map<std::string, std::string>;

struct Results {
  std::string direction;
  std::map<std::string, std::vector<std::string>> consequences;
};

template <class EType>
struct EventAction {
  EventAction<EType> const& operator=(EventAction<EType> const& e) {
    this->line = e.line;
    this->actor = e.actor;
    this->actorAsset = e.actorAsset;
    this->action = e.action;
    this->reactions = e.reactions;
    this->cons = e.cons;
    return *this;
  }
  int line;
  std::string actor;
  std::string actorAsset;
  EType action;
  std::vector<EType> reactions;
  std::vector<Consequence> cons;
};

class IModule {
 public:
  virtual Results const& getConsequences() const = 0;
};

template <class Type>
class Module : public IModule {
 public:
  const std::string background;

  Module(Type* contained, std::string bg)
      : content(contained), background(bg), id(0) {
    results.direction = "Next";
    results.consequences[std::string("toto")] = 18;
    // this->content->setEvents();
  }
  Module(Type* contained) : Module(contained, "modules/default.png") {}
  ~Module() { delete this->content; }
  EventAction<typename Type::EventType> const& getEvent() {
    if (this->id >= this->content->events.size()) throw(0);
    return this->content->events[id];
  }
  void setReact(size_t rid) {
    Consequence c = this->content->events[this->id].cons[rid];

    for (auto i = c.cbegin(); i != c.cend(); ++i) {
      this->results[i->first].push_back(i->second);
    }
    ++this->id;
    try {
      int line = atoi(c.at("ligne").c_str());
      this->id = 0;

      for (auto i = this->content->events.cbegin();
	   i < this->content->events.cend(); ++i) {
	if (i->line == line) break;
	++this->id;
      }
    } catch (std::out_of_range const& e) {
    }

    try {
      this->results.direction = c.at("module");
      this->id = -1;
    } catch (std::out_of_range const& e) {
    }
  }
  Results const& getConsequences() const { return this->results; }

  Type* content;

 private:
  Results results;
  size_t id;
};

/*
** ===============================
** Modules types
** ===============================
*/

class Text {
 public:
  using Unit = std::map<std::string, Consequence>;
  using EventType = std::string;

  Text(std::string const&);
  // Text& setDefault();
  // Text& setEvents();

  std::vector<EventAction<EventType>> events;
  std::string f;
};

#endif /* !MODULE_HPP */
