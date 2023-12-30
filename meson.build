project('smal', 'cpp',
    default_options: ['cpp_std=c++17'],
    version:         '1.0.0',
    license:         'MIT',
)

smal_header = include_directories('include')
smal_depend = []
smal_define = []

subdir('source/smal/Base')
subdir('source/smal/Memory')

executable('smal',
    sources: [
        'source/smal.cpp',
    ],
    include_directories: [smal_header],
    dependencies:        [smal_depend],
    link_with:           [smal_define],
    link_args:           '-lm',
)
