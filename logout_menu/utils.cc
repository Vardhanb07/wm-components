#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

std::filesystem::path abs_path(std::string &s) {
  std::string res = s;
  if (res == "~" || res.rfind("~/", 0) == 0) {
    const char *home = std::getenv("HOME");
    if (home != nullptr) {
      res.replace(0, 1, home);
    }
  }
  return std::filesystem::absolute(res);
}

using nlohmann::json;

json read_config_file(std::filesystem::path &abs_config_path) {
  std::ifstream f{abs_config_path};
  json data = json::parse(f);
  return data;
}
