#ifndef ORBIT_H
#define ORBIT_H

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

struct Point
{
    GLdouble x;
    GLdouble y;
};

struct OrbitAttrib
{
    /*The minimum distance from orbited object*/
    GLdouble periapsis;

    /*The maxium distance from orbited object*/
    GLdouble apapsis;

    /*The eccentricity of the orbit*/
    GLdouble eccentricity;

    /*The angle between the planets orbit and the orbited's equator*/
    GLdouble orbitalInclination;

    /*The amount of time to complete the orbit in days*/
    GLdouble orbitalPeriod;
};

class Orbit
{
    private:
        /*The farthest distance from the center of the ellipse.*/
        GLdouble mSemimajor;

        /*The shortest distance from the center of the ellipse.*/
        GLdouble mSemiminor;

        /*Distance from center to main focus.*/
        GLdouble mSemifocus;

        /*Time in days to complete orbit.*/
        GLdouble mOrbitalPeriod;

        /*Angle of inclination of orbit in degrees.*/
        GLdouble mOrbitalInclination;

        /*Gets the position of the planet on its elliptical orbit.*/
        Point position(GLint time);

    public:
        /*
         * An elliptical orbit of one object around another.
         *
         * @param periapsis - The minimum distance between the orbiting
         *     and the orbited objects.
         * @param apapsis - The maximum distance between the orbiting
         *     and the orbited objects.
         * @param eccentricity - The eccentricity of the orbit.
         * @param orbitalPeriod - The time in days to complete orbit.
         * @param orbitalInclination - The anle of inclination of the orbit in degrees.
         */
        Orbit(GLdouble periapsis, GLdouble apapsis, GLdouble eccentricity,
             GLdouble orbitalPeriod, GLdouble orbitalInclination);

        /*
         * Apply transformation matrices for orbit at a given time.
         *
         * @param time - The given time.
         */
        void transform(GLint time);
};

#endif
