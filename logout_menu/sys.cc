#include "sys.h"
#include "glibmm/spawn.h"

#include <nlohmann/json.hpp>
#include <ostream>
#include <string>
#include <iostream>

using nlohmann::json;

Sys::Sys(json config) : config(config) {}

void Sys::shutdown() {
  std::string shutdown_cmd = config["shutdown"]["cmd"];
  Glib::spawn_command_line_async(shutdown_cmd);
}

void Sys::sleep() {
  std::string sleep_cmd = config["sleep"]["cmd"];
  Glib::spawn_command_line_async(sleep_cmd);
}

void Sys::lock() {
  std::string lock_cmd = config["lock"]["cmd"];
  Glib::spawn_command_line_async(lock_cmd);
}

void Sys::logout() {
  std::string logout_cmd = config["logout"]["cmd"];
  Glib::spawn_command_line_async(logout_cmd);
}

void Sys::reboot() {
  std::string reboot_cmd = config["reboot"]["cmd"];
  Glib::spawn_command_line_async(reboot_cmd);
}
