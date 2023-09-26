project('smal', 'cpp',
    version: '1.0.0'
)

include = include_directories('include')

smal_memory = static_library('smal-memory',
    'source/smal/Memory/define.cpp',
    'source/smal/Memory/Page.cpp',
    'source/smal/Memory/PageAlloc.cpp',
    'source/smal/Memory/PageTable.cpp',
    include_directories: include
)

executable('smal',
    'source/main.cpp',
    include_directories: include,
    link_with:           smal_memory,
    override_options:    [
        'cpp_std=c++17'
    ]
)
