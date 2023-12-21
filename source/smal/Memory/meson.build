smal_memory = static_library('smal-memory',
    sources: [
        'Origin/BaseOrigin.cpp',
        'Origin/NullOrigin.cpp',
        'Origin/ArenaOrigin.cpp',
        'Origin/StackOrigin.cpp',
        'Origin/PoolOrigin.cpp',
        'Origin/SplitOrigin.cpp',
        'MemoryTable.cpp',
        'MemoryModule.cpp',
    ],
    include_directories: [smal_header],
)

smal_define = smal_define + smal_memory
