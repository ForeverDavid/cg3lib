#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

CONFIG += c++11
#CONFIG += object_parallel_to_source #allows the compilation of files with same name inside the project

CG3_ALL {
    CONFIG += CG3_CORE CG3_DATA_STRUCTURES CG3_MESHES CG3_ALGORITHMS CG3_CGAL CG3_CINOLIB CG3_LIBIGL CG3_VIEWER
}

CG3_CORE {
    include (cg3/core.pri)
}

CG3_DATA_STRUCTURES {
    include (cg3/data_structures.pri)
}

CG3_MESHES {
    include (cg3/meshes.pri)
}

CG3_ALGORITHMS {
    include (cg3/algorithms.pri)
}

CG3_CGAL {
    include (cg3/cgal.pri)
}

CG3_CINOLIB {
     include (cg3/cinolib.pri)
}

CG3_LIBIGL {
    include (cg3/libigl.pri)
}

qt {
    CG3_VIEWER {
        include (cg3/viewer.pri)
    }
}

CG3_DEVELOPMENT {
    include (cg3/development.pri)
}

CG3_DEPRECATED {
    include (cg3/deprecated.pri)
}

CG3_EXAMPLES {
    include (cg3/examples.pri)
}


DISTFILES += \
    $$PWD/LICENSE \
    $$PWD/README.md \
    $$PWD/TODO.md

INCLUDEPATH += $$PWD
