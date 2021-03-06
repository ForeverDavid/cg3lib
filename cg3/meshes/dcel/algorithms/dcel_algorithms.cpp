/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_algorithms.h"
#include <cg3/utilities//utils.h>

namespace cg3 {

/**
 * @brief DcelAlgorithms::getVectorFaces
 * @param vector
 * @param d
 */
void dcelAlgorithms::getVectorFaces(std::vector<const Dcel::Face*>& vector, const Dcel& d)
{
    int i = 0;
    vector.resize(d.getNumberFaces());
    for (const Dcel::Face* f : d.faceIterator()){
        vector[i++] = f;
    }
}

void dcelAlgorithms::getVectorFaces(std::vector<Dcel::Face*>& vector, Dcel& d)
{
    int i = 0;
    vector.resize(d.getNumberFaces());
    for (Dcel::Face* f : d.faceIterator()){
        vector[i++] = f;
    }
}

void dcelAlgorithms::getVectorMesh(
        std::vector<Pointd>& coords,
        std::vector<std::vector<int> >& faces,
        const Dcel& d,
        std::vector<const Dcel::Vertex*>& mappingVertices,
        std::vector<const Dcel::Face*>& mappingFaces)
{
    std::map<const Dcel::Vertex*, int> vertices;
    int nv = 0, nf = 0;
    coords.resize(d.getNumberVertices());
    mappingVertices.resize(d.getNumberVertices());
    faces.resize(d.getNumberFaces());
    mappingFaces.resize(d.getNumberFaces());

    for (const Dcel::Vertex* v : d.vertexIterator()) {
        coords[nv] = v->getCoordinate();
        mappingVertices[nv] = v;
        vertices[v] = nv++;
    }

    for (const Dcel::Face* f : d.faceIterator()) {
        std::vector<int> face;
        for (const Dcel::Vertex* inc : f->incidentVertexIterator()){
            face.push_back(vertices[inc]);
        }
        faces[nf] = face;
        mappingFaces[nf++] = f;
    }
}

void dcelAlgorithms::smartColoring(Dcel& d)
{
    struct adjComp {
        std::set<Dcel::Face*> getAdjacences(Dcel::Face* f){
            std::set<Dcel::Face*> adjacents;
            for (Dcel::Face* adj : f->adjacentFaceIterator()){
                adjacents.insert(adj);
            }
            return adjacents;
        }
    };

    std::vector<Dcel::Face*> vectorFaces;
    getVectorFaces(vectorFaces, d);
    std::map<Dcel::Face*, Color> mapColors = smartColoring(vectorFaces, adjComp());

    for (std::pair<Dcel::Face*, Color> p : mapColors){
        (p.first)->setColor(p.second);
    }
}

} //namespace cg3
