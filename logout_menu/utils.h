#include <filesystem>
#include <nlohmann/json.hpp>

using nlohmann::json;

std::filesystem::path abs_path(std::string &s);
json read_config_file(std::filesystem::path &abs_config_path);
