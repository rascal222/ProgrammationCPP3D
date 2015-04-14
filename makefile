CC = g++-4.9
F_FLAGS = -std=c++11
L_FLAGS = -lGL -lglut -lGLU -lm
BUILDDIR = build

SOURCE_DIR = src
CORE_DIR = $(SOURCE_DIR)/core
CURVE_DIR = $(SOURCE_DIR)/curves
PRIMITIVE_DIR = $(SOURCE_DIR)/primitives
SURFACE_DIR = $(SOURCE_DIR)/surfaces
GLWRAPPERS_DIR = $(SOURCE_DIR)/glWrappers
OCTREE_DIR = $(SOURCE_DIR)/octree
MESHING_DIR = $(SOURCE_DIR)/meshing
TP7_DIR = $(SOURCE_DIR)/tp7

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

SRC_OCTREE = $(wildcard $(OCTREE_DIR)/*.cpp)
OCTREE_OBJECTS = $(patsubst $(OCTREE_DIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC_OCTREE))

SRC_MESHING = $(wildcard $(MESHING_DIR)/*.cpp)
MESHING_OBJECTS = $(patsubst $(MESHING_DIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC_MESHING))


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

$(OCTREE_OBJECTS): $(BUILDDIR)/%.o : $(OCTREE_DIR)/%.cpp
	$(CC) $(F_FLAGS) -c $< -o $@

$(MESHING_OBJECTS): $(BUILDDIR)/%.o : $(MESHING_DIR)/%.cpp
	$(CC) $(F_FLAGS) -c $< -o $@

$(TP7_OBJECTS): $(BUILDDIR)/%.o : $(TP7_DIR)/%.cpp
	$(CC) $(F_FLAGS) -c $< -o $@

clean:
	rm -f $(BUILDDIR)/*o

dir:
	mkdir -p $(BUILDDIR)

tp3:  $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(GLWRAPPERS_OBJECTS)
	make dir
	$(CC) $(F_FLAGS) $^ $(SOURCE_DIR)/$@/$@.cpp -o $@.out $(L_FLAGS)

tp4/Cylinder:  $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(PRIMITIVE_OBJECTS) $(GLWRAPPERS_OBJECTS) $(SOURCE_DIR)/tp4/mainCylinder.cpp
	make dir
	$(CC) $(F_FLAGS) $^ -o drawCylinder.out $(L_FLAGS)

tp4/Sphere:  $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(PRIMITIVE_OBJECTS) $(GLWRAPPERS_OBJECTS) $(SOURCE_DIR)/tp4/mainSphere.cpp
	make dir
	$(CC) $(F_FLAGS) $^  -o drawSphere.out $(L_FLAGS)

tp4/Cone:  $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(PRIMITIVE_OBJECTS) $(GLWRAPPERS_OBJECTS) $(SOURCE_DIR)/tp4/mainCone.cpp
	make dir
	$(CC) $(F_FLAGS) $^  -o drawCone.out $(L_FLAGS)

tp5/drawVoxelSphere: $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(PRIMITIVE_OBJECTS) $(GLWRAPPERS_OBJECTS) $(OCTREE_OBJECTS) $(SOURCE_DIR)/tp5/voxel.cpp
	make dir
	$(CC) $(F_FLAGS) $^ -o drawVoxelSphere.out $(L_FLAGS)

tp5/drawVoxelCylinder: $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(PRIMITIVE_OBJECTS) $(GLWRAPPERS_OBJECTS) $(OCTREE_OBJECTS) $(SOURCE_DIR)/tp5/mainCylinder.cpp
	make dir
	$(CC) $(F_FLAGS) $^ -o drawVoxelCylinder.out $(L_FLAGS)

tp5/drawVoxelIntersection: $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(PRIMITIVE_OBJECTS) $(GLWRAPPERS_OBJECTS) $(OCTREE_OBJECTS) $(SOURCE_DIR)/tp5/mainIntersect.cpp
	make dir
	$(CC) $(F_FLAGS) $^ -o drawVoxelIntersection.out $(L_FLAGS)

tp5/drawVoxelDivision: $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(PRIMITIVE_OBJECTS) $(GLWRAPPERS_OBJECTS) $(OCTREE_OBJECTS) $(SOURCE_DIR)/tp5/mainDivide.cpp
	make dir
	$(CC) $(F_FLAGS) $^ -o drawVoxelDivision.out $(L_FLAGS)

tp5/drawVoxelUnion: $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(PRIMITIVE_OBJECTS) $(GLWRAPPERS_OBJECTS) $(OCTREE_OBJECTS) $(SOURCE_DIR)/tp5/mainUnion.cpp
	make dir
	$(CC) $(F_FLAGS) $^ -o drawVoxelUnion.out $(L_FLAGS)

tp6/offReader: $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(PRIMITIVE_OBJECTS) $(GLWRAPPERS_OBJECTS) $(OCTREE_OBJECTS) $(MESHING_OBJECTS) $(SOURCE_DIR)/tp6/mainOffReader.cpp
	make dir
	$(CC) $(F_FLAGS) $^ -o offReader.out $(L_FLAGS)


tp7/TopoCylinder: $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(PRIMITIVE_OBJECTS) $(GLWRAPPERS_OBJECTS) $(OCTREE_OBJECTS) $(MESHING_OBJECTS) $(SOURCE_DIR)/tp7/mainTp7Cylinder.cpp
	make dir
	$(CC) $(F_FLAGS) $^ -o topoCylinder.out $(L_FLAGS)

tp7/TopoCylinderActiveEdge: $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(PRIMITIVE_OBJECTS) $(GLWRAPPERS_OBJECTS) $(OCTREE_OBJECTS) $(MESHING_OBJECTS) $(SOURCE_DIR)/tp7/mainTp7Cylinder-active-edges.cpp
	make dir
	$(CC) $(F_FLAGS) $^ -o topoCylinderActiveEdge.out $(L_FLAGS)

tp7/TopoSphere: $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(PRIMITIVE_OBJECTS) $(GLWRAPPERS_OBJECTS) $(OCTREE_OBJECTS) $(MESHING_OBJECTS) $(SOURCE_DIR)/tp7/mainTp7Sphere.cpp
	make dir
	$(CC) $(F_FLAGS) $^ -o topoSphereActiveEdge.out $(L_FLAGS)

tp7/TopoSphere: $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(PRIMITIVE_OBJECTS) $(GLWRAPPERS_OBJECTS) $(OCTREE_OBJECTS) $(MESHING_OBJECTS) $(SOURCE_DIR)/tp7/mainTp7Sphere-active-edges.cpp
	make dir
	$(CC) $(F_FLAGS) $^ -o topoSphereActiveEdge.out $(L_FLAGS)

tp7/TopoGaussianCylinder: $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(PRIMITIVE_OBJECTS) $(GLWRAPPERS_OBJECTS) $(OCTREE_OBJECTS) $(MESHING_OBJECTS) $(SOURCE_DIR)/tp7/mainTp7GaussianSphere.cpp
	make dir
	$(CC) $(F_FLAGS) $^ -o topoGaussianCylinder.out $(L_FLAGS)

tp8/SegmentationByActiveEdge: $(CORE_OBJECTS) $(SURFACE_OBJECTS) $(CURVE_OBJECTS) $(PRIMITIVE_OBJECTS) $(GLWRAPPERS_OBJECTS) $(OCTREE_OBJECTS) $(MESHING_OBJECTS) $(SOURCE_DIR)/tp8/mainSegmentation.cpp
	make dir
	$(CC) $(F_FLAGS) $^ -o tp8Segmentation.out $(L_FLAGS)