#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

!contains(DEFINES, CG3_CORE_DEFINED){
    error(Algorithms module requires Core module!)
}

DEFINES += CG3_ALGORITHMS_DEFINED
MODULES += CG3_ALGORITHMS

HEADERS += \
    $$PWD/algorithms/convexhull.h \
    $$PWD/algorithms/2d/convexhull2d.h \
    $$PWD/algorithms/2d/convexhull2d_incremental.h \
    $$PWD/algorithms/graph_algorithms.h \
    $$PWD/algorithms/sphere_coverage.h \
    $$PWD/algorithms/global_optimal_rotation_matrix.h

SOURCES += \
    $$PWD/algorithms/convexhull.tpp \
    $$PWD/algorithms/2d/convexhull2d.tpp  \
    $$PWD/algorithms/2d/convexhull2d_incremental.tpp \
    $$PWD/algorithms/graph_algorithms.tpp \
    $$PWD/algorithms/sphere_coverage.tpp \
    $$PWD/algorithms/global_optimal_rotation_matrix.cpp
