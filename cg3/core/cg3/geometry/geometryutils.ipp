#include "geometryutils.h"

#include <numeric>

namespace cg3 {

    /**
     * @brief Get the determinant of a 3x3 double matrix
     * @return Determinant of the matrix
     */
    inline double determinant3x3(double (*m)[3]) {
        return
                (m[0][0] * m[1][1] * m[2][2]) +
                (m[0][1] * m[1][2] * m[2][0]) +
                (m[0][2] * m[1][0] * m[2][1]) -
                (m[0][2] * m[1][1] * m[2][0]) -
                (m[0][1] * m[1][0] * m[2][2]) -
                (m[0][0] * m[1][2] * m[2][1]);
    }


    /**
     * @brief Check if a point is at the right of the line passing through the segment
     *
     * @param[in] s1 First point of the segment
     * @param[in] s2 Second point of the segment
     * @param[in] point Input point
     * @return True if the point is at the right of the line passing through
     * the segment, false otherwise
     *
     */
    template<typename T>
    inline bool isPointAtRight(const Point2D<T>& s1, const Point2D<T>& s2, const Point2D<T>& point) {
        double m[3][3];

        m[0][0] = (double) s1.x();
        m[0][1] = (double) s1.y();
        m[0][2] = 1.0;

        m[1][0] = (double) s2.x();
        m[1][1] = (double) s2.y();
        m[1][2] = 1.0;

        m[2][0] = (double) point.x();
        m[2][1] = (double) point.y();
        m[2][2] = 1.0;

        return determinant3x3(m) > -std::numeric_limits<double>::epsilon();
    }

    /**
     * @brief Check if a point is at the right of the line passing through the segment
     *
     * @param[in] segment Input segment
     * @param[in] point Input point
     * @return True if the point is at the right of the line passing through
     * the segment, false otherwise
     *
     */
    template<typename T>
    inline bool isPointAtRight(const Segment<Point2D<T>>& segment, const Point2D<T>& point) {
        return isPointAtRight<T>(segment.getP1(), segment.getP2(), point);
    }




    /**
     * @brief Check if a point lies in a triangle (endpoints included)
     *
     * Taken from
     * https://stackoverflow.com/questions/13300904/determine-whether-point-lies-inside-triangle
     *
     * @param[in] a First vertex coordinate of the triangle
     * @param[in] b Second vertex coordinate of the triangle
     * @param[in] c Third vertex coordinate of the triangle
     * @param[in] p Input point
     * @param[in] includeEndpoints True if we want to include the endpoints
     * @return True if the point lies inside the triangle
     */
    inline bool isPointLyingInTriangle(
            const Point2Dd& a,
            const Point2Dd& b,
            const Point2Dd& c,
            const Point2Dd& p,
            bool includeEndpoints)
    {
        double alpha = ((b.y() - c.y())*(p.x() - c.x()) + (c.x() - b.x())*(p.y() - c.y())) /
                ((b.y() - c.y())*(a.x() - c.x()) + (c.x() - b.x())*(a.y() - c.y()));
        double beta = ((c.y() - a.y())*(p.x() - c.x()) + (a.x() - c.x())*(p.y() - c.y())) /
               ((b.y() - c.y())*(a.x() - c.x()) + (c.x() - b.x())*(a.y() - c.y()));
        double gamma = 1.0f - alpha - beta;

        if (includeEndpoints) {
            if (
                    alpha >= -std::numeric_limits<double>::epsilon() &&
                    beta >= -std::numeric_limits<double>::epsilon() &&
                    gamma >= -std::numeric_limits<double>::epsilon())
            {
                return true;
            }
        }
        else {
            if (alpha > 0.0 && beta > 0.0 && gamma > 0.0) {
                return true;
            }
        }

        return false;
    }

    /**
     * @brief Check if a point lies inside a circle passing for three points
     * @param[in] a First coordinate of the circle
     * @param[in] b Third coordinate of the circle
     * @param[in] c Second coordinate of the circle
     * @param[in] p Input point
     * @param[in] includeEndpoints True if we want to include the endpoints
     * @return True if the point lies inside the circle
     */
    inline bool isPointLyingInCircle(
            const Point2Dd& a,
            const Point2Dd& b,
            const Point2Dd& c,
            const Point2Dd& p,
            bool includeEndpoints)
    {
        Eigen::Matrix4d A;

        A << a.x(), a.y(), a.x()*a.x() + a.y()*a.y(), 1,
                b.x(), b.y(), b.x()*b.x() + b.y()*b.y(), 1,
                c.x(), c.y(), c.x()*c.x() + c.y()*c.y(), 1,
                p.x(), p.y(), p.x()*p.x() + p.y()*p.y(), 1;

        if (includeEndpoints) {
            return (A.determinant() >= -std::numeric_limits<double>::epsilon());
        }
        else {
            return (A.determinant() > 0);
        }
    }

    /**
     * @brief Check if the triangulation is a Delaunay triangulation (brute force, O(n^2))
     * @param points Vector of points
     * @param triangles Vector of triangles (represented by a vector of three points)
     * @return
     */
    inline bool isDeulaunayTriangulation(
            const std::vector<Point2Dd>& points,
            const std::vector<std::vector<Point2Dd>>& trianglePoints)
    {
        for (const std::vector<Point2Dd>& triangle : trianglePoints) {
            const Point2Dd& a = triangle.at(0);
            const Point2Dd& b = triangle.at(1);
            const Point2Dd& c = triangle.at(2);

            for (const Point2Dd& p : points) {
                if (p != a && p != b && p != c) {
                    if (isPointLyingInCircle(a,b,c,p,false)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

}