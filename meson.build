project('hazi_19_05', 'cpp',
  version : '1.0',
  default_options : [
    'cpp_std=c++17',
    'warning_level=3',
    # 'werror=true',
    'optimization=g',
    'debug=true',
    'b_ndebug=if-release'
  ]
)

fs = import('fs')

include_dir = include_directories('include')
cpptui_dir = meson.project_source_root() / 'external' / 'cpptui'

git = find_program('git', required: true)

if not fs.exists(cpptui_dir)
  # message('Cloning cpptui...')
  # run_command(git, 'clone', 'https://github.com/csboo/cpptui', cpptui_dir, check: true)


  message('Cloning cpptui at commit cfa92df...')
  run_command(git, 'init', cpptui_dir, check: true)
  run_command(git, '-C', cpptui_dir, 'remote', 'add', 'origin', 'https://github.com/csboo/cpptui', check: true)
  run_command(git, '-C', cpptui_dir, 'fetch', 'origin', 'cfa92dfdf69c6218f9cf95dac70cf8201a350184', check: true)
  run_command(git, '-C', cpptui_dir, 'checkout', 'FETCH_HEAD', check: true)
else
  message('Cpptui exists!')
endif

message('cpptui cloned to: ' + cpptui_dir)


executable('app',
  sources : [
    'src/main.cpp',
    'src/tools.cpp',
    'src/menu.cpp',
    'src/shop.cpp',
    'src/product.cpp'
  ],
  include_directories: include_dir,
  install : false
)

