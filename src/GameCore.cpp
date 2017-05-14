#include "GameCore.hh"
#include "BasicExcel.hpp"

GameCore::GameCore() {}

GameCore::~GameCore() {}

int GameCore::loadStory(std::string file) {
  YExcel::BasicExcel excel;

  excel.Load(file.c_str());
  for (size_t i = 0; i < excel.GetTotalWorkSheets(); ++i) {
    YExcel::BasicExcelWorksheet* ws = excel.GetWorksheet(i);
    std::shared_ptr<IModule> ptr(new Module<Text>(new Text(ws)));

    if (!i) this->head = ptr;
    storyLines[ws->GetAnsiSheetName()] = ptr;
  }
  return 0;
}

void GameCore::start() {
  this->graphics.start();
  if (this->graphics.menu() < 0) return;
  Text* sample = new Text(NULL);
  sample->setDefault();
  Module<Text> sModule(sample);
  this->graphics.dispModule(sModule);
}
