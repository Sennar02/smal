smal_engine = static_library('smal-engine',
    sources: [
        'State.cpp',
        'StateManager.cpp',
        'Engine.cpp',
    ],
    include_directories: [smal_header],
)

smal_define = smal_define + smal_engine
smal_depend = smal_depend + [
    dependency('sfml-graphics'),
]
