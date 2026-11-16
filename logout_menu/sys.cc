#include "sys.h"
#include "glibmm/spawn.h"

void Sys::shutdown() { Glib::spawn_command_line_async("systemctl poweroff"); }

void Sys::sleep() { Glib::spawn_command_line_async("systemctl suspend"); }

void Sys::lock() { Glib::spawn_command_line_async("loginctl lock-session"); }

void Sys::logout() {
  Glib::spawn_command_line_async(
      "sh -c 'loginctl kill-session $XDG_SESSION_ID'");
}

void Sys::reboot() { Glib::spawn_command_line_async("systemctl reboot"); }
