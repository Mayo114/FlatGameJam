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
    std::cout << "toto" << std::endl;
    this->line = e.line;
    std::cout << "toto" << std::endl;
    this->actor = e.actor;
    std::cout << "toto" << std::endl;
    this->actorAsset = e.actorAsset;
    std::cout << "toto" << std::endl;
    this->action = e.action;
    std::cout << "toto" << std::endl;
    this->reactions = e.reactions;
    std::cout << "toto" << std::endl;
    this->cons = e.cons;
    std::cout << "toto" << std::endl;
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
    std::cout << this->content->events.size() << std::endl;
    return this->content->events[id];
  }
  void setReact(size_t id) { ++id; }
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
