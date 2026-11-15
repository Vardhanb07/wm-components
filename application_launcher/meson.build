project('application_laucher', 'cpp', version: '1.0', default_options: ['cpp_std=c++17'])

gtk = [dependency('gtkmm-4.0'), dependency('gtk4-layer-shell-0')]

rapifuzz = declare_dependency(
  include_directories: include_directories('vendor/rapidfuzz', is_system: true),
)

executable('application_launcher', 'main.cc', dependencies: [gtk, rapifuzz])
