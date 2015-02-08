CC = g++-4.8
F_FLAGS = -std=c++11
L_FLAGS = -lGL -lglut -lGLU -lm
BUILDDIR = build

all:
    g++-4.8 -std=c++11 src/tp/TP_OPENGL.cpp src/core/*.cpp -lGL -lglut -lGLU -lm

test:
    g++-4.8 -std=c++11 ./src/tp/test.cp ./src/core/*.cpp -o test

