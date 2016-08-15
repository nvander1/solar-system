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
#include <SOIL/SOIL.h>
#include "rings.hpp"

Rings::Rings(GLdouble inner, GLdouble outer, const char* texture)
{
    mInner = .5*log2(inner);
    mOuter = .5*log2(outer);

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
}

Rings::~Rings()
{
    gluDeleteQuadric(mpQuadric);
}

void Rings::draw()
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    glScalef(1.0, 1.2, 1.0);
    gluDisk(mpQuadric, mInner, mOuter, RING_DETAIL, RING_DETAIL);
    glPopMatrix();
}
