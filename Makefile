
OUT = snake
LIB = src/lib

CFILES := src/main.c \
src/game.c \
src/snake.c \
src/food.c \
src/util/fps.c \
src/util/surface.c \
src/util/draw.c \
src/util/window.c \
src/util/text/load_text.c \
src/util/text/render_text.c \
src/util/text/text.c

OFILES := $(patsubst src/%.c, obj/%.o, $(CFILES))
SDL2IMAGE = dependencies/SDL2_image/.libs/libSDL2_image.a
SDL2TFF = dependencies/SDL2_tff/.libs/libSDL2_ttf.a
SDL2 = dependencies/SDL2/build/libSDL2.a
SODIUM = dependencies/libsodium/src/libsodium/.libs/libsodium.a
LIBFT = dependencies/libft/libft.a

TYPE=Debug

CC = gcc

STATIC=true

ifeq ($(STATIC), true)
LIBS = $(SDL2LIB) $(SDL2IMAGE) $(SDL2TFF) $(SDL2) $(LIBFT) $(SODIUM)
else
LIBS =	-L dependencies/SDL2/build -lSDL2 -L dependencies/SDL2_image/.libs/ -lSDL2_image \
		-L dependencies/SDL2_tff/.libs -lSDL2_ttf -L dependencies/libft -lft -L dependencies/libsodium/src/libsodium/.libs -l sodium
endif

ifeq ($(shell uname), Darwin)
PLATFORM_DEPENDENCIES = -framework CoreFoundation -framework AppKit -framework CoreAudio \
						-framework CoreVideo -framework ForceFeedback -framework IOKit \
						-framework Metal -framework Carbon -framework AudioToolbox -liconv \
						-L /usr/X11/lib/ -lfreetype
endif
ifeq ($(shell uname), Linux)
PLATFORM_DEPENDENCIES = -lX11 -lXext -lasound -lpthread -ldl -lm -lsndio -lcairo -lwayland-server -lwayland-client \
						-lwayland-cursor -lwayland-egl -lpulse -lXcursor -lXi -lXrandr -lXxf86vm -lXinerama -lXss \
						-lxkbcommon -lfreetype
endif

CFLAGS = -g -Wall -Wextra -Werror -I src -I dependencies/libft/include -I dependencies/SDL2/include -I dependencies/SDL2_image/ -I dependencies/SDL2_tff -I dependencies/libsodium/src/libsodium/include

all: dependencies $(OFILES)
	@echo "CC $(CFLAGS) -o $(OUT) $(PLATFORM_DEPENDENCIES) $(LIBS) $(OFILES)"
	@$(CC) $(CFLAGS) -o $(OUT) $(OFILES) $(LIBS) $(PLATFORM_DEPENDENCIES) 
	@echo "Done"

dependencies: obj $(SDL2) $(SDL2IMAGE) \
			$(SDL2TFF) $(LIBFT) $(SODIUM)

$(SDL2IMAGE):
	@echo "BUILDING SDL2IMAGE"
	@cd dependencies/SDL2_image && sh autogen.sh && ./configure && make 

$(SDL2TFF):
	@echo "BUILDING SDL2TFF"
	@cd dependencies/SDL2_tff && sh autogen.sh && ./configure && make 

$(SDL2):
	@echo "BUILDING SDL2"
	-@cd dependencies/SDL2 && mkdir build
	@cd dependencies/SDL2/build && cmake .. && make 

$(LIBFT):
	@echo "BUILDING LIBFT"
	@cd dependencies/libft && make

$(SODIUM):
	@echo "BUILDING LIBSODIUM"
	@cd dependencies/libsodium && sh autogen.sh && ./configure && make

obj/%.o: src/%.c
	@echo "CC $(CFLAGS) -c -o $@ $<"
	@$(CC) $(CFLAGS) -c -o $@ $<

run:
	./snake

# TODO Make this so that we dont need to make a new directory for every subdirectory in src
obj:
	-@mkdir obj
	-@mkdir obj/util
	-@mkdir obj/util/text
	-@mkdir dependencies

clean:
	-@rm -rf obj
	-@rm -f snake

fclean: clean
	-@rm -rf dependencies

re: clean all

.PHONY: all fclean clean re
