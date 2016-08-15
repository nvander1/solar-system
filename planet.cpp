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

#include <GL/glut.h>
#include <cmath>
#include <SOIL/SOIL.h>
#include "planet.hpp"

void Planet::rings(GLdouble inner, GLdouble outer, const char* texture)
{
    mpRings = new Rings(inner, outer, texture);
}

void Planet::moon(GLdouble radius, GLdouble axialTilt, GLdouble rotationalPeriod,
        const char* texture, GLdouble periapsis, GLdouble apapsis,
        GLdouble eccentricity, GLdouble orbitalPeriod,
        GLdouble orbitalInclination)
{
    mpMoon = new Planet(.25*radius, axialTilt, rotationalPeriod, texture, periapsis,
            apapsis, eccentricity, orbitalPeriod, orbitalInclination);
}

void Planet::orbit(GLdouble periapsis, GLdouble apapsis, GLdouble eccentricity,
        GLdouble orbitalPeriod, GLdouble orbitalInclination)
{
    if (mpOrbit) {
        delete mpOrbit;
    }

    mpOrbit = new Orbit(periapsis, apapsis, eccentricity,
            orbitalPeriod, orbitalInclination);
}

Planet::Planet(GLdouble radius, GLdouble axialTilt,
        GLdouble rotationalPeriod, const char* texture)
{
    mRadius = .25 * log2(radius);
    mAxialTilt = axialTilt;
    mRotationalPeriod = rotationalPeriod;

    mTextureId = SOIL_load_OGL_texture
        (
         texture,
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
         SOIL_FLAG_MIPMAPS
        );

    mpQuadric = gluNewQuadric();
    gluQuadricDrawStyle(mpQuadric, GLU_FILL);
    gluQuadricTexture(mpQuadric, GL_TRUE);
    gluQuadricNormals(mpQuadric, GLU_SMOOTH);

    mpOrbit = NULL;
    mpMoon = NULL;
    mpRings = NULL;
}


Planet::Planet(GLdouble radius, GLdouble axialTilt, GLdouble rotationalPeriod,
        const char* texture, GLdouble periapsis, GLdouble apapsis,
        GLdouble eccentricity, GLdouble orbitalPeriod,
        GLdouble orbitalInclination)
{
    mRadius = .25 * log2(radius);
    mAxialTilt = axialTilt;
    mRotationalPeriod = rotationalPeriod;

    mTextureId = SOIL_load_OGL_texture
        (
         texture,
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
         SOIL_FLAG_MIPMAPS
        );

    mpQuadric = gluNewQuadric();
    gluQuadricDrawStyle(mpQuadric, GLU_FILL);
    gluQuadricTexture(mpQuadric, GL_TRUE);
    gluQuadricNormals(mpQuadric, GLU_SMOOTH);

    mpOrbit = new Orbit(periapsis, apapsis, eccentricity,
            orbitalPeriod, orbitalInclination);

    mpMoon = NULL;
    mpRings = NULL;
}

void Planet::draw(GLint time)
{
    GLdouble angle = (time/mRotationalPeriod) * 2 * M_PI;

    if (!mpOrbit) {
        glPushMatrix();
        /*Rotate about axis.*/
        glRotated(angle, 0.0, 0.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, mTextureId);
        gluSphere(mpQuadric, mRadius, DETAIL, DETAIL);
        glPopMatrix();
    } else {
        glPushMatrix();
        /*Apply transformations for orbit.*/
        mpOrbit->transform(time);

        /*Draw moon, if there is one.*/
        if (mpMoon) {
            mpMoon->draw(time);
        }
        if (mpRings) {
            mpRings->draw();
        }

        /*Rotate about axis.*/
        glRotated(angle, 0.0, 0.0, 1.0);
        /*Add texture and draw.*/
        glBindTexture(GL_TEXTURE_2D, mTextureId);
        gluSphere(mpQuadric, mRadius, DETAIL, DETAIL);
        glPopMatrix();
    }
}

Planet::~Planet()
{
    gluDeleteQuadric(mpQuadric);
    if (mpOrbit) delete mpOrbit;
    if (mpMoon) delete mpMoon;
}
