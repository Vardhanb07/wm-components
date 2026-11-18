#include "menu.h"
#include "gdk/gdkkeysyms.h"
#include "gdkmm/display.h"
#include "glibconfig.h"
#include "gtk/gtk.h"
#include "gtk4-layer-shell.h"
#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/cssprovider.h"
#include "gtkmm/enums.h"
#include "gtkmm/eventcontrollerkey.h"
#include "gtkmm/image.h"
#include "gtkmm/label.h"
#include "gtkmm/object.h"
#include "gtkmm/stylecontext.h"
#include "sigc++/functors/mem_fun.h"
#include "sys.h"

#include <memory>
#include <unistd.h>
#include <vector>

Menu::Menu(json config)
    : hBox(Gtk::Orientation::HORIZONTAL, 10), sys(std::make_unique<Sys>(config)) {
  gtk_layer_init_for_window(gobj());
  gtk_layer_set_layer(gobj(), GTK_LAYER_SHELL_LAYER_TOP);

  gtk_layer_set_keyboard_mode(gobj(), GTK_LAYER_SHELL_KEYBOARD_MODE_EXCLUSIVE);

  gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_TOP, TRUE);
  gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_LEFT, TRUE);
  gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, TRUE);
  gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, TRUE);

  gtk_layer_set_margin(gobj(), GTK_LAYER_SHELL_EDGE_TOP, 6);
  gtk_layer_set_margin(gobj(), GTK_LAYER_SHELL_EDGE_LEFT, 6);
  gtk_layer_set_margin(gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, 6);
  gtk_layer_set_margin(gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, 6);

  auto css_provider = Gtk::CssProvider::create();
  css_provider->load_from_resource(
      "/com/vardhanbattula/wm-components/logout_menu/styles.css");
  Gtk::StyleContext::add_provider_for_display(Gdk::Display::get_default(),
                                              css_provider,
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);

  add_css_class("logout-menu");

  auto key_controller = Gtk::EventControllerKey::create();
  key_controller->signal_key_pressed().connect(
      sigc::mem_fun(*this, &Menu::on_key_press), false);
  add_controller(key_controller);

  hBox.set_halign(Gtk::Align::CENTER);
  hBox.set_valign(Gtk::Align::CENTER);
  set_child(hBox);

  std::vector<std::pair<Gtk::Button *, std::string>> buttons = {
      {&shutdownButton, "shutdown"},
      {&sleepButton, "sleep"},
      {&lockButton, "lock"},
      {&logoutButton, "logout"},
      {&rebootButton, "reboot"}};
  for (auto &[button, name] : buttons) {
    button->add_css_class("logout-button");
    button->add_css_class("flat");
    auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    box->set_valign(Gtk::Align::CENTER);
    box->set_halign(Gtk::Align::CENTER);
    box->set_can_target(false);
    auto icon = Gtk::make_managed<Gtk::Image>();
    icon->set_from_resource(
        "/com/vardhanbattula/wm-components/logout_menu/icons/" + name + ".png");
    icon->set_size_request(90, 90);
    icon->set_pixel_size(50);
    icon->set_can_target(false);
    auto label = Gtk::make_managed<Gtk::Label>(name);
    label->set_can_target(false);
    box->append(*icon);
    box->append(*label);
    button->set_child(*box);
    hBox.append(*button);
  }

  shutdownButton.signal_clicked().connect(
      sigc::mem_fun(*this, &Menu::on_shutdown_button_click));
  sleepButton.signal_clicked().connect(
      sigc::mem_fun(*this, &Menu::on_sleep_button_click));
  lockButton.signal_clicked().connect(
      sigc::mem_fun(*this, &Menu::on_lock_button_click));
  logoutButton.signal_clicked().connect(
      sigc::mem_fun(*this, &Menu::on_logout_button_click));
  rebootButton.signal_clicked().connect(
      sigc::mem_fun(*this, &Menu::on_reboot_button_click));
}

Menu::~Menu() {}

auto Menu::on_key_press(guint keyval, guint, Gdk::ModifierType state) -> bool {
  if (keyval == GDK_KEY_Escape) {
    close();
    return true;
  }
  return false;
}

void Menu::on_shutdown_button_click() {
  sys->shutdown();
  close();
}

void Menu::on_sleep_button_click() {
  sys->sleep();
  close();
}

void Menu::on_lock_button_click() {
  sys->lock();
  close();
}

void Menu::on_logout_button_click() {
  sys->logout();
  close();
}

void Menu::on_reboot_button_click() {
  sys->reboot();
  close();
}
