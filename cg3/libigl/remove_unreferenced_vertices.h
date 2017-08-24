#ifndef CG3_REMOVE_UNREFERENCED_VERTICES_H
#define CG3_REMOVE_UNREFERENCED_VERTICES_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {

namespace libigl {

void removeUnreferencedVertices(SimpleEigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I);
void removeUnreferencedVertices(SimpleEigenMesh &input);

}

}

#endif // CG3_REMOVE_UNREFERENCED_VERTICES_H
