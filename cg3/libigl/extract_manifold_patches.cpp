#include "extract_manifold_patches.h"

#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {

namespace libigl {

int extractManifoldPatches(const SimpleEigenMesh &m, Eigen::Matrix<int, Eigen::Dynamic, 1> &I) {
    return internal::EigenMeshLibIglAlgorithms::extractManifoldPatches(m, I);
}

int extractManifoldPatches(const SimpleEigenMesh &m){
    Eigen::VectorXi I;
    return internal::EigenMeshLibIglAlgorithms::extractManifoldPatches(m, I);
}

}

}
