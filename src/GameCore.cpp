#include "GameCore.hh"
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include "csv.h"

static int getdir(std::string dir, std::vector<std::string> &files) {
  DIR *dp;
  struct dirent *dirp;
  if ((dp = opendir(dir.c_str())) == NULL) {
    std::cout << "Error(" << errno << ") opening " << dir << std::endl;
    return errno;
  }

  while ((dirp = readdir(dp)) != NULL) {
    files.push_back(std::string(dirp->d_name));
  }
  closedir(dp);
  return 0;
}

GameCore::GameCore() {}

GameCore::~GameCore() {}

int GameCore::loadStory(std::string file) {
  std::vector<std::string> files;

  getdir(file, files);
  std::cout << files.size() << std::endl;
  this->head = storyLines[*files.cbegin()];
  for (auto i = files.cbegin(); i != files.cend(); ++i) {
    try {
      std::shared_ptr<IModule> ptr(new Module<Text>(new Text(file + "/" + *i)));
      storyLines[*i] = ptr;
    } catch (io::error::too_many_columns const &e) {
      std::cerr << e.what() << std::endl;
      exit(0);
    } catch (io::error::too_few_columns const &e) {
      std::cerr << e.what() << std::endl;
      exit(0);
    }
  }
  return 0;
}

void GameCore::start() {
  usleep(300000);
  this->graphics.start();
  if (this->graphics.menu() < 0) return;
  this->graphics.dispModule(dynamic_cast<Module<Text> *>(&*this->head));
}
