#pragma once

#include "entry.h"
#include "gdkmm/enums.h"
#include "glib.h"
#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/listitem.h"
#include "gtkmm/listview.h"
#include "gtkmm/scrolledwindow.h"
#include "gtkmm/searchentry.h"
#include "gtkmm/stringlist.h"
#include "gtkmm/window.h"

#include <memory>

class Launcher : public Gtk::Window {
public:
  Launcher();
  virtual ~Launcher();

protected:
  void on_setup_label(const Glib::RefPtr<Gtk::ListItem> &listItem);
  void on_bind_name(const Glib::RefPtr<Gtk::ListItem> &listItem);
  void on_activate(guint position);
  bool on_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state);
  void on_search_changed();

  Gtk::Box vBox;
  Gtk::SearchEntry searchEntry;
  Gtk::ListView listView;
  Gtk::ScrolledWindow scrolledWindow;
  Glib::RefPtr<Gtk::StringList> stringList;

  std::unique_ptr<Entry> entry;
};
