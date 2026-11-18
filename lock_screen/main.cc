#include "gtkmm/application.h"
#include "screen.h"

int main(int argc, char **argv) {
  auto app =
      Gtk::Application::create("com.vardhanbattula.wm-components.lock_screen");
  return app->make_window_and_run<Screen>(argc, argv);
}
