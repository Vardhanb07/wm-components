project(
  'application_laucher',
  'cpp',
  version: '1.0',
  license: 'MIT',
  default_options: ['cpp_std=c++17'],
)

gtk = [dependency('gtkmm-4.0'), dependency('gtk4-layer-shell-0')]

rapifuzz = declare_dependency(
  include_directories: include_directories('vendor/rapidfuzz', is_system: true),
)

executable(
  'vapplauncher',
  'main.cc',
  'launcher.cc',
  'entry.cc',
  dependencies: [gtk, rapifuzz],
  install: true
)
