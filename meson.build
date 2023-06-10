project('MultiCalc', 'cpp',
    version : 'v0.1',
    default_options : ['cpp_std=c++20']
)

sources = files(
    'src/main.cpp'
)

includes = include_directories('src')

cmake = import('cmake')

ftxui_opts = cmake.subproject_options()
ftxui_opts.add_cmake_defines({ 'FTXUI_ENABLE_INSTALL' : false })

ftxui_sub = cmake.subproject('ftxui', options : ftxui_opts)
ftxui_deps = [
    ftxui_sub.dependency('component'),
    ftxui_sub.dependency('dom'), 
    ftxui_sub.dependency('screen')
]

fmt_opts = cmake.subproject_options()
fmt_opts.add_cmake_defines({
    'FMT_INSTALL' : false,
    'FMT_TEST' : false,
    'FMT_DOC' : false
})

fmt_dep = cmake.subproject('fmt', options : fmt_opts).dependency('fmt')

executable('multicalc',
    dependencies : [
        ftxui_deps,
        fmt_dep
    ],
    sources : sources,
    include_directories : includes
)