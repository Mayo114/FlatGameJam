#ifndef MODULE_HPP
#define MODULE_HPP

#include <vector>
#include "BasicExcel.hpp"

struct Consequence {
  std::map<std::string, int> variables;
};

struct Results {
  std::string direction;
  Consequence consequences;
};

template <class EType>
struct EventAction {
  std::vector<EType> reactions;
};

class IModule {
 public:
  virtual Results const& getConsequences() const = 0;
};

template <class Type>
class Module : public IModule {
 public:
  Module(Type contained) : content(contained) {
    results.direction = "Next";
    results.consequences.variables[std::string("toto")] = 18;
  }
  EventAction<typename Type::EventType> const& getEvent();
  void setReact(size_t);
  Results const& getConsequences() const { return results; }

 private:
  Results results;
  Type content;
  Consequence cnsq;
  std::vector<std::string> childs;
};

/*
** ===============================
** Modules types
** ===============================
*/

class Text {
 public:
  struct EventType {
    std::string event;
  };
  Text(YExcel::BasicExcelWorksheet const*);
};

#endif /* !MODULE_HPP */
