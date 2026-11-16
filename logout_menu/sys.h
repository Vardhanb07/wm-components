#pragma once

class Sys {
public:
  Sys() = default;
  ~Sys() = default;

  void shutdown();
  void sleep();
  void lock();
  void logout();
  void reboot();
};
