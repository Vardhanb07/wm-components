#include "launcher.h"
#include "entry.h"
#include "gdk/gdkkeysyms.h"
#include "gtk4-layer-shell.h"
#include "gtkmm/box.h"
#include "gtkmm/enums.h"
#include "gtkmm/eventcontroller.h"
#include "gtkmm/eventcontrollerkey.h"
#include "gtkmm/label.h"
#include "gtkmm/object.h"
#include "gtkmm/signallistitemfactory.h"
#include "gtkmm/singleselection.h"
#include "gtkmm/stringlist.h"
#include "gtkmm/widget.h"
#include "pangomm/layout.h"
#include "sigc++/functors/mem_fun.h"

#include <memory>

Launcher::Launcher()
    : vBox(Gtk::Orientation::VERTICAL), entry(std::make_unique<Entry>()) {
  gtk_layer_init_for_window(gobj());
  gtk_layer_set_layer(gobj(), GTK_LAYER_SHELL_LAYER_TOP);
  gtk_layer_set_keyboard_mode(gobj(), GTK_LAYER_SHELL_KEYBOARD_MODE_EXCLUSIVE);
  gtk_layer_auto_exclusive_zone_enable(gobj());

  set_default_size(400, 500);
  vBox.set_size_request(400, 500);
  vBox.set_margin(6);

  set_child(vBox);
  vBox.append(searchEntry);
  vBox.append(scrolledWindow);
  scrolledWindow.set_child(listView);

  scrolledWindow.set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);
  scrolledWindow.set_vexpand(true);

  searchEntry.signal_search_changed().connect(
      sigc::mem_fun(*this, &Launcher::on_search_changed));

  stringList = Gtk::StringList::create(entry->get_app_names());
  auto model = Gtk::SingleSelection::create();
  model->set_can_unselect(false);
  model->set_model(stringList);
  listView.set_model(model);

  auto factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
      sigc::mem_fun(*this, &Launcher::on_setup_label));
  factory->signal_bind().connect(sigc::mem_fun(*this, &Launcher::on_bind_name));
  listView.set_factory(factory);

  listView.signal_activate().connect(
      sigc::mem_fun(*this, &Launcher::on_activate));

  auto key_controller = Gtk::EventControllerKey::create();
  key_controller->set_propagation_phase(Gtk::PropagationPhase::CAPTURE);
  key_controller->signal_key_pressed().connect(
      sigc::mem_fun(*this, &Launcher::on_key_pressed), false);
  add_controller(key_controller);
}

Launcher::~Launcher() {}

auto Launcher::on_key_pressed(guint keyval, guint keycode,
                              Gdk::ModifierType state) -> bool {
  if (keyval == GDK_KEY_Escape) {
    close();
    return true;
  }
  if (keyval == GDK_KEY_Return) {
    auto model =
        std::dynamic_pointer_cast<Gtk::SingleSelection>(listView.get_model());
    auto position = model->get_selected();
    on_activate(position);
    return true;
  }
  return false;
}

void Launcher::on_setup_label(const Glib::RefPtr<Gtk::ListItem> &listItem) {
  auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
  box->set_size_request(400, -1);
  auto label = Gtk::make_managed<Gtk::Label>("", Gtk::Align::START);
  label->set_ellipsize(Pango::EllipsizeMode::END);
  box->append(*label);
  listItem->set_child(*box);
}

void Launcher::on_bind_name(const Glib::RefPtr<Gtk::ListItem> &listItem) {
  auto pos = listItem->get_position();
  auto label =
      dynamic_cast<Gtk::Label *>(listItem->get_child()->get_first_child());
  if (!label) {
    return;
  }
  label->set_text(stringList->get_string(pos));
}

void Launcher::on_activate(guint position) {
  auto app_name = stringList->get_string(position);
  entry->exec_app(app_name);
  close();
}

void Launcher::on_search_changed() {
  auto query = searchEntry.get_text();
  if (!query.empty()) {
    stringList->splice(0, stringList->get_n_items(),
                       entry->fuzz_query_apps(query));
    return;
  }
  stringList->splice(0, stringList->get_n_items(), entry->get_app_names());
}
