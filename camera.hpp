#ifndef CAMERA_H
#define CAMERA_H

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

class Camera {
    public:
        double xPos;
        double yPos;
        double zPos;

        double xLook;
        double yLook;
        double zLook;

        double xUp;
        double yUp;
        double zUp;

        double mR;
        double mTheta;
        double mPhi;

        Camera(double r, double theta, double phi);

        void update();

        void view();
};

#endif
