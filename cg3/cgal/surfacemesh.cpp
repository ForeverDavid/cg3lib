/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "surfacemesh.h"

namespace cg3 {
namespace cgal {
namespace internal {

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef SurfaceMesh::Vertex_index VertexDescriptor;

} //namespace cg3::cgal::internal

#ifdef CG3_DCEL_DEFINED
/**
 * @ingroup cg3cgal
 * @brief getSurfaceMeshFromDcel
 * @param d
 * @return
 */
SurfaceMesh getSurfaceMeshFromDcel(const Dcel &d)
{
    SurfaceMesh mesh;
    std::map<const Dcel::Vertex*, internal::VertexDescriptor> mapV;
    for(const Dcel::Vertex* v : d.vertexIterator()){
        internal::VertexDescriptor vd = mesh.add_vertex((internal::K::Point_3(v->getCoordinate().x(),v->getCoordinate().y(),v->getCoordinate().z())));
        mapV[v] = vd;
    }
    for (const Dcel::Face* f : d.faceIterator()){
        std::list<internal::VertexDescriptor> lv;
        for (const Dcel::Vertex* v : f->incidentVertexIterator()){
            lv.push_back(mapV.at(v));
        }
        mesh.add_face(lv);
    }
    return mesh;
}
#endif

} //namespace cg3::cgal
} //namespace cg3

