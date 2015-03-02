CC = g++-4.8
F_FLAGS = -std=c++11
L_FLAGS = -lGL -lglut -lGLU -lm
BUILDDIR = build

all:
    g++-4.8 -std=c++11 src/tp/TP_OPENGL.cpp src/core/*.cpp -lGL -lglut -lGLU -lm
    g++-4.8 -std=c++11 -o a.out src/core/*.cpp src/curves/*.cpp src/tp/TP_OPENGL.cpp -lGL -lglut -lGLU -lm
    g++-4.8 -std=c++11 -o a.out src/core/*.cpp src/curves/*.cpp src/surfaces/*.cpp src/tp3/tp3.cpp -lGL -lglut -lGLU -lm
    g++-4.8 -std=c++11 -o a.out src/core/*.cpp src/curves/*.cpp src/surfaces/*.cpp src/tp3/mainCylindricSurface.cpp -lGL -lglut -lGLU -lm
   g++-4.8 -std=c++11 -o a.out src/core/*.cpp src/curves/*.cpp src/surfaces/*.cpp src/tp3/mainRuledSurf.cpp -lGL -lglut -lGLU -lm
   g++-4.8 -std=c++11 -o a.out src/core/*.cpp src/curves/*.cpp src/surfaces/*.cpp src/tp3/mainStrange.cpp -lGL -lglut -lGLU -lm
test:
    g++-4.8 -std=c++11 ./src/tp/test.cp ./src/core/*.cpp -o test

