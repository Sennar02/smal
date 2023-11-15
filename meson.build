project('smal', 'cpp',
    default_options: ['cpp_std=c++17'],
    version:         '1.0.0',
    license:         'MIT',
)

smal_header = include_directories('include')

smal_memory = static_library('smal-memory',
    sources: [
        'source/smal/Memory/helper.cpp',
        'source/smal/Memory/Page.cpp',
        'source/smal/Memory/PageTable.cpp',
        'source/smal/Memory/Origin/PoolOrigin.cpp',
        'source/smal/Memory/Origin/StackOrigin.cpp',
    ],
    include_directories: [smal_header],
)

smal_parser = static_library('smal-parser',
    sources: [
        'source/smal/Parser/String.cpp',
        'source/smal/Parser/Json/Lexeme.cpp',
        'source/smal/Parser/Json/Lexer.cpp',
        'source/smal/Parser/Json/Reader.cpp',
        'source/smal/Parser/Json/Client.cpp',
    ],
    include_directories: [smal_header],
)

smal_struct = static_library('smal-struct',
    sources: [
        'source/smal/Struct/Algo/Hashing.cpp',
    ],
    include_directories: [smal_header],
)


smal_engine = static_library('smal-engine',
    sources: [
        'source/smal/Engine/Engine.cpp',
        'source/smal/Engine/Screen/Screen.cpp',
        'source/smal/Engine/Screen/ScreenMachine.cpp',
    ],
    include_directories: [smal_header],
)

smal_depend = [
    dependency('sfml-graphics', required: true),
]
smal_define = [
    smal_memory,
    smal_parser,
    smal_struct,
    smal_engine,
]

executable('smal',
    sources: [
        'source/smal.cpp',
    ],
    include_directories: [smal_header],
    link_with:           [smal_define],
    link_args:           '-lm',
    dependencies:        [smal_depend],
)
