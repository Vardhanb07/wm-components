#pragma once

#include "gtkmm/window.h"
#include "sys.h"

#include <memory>

class Menu : public Gtk::Window {
public:
  Menu();
  virtual ~Menu();

protected:
  std::unique_ptr<Sys> sys;
};
