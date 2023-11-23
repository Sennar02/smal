smal_memory = static_library('smal-memory',
    sources: [
        'Page.cpp',
        'PageTable.cpp',
        'Origin/PoolOrigin.cpp',
        'Origin/StackOrigin.cpp',
        'helper.cpp',
    ],
    include_directories: [smal_header],
)

smal_define = smal_define + smal_memory
