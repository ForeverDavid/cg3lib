DEFINES += CG3_ALGORITHMS_DEFINED
CONFIG += CG3_ALGORITHMS
MODULES += CG3_ALGORITHMS

!contains(DEFINES, CG3_CORE_DEFINED){
    error(Algorithms module requires cg3_core!)
}

HEADERS += \
    $$PWD/algorithms/convexhull.h \
    $$PWD/algorithms/marching_cubes.h \
    $$PWD/algorithms/2d/convexhull2d.h \
    $$PWD/algorithms/2d/convexhull2d_iterative.h

SOURCES += \
    $$PWD/algorithms/convexhull.cpp \
    $$PWD/algorithms/marching_cubes.cpp \
    $$PWD/algorithms/2d/convexhull2d.tpp \
    $$PWD/algorithms/2d/convexhull2d_iterative.tpp
