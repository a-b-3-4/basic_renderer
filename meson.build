project('basic_renderer', 'cpp')

# dependencies
cpp = meson.get_compiler('cpp')
# glfw
libdir = meson.current_source_dir() + './dependencies/GLFW/lib-vc2022/'
glfw = cpp.find_library('glfw3', dirs : libdir)
# glew
libdir = meson.current_source_dir() + './dependencies/GLEW/lib/Release/x64/'
glew = cpp.find_library('glew32s', dirs : libdir)
# opengl32.lib
libdir = 'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.19041.0/um/x64/'
opengl = cpp.find_library('OpenGL32', dirs : libdir)

# include directories
include_directory = include_directories(
    'basic_renderer/include',
    'dependencies/GLFW/include',
    'dependencies/GLEW/include'
)

# src files
c = run_command('print_src_files.bat', check: true)
src_files = c.stdout().strip().split('\n')
executable(
    'basic_renderer',
    src_files,
    include_directories : include_directory,
    dependencies : [glfw, glew, opengl]
)