#pragma once

#include "giomm/appinfo.h"

#include <string>
#include <vector>

struct App {
  std::string name;
  GAppInfo *info;
  int lcs_score;
  App(std::string name, GAppInfo *info)
      : name(name), info(info), lcs_score(0) {}
};

class Entry {
public:
  Entry();
  ~Entry() = default;

  std::vector<Glib::ustring> get_app_names();
  void exec_app(std::string app_name);
  std::vector<Glib::ustring> fuzz_query_apps(std::string query);

protected:
  std::vector<std::shared_ptr<App>> apps;
};
