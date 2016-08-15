#ifndef PLANET_H
#define PLANET_H

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
#include <vector>
#include <SOIL/SOIL.h>
#include "orbit.hpp"
#include "rings.hpp"

#define  DETAIL 50

struct PlanetAttrib
{
    /*The equatorial radius of the planet*/
    GLdouble radius;

    /*The amount of time to rotate about the planet's axis in days*/
    GLdouble rotationalPeriod;

    /*The obliquity of the planets axis to the orbit*/
    GLdouble axialTilt;
};

class Planet
{
    private:
        /*The equatorial radius of planet.*/
        GLdouble mRadius;

        /*The tilt of planet's axis from vertical in degrees.*/
        GLdouble mAxialTilt;

        /*The time in days for the planet to rotate about its axis.*/
        GLdouble mRotationalPeriod;

        /*The texture id for planet.*/
        GLuint mTextureId;

        /*The pointer to quadric object for drawing planet.*/
        GLUquadric* mpQuadric;

        /*A pointer to an orbit object for the planet.*/
        Orbit* mpOrbit;

        /*Moons*/
        Planet* mpMoon;

        /*Rings*/
        Rings* mpRings;

    public:
        /*
         * Creates a planet object at (0, 0, 0) with a given radius,
         * texture and axial tilt.
         *
         * @param radius - The equatorial radius of the planet.
         * @param axialTilt - The The tilt of planet's axis from
         *     vertical in degrees.
         * @param rotationalPeriod - The time  in daysto complete one
         *     rotation about the planet's axis.
         * @param texture - The path to the texture file to load on
         *     the planet.
         */
        Planet(GLdouble radius, GLdouble axialTilt,
                GLdouble rotationalPeriod, const char* texture);

        /*
         * Creates a planet object at (0, 0, 0) with a given radius,
         * texture and axial tilt, that follows orbit specified by given parameters.
         *
         * @param radius - The equatorial radius of the planet.
         * @param axialTilt - The The tilt of planet's axis from
         *     vertical in degrees.
         * @param rotationalPeriod - The time  in daysto complete one
         *     rotation about the planet's axis.
         * @param texture - The path to the texture file to load on
         *     the planet.
         * @param periapsis - The minimum distance between the orbiting
         *     and the orbited objects.
         * @param apapsis - The maximum distance between the orbiting
         *     and the orbited objects.
         * @param eccentricity - The eccentricity of the orbit.
         * @param orbitalPeriod - The time in days to complete orbit.
         * @param orbitalInclination - The anle of inclination of the orbit in degrees.
         */
        Planet(GLdouble radius, GLdouble axialTilt, GLdouble rotationalPeriod,
                const char* texture, GLdouble periapsis, GLdouble apapsis,
                GLdouble eccentricity, GLdouble orbitalPeriod,
                GLdouble orbitalInclination);

        void orbit(GLdouble periapsis, GLdouble apapsis, GLdouble eccentricity,
                GLdouble orbitalPeriod, GLdouble orbitalInclination);

        /*Draw the planet at given time.*/
        void draw(GLint time);

        /*Add a moon that orbits the planet folling given orbital parameters.*/
        void moon(GLdouble radius, GLdouble axialTilt, GLdouble rotationalPeriod,
                    const char* texture, GLdouble periapsis, GLdouble apapsis,
                    GLdouble eccentricity, GLdouble orbitalPeriod,
                    GLdouble orbitalInclination);

        void rings(GLdouble inner, GLdouble outer, const char* texture);

        ~Planet();
};

#endif
