#include "screen.h"
#include "gtkmm/button.h"
#include "gtkmm/enums.h"
#include "gtkmm/label.h"

#include "gdk/gdkkeysyms.h"
#include "glib.h"
#include "gtkmm/eventcontrollerkey.h"

#include "glibconfig.h"
#include "gtk4-layer-shell/gtk4-layer-shell.h"
#include "sigc++/functors/mem_fun.h"

#include <unistd.h>

Screen::Screen() : vBox(Gtk::Orientation::VERTICAL), label("test label"), button("test") {
  gtk_layer_init_for_window(gobj());

  gtk_layer_set_layer(gobj(), GTK_LAYER_SHELL_LAYER_OVERLAY);

  gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_TOP, TRUE);
  gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_LEFT, TRUE);
  gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, TRUE);
  gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, TRUE);

  gtk_layer_set_keyboard_mode(gobj(), GTK_LAYER_SHELL_KEYBOARD_MODE_EXCLUSIVE);

#ifdef dev
  auto key_controller = Gtk::EventControllerKey::create();
  key_controller->signal_key_pressed().connect(
      [this](guint keyval, guint, Gdk::ModifierType state) -> bool {
        if (keyval == GDK_KEY_Escape) {
          this->close();
          return true;
        }
        return false;
      },
      false);
  add_controller(key_controller);
#endif

  vBox.set_halign(Gtk::Align::CENTER);
  vBox.set_valign(Gtk::Align::CENTER);
  vBox.append(label);
  vBox.append(entry);
  vBox.append(button);

  set_child(vBox);

  button.signal_clicked().connect(
      sigc::mem_fun(*this, &Screen::on_button_click));
}

Screen::~Screen() {}

void Screen::on_button_click() { close(); }
