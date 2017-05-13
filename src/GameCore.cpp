#include "BasicExcel.hpp"
#include "GameCore.hh"

GameCore::GameCore() {}

GameCore::~GameCore() {}

int GameCore::loadStory(std::string file) {
  YExcel::BasicExcel excel;

  excel.Load(file.c_str());
  for (size_t i = 0; i < excel.GetTotalWorkSheets(); ++i) {
    YExcel::BasicExcelWorksheet* ws = excel.GetWorksheet(i);
    std::shared_ptr<IModule> ptr(new Module<Text>(Text(ws)));

    if (!i) this->head = ptr;
    storyLines[ws->GetAnsiSheetName()] = ptr;
  }
  return 0;
}

void GameCore::start() {
  this->graphics.start();
  this->graphics.loop();
}
