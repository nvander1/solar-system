#ifndef RINGS_H
#define RINGS_H

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

#define RING_DETAIL 500

struct RingAttrib
{
    GLdouble inner;
    GLdouble outer;
};

class Rings {
    private:
        /*Inner diameter of rings in kilometers.*/
        GLdouble mInner;

        /*Outer diameter of rings in kilometers.*/
        GLdouble mOuter;

        /*OpenGL texture ID.*/
        GLuint mTextureId;

        /*Pointer to quadric object used to render rings.*/
        GLUquadric* mpQuadric;
    public:
        Rings(GLdouble inner, GLdouble outer, const char* texture);
        ~Rings();

        void draw();
};

#endif
