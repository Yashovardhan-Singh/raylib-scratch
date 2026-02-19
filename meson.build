project(
  'rlib-wshop',
  'c',
  version: '0.1.0',
  default_options: [
    'warning_level=2',
    'c_std=c11'
  ]
)

cc = meson.get_compiler('c')
sys = host_machine.system()
linkage = get_option('linkage')

deps = []
link_args = []
rpath = ''

if linkage == 'dynamic'
  if sys == 'linux'
    rpath = '$ORIGIN'
  elif sys == 'darwin'
    rpath = '@loader_path'
  endif
endif

raylib_dep = dependency('raylib', required: false)

if not raylib_dep.found()
  libdir = meson.project_source_root() / 'lib' / sys

  raylib_dep = cc.find_library(
    'raylib',
    dirs: libdir,
    static: linkage == 'static',
    required: true
  )
endif

deps += raylib_dep

if sys == 'linux'

  deps += [
    cc.find_library('GL', required: true),
    cc.find_library('m', required: true),
    cc.find_library('pthread', required: true),
    cc.find_library('dl', required: true),
    cc.find_library('rt', required: true),
    cc.find_library('X11', required: false),
  ]

elif sys == 'darwin'

  deps += [
    cc.find_library('m', required: true),
    cc.find_library('pthread', required: true),
    cc.find_library('objc', required: true),
  ]

  link_args += [
    '-framework', 'OpenGL',
    '-framework', 'Cocoa',
    '-framework', 'IOKit',
    '-framework', 'CoreVideo'
  ]

elif sys == 'windows'

  deps += [
    cc.find_library('opengl32', required: true),
    cc.find_library('gdi32', required: true),
    cc.find_library('winmm', required: true),
    cc.find_library('user32', required: true),
    cc.find_library('shell32', required: true),
  ]

else
  error('Unsupported platform: ' + sys)
endif

exe = executable(
  'main',
  'src/main.c',
  include_directories: include_directories('include'),
  dependencies: deps,
  link_args: link_args,
  install_rpath: rpath,
)

if linkage == 'dynamic'
  libdir = meson.project_source_root() / 'lib' / sys

  if sys == 'darwin'
    dylib = libdir / 'libraylib.dylib'
    if fs.exists(dylib)
      run_command('cp', dylib, meson.project_build_root(), check: false)
    endif

  elif sys == 'linux'
    sofile = libdir / 'libraylib.so'
    if fs.exists(sofile)
      run_command('cp', sofile, meson.project_build_root(), check: false)
    endif

  elif sys == 'windows'
    dllfile = libdir / 'raylib.dll'
    if fs.exists(dllfile)
      run_command('cp', dllfile, meson.project_build_root(), check: false)
    endif
  endif
endif
