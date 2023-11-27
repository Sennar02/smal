smal_memory = static_library('smal-memory',
    sources: [
        'Alloc/BaseAlloc.cpp',
        'Alloc/PoolAlloc.cpp',
        'Alloc/StackAlloc.cpp',
        'Block/PageTable.cpp',
        'util.cpp',
    ],
    include_directories: [smal_header],
)

smal_define = smal_define + smal_memory
