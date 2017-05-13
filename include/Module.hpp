#ifndef MODULE_HPP
#define MODULE_HPP

#include <vector>
#include "BasicExcel.hpp"

class Text {
 public:
  Text(YExcel::BasicExcelWorksheet const*);
};

class IModule {
  IModule* getNext() const;

 private:
  std::vector<std::string> childs;
};

template <class Type>
class Module : public IModule {
 public:
  Module(Type contained) : content(contained) {}

 private:
  Type content;
};

#endif /* !MODULE_HPP */
