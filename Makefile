CFLAGS = -O3 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -lm

INC = structure.h display.h data.h sdl_function.h map.h event.h
SRC = structure.c display.c data.c sdl_function.c map.c event.c game.c
OBJ = $(SRC:%.c=%.o)

PROG = ddkz

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $<
	
ddkz: $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

doc: $(PROG)
	doxygen ./$(PROG)
	make -C latex

clean:
	rm -f *~ *.o $(PROG) tests
	
date:
	date