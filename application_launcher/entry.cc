#include "entry.h"
#include "gio/gio.h"
#include "glib-object.h"
#include "glib.h"
#include "glibmm/ustring.h"

#include <algorithm>
#include <execution>
#include <iostream>
#include <memory>
#include <rapidfuzz/distance/LCSseq.hpp>
#include <rapidfuzz/fuzz.hpp>
#include <vector>

Entry::Entry() {
  auto app_list = g_app_info_get_all();
  for (auto i = app_list; i != nullptr; i = i->next) {
    auto app_info = static_cast<GAppInfo *>(i->data);
    if (g_app_info_should_show(app_info) && g_app_info_get_name(app_info)) {
      g_object_ref(app_info);
      apps.push_back(
          std::make_shared<App>(App(g_app_info_get_name(app_info), app_info)));
    }
  }
  g_list_free_full(app_list, g_object_unref);
}

auto Entry::get_app_names() -> std::vector<Glib::ustring> {
  std::vector<Glib::ustring> ret;
  for (auto &app : apps) {
    ret.push_back(app->name);
  }
  return ret;
}

void Entry::exec_app(std::string app_name) {
  for (auto &app : apps) {
    if (app->name == app_name) {
      GError *err = nullptr;
      bool s = g_app_info_launch(app->info, nullptr, nullptr, &err);
      if (!s) {
        std::cerr << "Error launching application: " << err->message
                  << std::endl;
        g_error_free(err);
      }
    }
  }
}

auto Entry::fuzz_query_apps(std::string query) -> std::vector<Glib::ustring> {
  std::vector<std::pair<Glib::ustring, int>> v;
  for (auto &app : apps) {
    double score = rapidfuzz::fuzz::ratio(query, app->name, 60.0);
    if (score != 0.0) {
      app->lcs_score = rapidfuzz::lcs_seq_similarity(query, app->name, 1);
      if (app->lcs_score != 0) {
        v.push_back({app->name, app->lcs_score});
      }
    }
  }
  std::sort(std::execution::par, v.begin(), v.end(),
            [&](std::pair<Glib::ustring, int> a,
                std::pair<Glib::ustring, int> b) -> bool {
              return a.second > b.second;
            });
  std::vector<Glib::ustring> ret;
  for (auto &[name, _] : v) {
    ret.push_back(name);
  }
  return ret;
}
