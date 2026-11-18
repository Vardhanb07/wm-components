#pragma once

#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/entry.h"
#include "gtkmm/label.h"
#include "gtkmm/window.h"

class Screen : public Gtk::Window {
public:
  Screen();
  virtual ~Screen();

protected:
  void on_button_click();

  Gtk::Box vBox;
  Gtk::Label label;
  Gtk::Entry entry;
  Gtk::Button button;
};
