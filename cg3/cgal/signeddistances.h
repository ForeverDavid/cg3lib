/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_CGAL_SIGNEDDISTANCES_H
#define CG3_CGAL_SIGNEDDISTANCES_H

#include <cg3/utilities/utils.h>
#include <cg3/geometry/point.h>
#include <cg3/geometry/2d/point2d.h>

#include "aabbtree.h"

namespace cg3 {
namespace cgal {

std::vector<double> getUnsignedDistances(const std::vector<Pointd> &points, const AABBTree &tree);

} //namespace cg3::cgal
} //namespace cg3

#endif // CG3_CGAL_SIGNEDDISTANCES_H
