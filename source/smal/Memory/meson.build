smal_memory = static_library('smal-memory',
    sources: [
        'Alloc/NullAlloc.cpp',
        'Alloc/PoolAlloc.cpp',
        'Alloc/StackAlloc.cpp',
        'Alloc/ProxyAlloc.cpp',
        'Block/PageTable.cpp',
        'MemoryService.cpp',
        'util.cpp',
    ],
    include_directories: [smal_header],
)

smal_define = smal_define + smal_memory
