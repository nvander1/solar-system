/*
 * Copyright (C) 2016  Nikolas Vanderhoof
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cmath>
#include <GL/glut.h>
#include "orbit.hpp"

Orbit::Orbit(GLdouble periapsis, GLdouble apapsis, GLdouble eccentricity,
        GLdouble orbitalPeriod, GLdouble orbitalInclination)
{
    mSemimajor = (periapsis + apapsis) / 2;
    mSemiminor = mSemimajor * std::sqrt(1 - eccentricity * eccentricity);
    mSemifocus = -1 * std::sqrt(mSemimajor*mSemimajor - mSemiminor*mSemiminor);
    mOrbitalPeriod = orbitalPeriod;
    mOrbitalInclination = orbitalInclination;
}

Point Orbit::position(GLint time)
{
    /*Calculate angle around ellipse.*/
    GLdouble angle = (time/mOrbitalPeriod) * 2 * M_PI;
    /*Calculate x,y coordinates.*/
    Point p = {mSemimajor*cos(angle), mSemiminor*sin(angle)};
    return p;
}

void Orbit::transform(GLint time)
{
    /*Calculate point on orbit cenetered in xy plane.*/
    Point p = position(time);

    /*Tilt orbit.*/
    glRotated(mOrbitalInclination, 0.0, 1.0, 0.0);
    /*Translate to move orbited body to focus from center.*/
    glTranslated(mSemifocus, 0.0, 0.0);
    /*Move to path along ellipse.*/
    glTranslated(p.x, p.y, 0.0);
}
