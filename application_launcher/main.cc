#include "gtkmm/application.h"
#include "launcher.h"

int main(int argc, char *argv[]) {
  auto app = Gtk::Application::create(
      "com.vardhanb07.wm-components.application_launcher");
  return app->make_window_and_run<Launcher>(argc, argv);
}
