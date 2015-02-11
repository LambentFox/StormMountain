#Linux: -lGLU -lGL -lm
#Windows SDL: -lmingw32 -lSDLmain -lSDL -lglu32 -lopengl32
#Windows Glut: -lglu32 -lopengl32 -lglut32cu

ifeq ($(OS),Windows_NT)
	LIBS = -lglu32 -lopengl32 -lglut32cu -lglew32
else 
	UNAME := $(shell uname)
	ifeq ($(UNAME),Linux)
		LIBS = -lglut -lGLU -lGL -lm
	endif
endif

game: main.o glraphics.o shader.o matrix.o bufferDraw.o
	g++ -Wall -O3 -o $@ $^ $(LIBS)
.c.o:
	gcc -c -O3 -Wall $<
clean:
	rm -f game *.o
