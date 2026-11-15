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

gnome = import('gnome')

app_resources = gnome.compile_resources('app-resources', 'resources.gresource.xml', source_dir: '.', c_name: 'app')

executable(
  'vapplauncher',
  'main.cc',
  'launcher.cc',
  'entry.cc',
  app_resources,
  dependencies: [gtk, rapifuzz],
  install: true,
)
