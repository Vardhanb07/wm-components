#pragma once

#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/window.h"
#include "sys.h"

#include <memory>

class Menu : public Gtk::Window {
public:
  Menu();
  virtual ~Menu();

protected:
  void on_shutdown_button_click();
  void on_sleep_button_click();
  void on_lock_button_click();
  void on_logout_button_click();
  void on_reboot_button_click();

  bool on_key_press(guint keyval, guint, Gdk::ModifierType state);

  Gtk::Box hBox;
  Gtk::Button shutdownButton;
  Gtk::Button sleepButton;
  Gtk::Button lockButton;
  Gtk::Button logoutButton;
  Gtk::Button rebootButton;

  std::unique_ptr<Sys> sys;
};
