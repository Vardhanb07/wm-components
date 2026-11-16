project(
  'logout_menu',
  'cpp',
  version: '1.0',
  license: 'MIT',
  default_options: ['cpp_std=c++17'],
)

gtk = [dependency('gtkmm-4.0'), dependency('gtk4-layer-shell-0')]

gnome = import('gnome')

app_resources = gnome.compile_resources(
  'logout-menu-resources',
  'resources.gresource.xml',
  source_dir: '.',
  c_name: 'logout_menu',
)

executable(
  'vlogout',
  'main.cc',
  'menu.cc',
  'sys.cc',
  app_resources,
  dependencies: [gtk],
  install: true,
)
