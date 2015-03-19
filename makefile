CC = g++-4.8
F_FLAGS = -std=c++11
L_FLAGS = -lGL -lglut -lGLU -lm
BUILDDIR = build

SOURCE_DIR = src
CORE_DIR = $(SOURCE_DIR)/core
CURVE_DIR = $(SOURCE_DIR)/curves
PRIMITIVE_DIR = $(SOURCE_DIR)/primitives
SURFACE_DIR = $(SOURCE_DIR)/surfaces
GLWRAPPERS_DIR = $(SOURCE_DIR)/glWrappers

SRC_CORE = $(wildcard $(CORE_DIR)/*.cpp)
CORE_OBJECTS = $(patsubst $(CORE_DIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC_CORE))

SRC_CURVE = $(wildcard $(CURVE_DIR)/*.cpp)
CURVE_OBJECTS = $(patsubst $(CURVE_DIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC_CURVE))

SRC_PRIMITIVE = $(wildcard $(PRIMITIVE_DIR)/*.cpp)
PRIMITIVE_OBJECTS = $(patsubst $(PRIMITIVE_DIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC_PRIMITIVE))

SRC_SURFACE = $(wildcard $(SURFACE_DIR)/*.cpp)
SURFACE_OBJECTS = $(patsubst $(SURFACE_DIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC_SURFACE))

SRC_GLWRAPPERS = $(wildcard $(GLWRAPPERS_DIR)/*.cpp)
GLWRAPPERS_OBJECTS = $(patsubst $(GLWRAPPERS_DIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC_GLWRAPPERS))

all:
	g++-4.8 -std=c++11 src/tp/TP_OPENGL.cpp src/core/*.cpp -lGL -lglut -lGLU -lm
	g++-4.8 -std=c++11 -o a.out src/core/*.cpp src/curves/*.cpp src/tp/TP_OPENGL.cpp -lGL -lglut -lGLU -lm
	g++-4.8 -std=c++11 -o a.out src/core/*.cpp src/curves/*.cpp src/surfaces/*.cpp src/tp3/tp3.cpp -lGL -lglut -lGLU -lm
	g++-4.8 -std=c++11 -o a.out src/core/*.cpp src/curves/*.cpp src/surfaces/*.cpp src/tp3/mainCylindricSurface.cpp -lGL -lglut -lGLU -lm
   g++-4.8 -std=c++11 -o a.out src/core/*.cpp src/curves/*.cpp src/surfaces/*.cpp src/tp3/mainRuledSurf.cpp -lGL -lglut -lGLU -lm
   g++-4.8 -std=c++11 -o a.out src/core/*.cpp src/curves/*.cpp src/surfaces/*.cpp src/tp3/mainStrange.cpp -lGL -lglut -lGLU -lm
test:
	g++-4.8 -std=c++11 ./src/tp/test.cp ./src/core/*.cpp -o test


$(CORE_OBJECTS): $(BUILDDIR)/%.o : $(CORE_DIR)/%.cpp
	$(CC) $(F_FLAGS) -c $< -o $@

$(CURVE_OBJECTS): $(BUILDDIR)/%.o : $(CURVE_DIR)/%.cpp
	$(CC) $(F_FLAGS) -c $< -o $@

$(PRIMITIVE_OBJECTS): $(BUILDDIR)/%.o : $(PRIMITIVE_DIR)/%.cpp
	$(CC) $(F_FLAGS) -c $< -o $@

$(SURFACE_OBJECTS): $(BUILDDIR)/%.o : $(SURFACE_DIR)/%.cpp
	$(CC) $(F_FLAGS) -c $< -o $@

$(GLWRAPPERS_OBJECTS): $(BUILDDIR)/%.o : $(GLWRAPPERS_DIR)/%.cpp
	$(CC) $(F_FLAGS) -c $< -o $@

clean:
	rm -f $(BUILDDIR)/*o

dir:
	mkdir -p $(BUILDDIR)

tp3:  $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS)
	make dir
	$(CC) $(F_FLAGS) $^ $(SOURCE_DIR)/$@/$@.cpp -o $@.out $(L_FLAGS)

tp4/Cylinder:  $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(PRIMITIVE_OBJECTS) $(SOURCE_DIR)/tp4/mainCylinder.cpp
	make dir
	$(CC) $(F_FLAGS) $^ -o drawCylinder.out $(L_FLAGS)

tp4/Sphere:  $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(PRIMITIVE_OBJECTS) $(SOURCE_DIR)/tp4/mainSphere.cpp
	make dir
	$(CC) $(F_FLAGS) $^  -o drawSphere.out $(L_FLAGS)

tp4/Cone:  $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(PRIMITIVE_OBJECTS) $(SOURCE_DIR)/tp4/mainCone.cpp
	make dir
	$(CC) $(F_FLAGS) $^  -o drawCone.out $(L_FLAGS)

tp5/voxel: $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(PRIMITIVE_OBJECTS) $(GLWRAPPERS_OBJECTS) $(SOURCE_DIR)/tp5/voxel.cpp
	make dir
	$(CC) $(F_FLAGS) $^ -o voxel.out $(L_FLAGS)