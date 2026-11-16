#include "gtkmm/application.h"
#include "menu.h"

int main(int argc, char *argv[]) {
  auto app =
      Gtk::Application::create("com.vardhanbattula.wm-components.logout_menu");
  return app->make_window_and_run<Menu>(argc, argv);
}
