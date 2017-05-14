#ifndef MODULE_HPP
#define MODULE_HPP

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
    return this->content->events[id];
  }
  void setReact(size_t id) { ++id; }
  Results const& getConsequences() const { return results; }

 private:
  Results results;
  Type* content;
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
  struct id {
    int line;
    std::string actor;
    std::string content;
  };

  Text(std::string const&);
  // Text& setDefault();
  // Text& setEvents();

  std::vector<EventAction<EventType>> events;
};

#endif /* !MODULE_HPP */
