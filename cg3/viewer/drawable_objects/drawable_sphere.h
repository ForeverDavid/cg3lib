/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_SPHERE_H
#define CG3_DRAWABLE_SPHERE_H

#include "../interfaces/drawable_object.h"
#include <cg3/geometry/sphere.h>

namespace cg3 {

class DrawableSphere : public Sphere, public DrawableObject
{
public:
    DrawableSphere();
    DrawableSphere(
            const Pointd& _center,
            double _radius,
            QColor color = QColor(128,128,128),
            int precision = 10);

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;

protected:
    QColor color;
    int precision;

};

}

#endif // CG3_DRAWABLE_SPHERE_H
