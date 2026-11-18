project(
  'lock_screen',
  'cpp',
  version: '1.0',
  license: 'MIT',
  default_options: ['cpp_std=c++17', 'buildtype=debug'],
)

if get_option('debug')
  add_project_arguments('-Ddev', language: 'cpp')
endif

gtk = [dependency('gtkmm-4.0'), dependency('gtk4-layer-shell-0')]

# gnome = import('gnome')

# app_resources = gnome.compile_resources(
#   'lock-screen-resources',
#   'resources.gresource.xml',
#   source_dir: '.',
#   c_name: 'lock_screen',
# )

executable(
  'vlockscreen',
  'main.cc',
  'screen.cc',
  'sys.cc',
  # app_resources,
  dependencies: [gtk],
  install: true,
)
