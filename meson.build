project('smal', 'cpp',
    default_options: ['cpp_std=c++17'],
    version:         '1.0.0',
    license:         'MIT'
)

smal_header = include_directories('include')
smal_memory = static_library('smal-memory',
    sources: [
        'source/smal/Memory/helper.cpp',
        'source/smal/Memory/Part.cpp',
        'source/smal/Memory/PageAlloc.cpp',
        'source/smal/Memory/PageTable.cpp',
        'source/smal/Memory/ArenaAlloc.cpp'
    ],
    include_directories: [smal_header]
)

smal_depend = [
    dependency('sfml-graphics', static: true)
]

executable('smal', 'source/main.cpp',
    include_directories: [smal_header],
    link_with:           [smal_memory],
    link_args:           '-lm',
    dependencies:        [smal_depend])
