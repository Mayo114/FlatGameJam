#ifndef MODULE_HPP
#define MODULE_HPP

#include <iostream>
#include <map>
#include <tuple>
#include <vector>

using Consequence = std::map<std::string, int>;

struct Results {
  std::string direction;
  Consequence consequences;
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
  void setReact(size_t id) { ++this->id; }
  Results const& getConsequences() const { return results; }

  Type* content;

 private:
  Results results;
  Consequence cnsq;
  size_t id;
  std::vector<std::string> childs;
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
