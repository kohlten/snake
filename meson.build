project('snake', 'c')

src = ['src/food.c', 'src/game.c', 'src/main.c', 'src/snake.c', 'src/util/draw.c', 'src/util/fps.c',
       'src/util/surface.c', 'src/util/text/text.c', 'src/util/text/text_util.c', 'src/util/window.c', 'src/util/list.c']

base_dir = include_directories('src')
cc = meson.get_compiler('c')

libsdl2_dep = dependency('SDL2')
libsdl2_image_dep = dependency('SDL2_image')
libsdl2_ttf_dep = dependency('SDL2_ttf')
jansson_dep = dependency('jansson')
sodium_dep = dependency('libsodium')

sndio = cc.find_library('sndio', required : false)
math = cc.find_library('m', required : false)
dl = cc.find_library('dl', required : false)

add_project_arguments('-Wextra', '-Wall', '-g', language : 'c')


depends = [libsdl2_dep, libsdl2_image_dep,
           libsdl2_ttf_dep, jansson_dep, sodium_dep,
           math, dl, sndio]

executable('snake', src,
           dependencies : depends,
                          include_directories: [base_dir])
