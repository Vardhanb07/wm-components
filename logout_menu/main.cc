#include "gtkmm/application.h"
#include "menu.h"
#include "nlohmann/json_fwd.hpp"
#include "utils.h"
#include <cstdlib>
#include <filesystem>
#include <getopt.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <ostream>

using nlohmann::json;

int main(int argc, char *argv[]) {
  char option;
  std::string config_file = "";
  std::string help = "-c <filename>, provide config with this "
                     "option. Config file should have json";
  std::string invalid_opt_err = "invalid option, use -h or --help";
  std::string file_not_found_err = "file not found";
  std::string not_a_file_err = "not a file";
  std::string json_err = "invalid config format, use json";

  while ((option = getopt(argc, argv, "c:h")) != -1) {
    switch (option) {
    case 'h':
      std::cout << help << std::endl;
      return EXIT_FAILURE;
    case 'c':
      config_file = optarg;
      break;
    case '?':
      std::cerr << invalid_opt_err << std::endl;
      return EXIT_FAILURE;
    }
  }

  if (optind < 2) {
    std::cerr << invalid_opt_err << std::endl;
    return EXIT_FAILURE;
  }

  auto abs_config_file = abs_path(config_file);

  if (!std::filesystem::exists(abs_config_file)) {
    std::cerr << file_not_found_err << std::endl;
    return EXIT_FAILURE;
  }

  if (!std::filesystem::is_regular_file(abs_config_file) &&
      !std::filesystem::is_symlink(abs_config_file)) {
    std::cerr << not_a_file_err << std::endl;
    return EXIT_FAILURE;
  }

  json config = read_config_file(abs_config_file);

  auto app =
      Gtk::Application::create("com.vardhanbattula.wm-components.logout_menu");

  return app->make_window_and_run<Menu>(0, nullptr, config);
}
