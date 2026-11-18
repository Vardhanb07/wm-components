#pragma once

#include <nlohmann/json.hpp>

using nlohmann::json;

class Sys {
public:
  Sys(json config);
  ~Sys() = default;

  void shutdown();
  void sleep();
  void lock();
  void logout();
  void reboot();

protected:
  json config;
};
