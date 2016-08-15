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
#include "camera.hpp"

double toRad = M_PI / 180;

Camera::Camera(double r, double theta, double phi)
{
    mR = r;
    mTheta = theta;
    mPhi = phi;

    update();

    xLook = 0.0;
    yLook = 0.0;
    zLook = 0.0;

    xUp = 0.0;
    yUp = 0.0;
    zUp = -1.0;
}

void Camera::update()
{
    xPos = mR*sin(mPhi*toRad)*cos(mTheta*toRad);
    yPos = mR*sin(mPhi*toRad)*sin(mTheta*toRad);
    zPos = mR*cos(mPhi*toRad);
}

void Camera::view()
{
    glLoadIdentity();
    gluLookAt(
            xPos, yPos, zPos,
            xLook, yLook, zLook,
            xUp, yUp, zUp
            );
}
