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

#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include "main.hpp"
#include "planet.hpp"
#include "camera.hpp"

float day = 0;

int w;
int h;

Camera cam(100, 90.1, 90);

GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0};
GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};

GLuint sunTex;
GLuint skybox;

GLUquadric* sun;
GLUquadric* sky;
Planet* planets[9];
RingAttrib saturnrings = {66900, 480000};

OrbitAttrib orbitData[] = {
    /*Mercury*/ {4.60e7, 6.98e7, 0.2056, 3.38, 87.969},
    /*Venus*/ {1.07e8, 1.09e8, 0.0067, 3.86, 224.701},
    /*Earth*/ {1.47e8, 1.52e8, 0.0167, 7.16, 365.256},
    /*Mars*/ {2.07e8, 2.49e8, 0.0935, 5.65, 686.98},
    /*Jupiter*/ {7.41e8, 8.17e8, 0.0489, 3.13, 4332.589,},
    /*Saturn*/ {1.35e9, 1.51e9, 0.0565, 5.51, 10759.22},
    /*Uranus*/ {2.74e9, 3.00e9, 0.0457, 6.48, 30685.4},
    /*Neptune*/ {4.44e9, 4.55e9, 0.0113, 6.43, 60189},
    /*Moon*/ {362600, 405400, 0.0549, 5.145, 27.321661}
};

PlanetAttrib planetData[] = {
    /*Mercury*/ {2439.7, 58.65, 0.034},
    /*Venus*/ {6051.8, 243.025, 177.36},
    /*Earth*/ {6378.137, 0.997271, 23.44},
    /*Mars*/ {3396.2, 1.025954, 25.19},
    /*Jupiter*/ {71492, 0.413542, 6.09},
    /*Saturn*/ {60268, 0.444, 26.73},
    /*Uranus*/ {25559, 0.718333, 97.77},
    /*Neptune*/ {24764, 0.67125, 28.32},
    /*Moon*/ {1738.1, 27.321661, 6.687}
};

const char* images[] = {
    "images/textures/mercury.jpg",
    "images/textures/venus.jpg",
    "images/textures/earth.jpg",
    "images/textures/mars.jpg",
    "images/textures/jupiter.jpg",
    "images/textures/saturn.jpg",
    "images/textures/uranus.jpg",
    "images/textures/neptune.jpg",
    "images/textures/suncyl1.jpg",
    "images/textures/moon.jpg",
    "images/textures/saturnringcolor.jpg",
    "images/textures/uranusringcolor.jpg"
};

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
    cam.view();

    glDisable(GL_LIGHTING);
    /*Background*/
    glBindTexture(GL_TEXTURE_2D, skybox);
    gluSphere(sky, (GLdouble) 1000000, (GLint) 10000, (GLint) 10000);
    /*Sun*/
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, sunTex);
        glRotated(day/26.6 * 2 * M_PI, 0.0, 0.0, 1.0);
        gluSphere(sun, (GLdouble) 19.40871, (GLint) 900, (GLint) 900);
    glPopMatrix();
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    for (int i = 0; i < 8; i++) {
        planets[i]->draw(day);
    }

    day += 0.5;
    glutSwapBuffers();
    glutPostRedisplay();
}

void init()
{
    // Paint it black
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    for (int i = 0; i < 9; i++) {
        planets[i] = new Planet(
                planetData[i].radius,
                planetData[i].axialTilt,
                planetData[i].rotationalPeriod,
                images[i],
                // planetData[i].aphelion,
                // planetData[i].perihelion,
                // too far apart
                (i+1) * 30,
                (i+1) * 30,
                orbitData[i].eccentricity,
                orbitData[i].orbitalPeriod,
                orbitData[i].orbitalInclination
                );
    }

    planets[2]->moon(
            planetData[8].radius,
            planetData[8].axialTilt,
            planetData[8].rotationalPeriod,
            images[9],
            8,
            10,
            orbitData[8].eccentricity,
            orbitData[8].orbitalPeriod,
            orbitData[8].orbitalInclination
            );

    planets[5]->rings(
            saturnrings.inner,
            saturnrings.outer,
            images[10]
            );

    /* setup sun*/
    sun = gluNewQuadric();
    gluQuadricDrawStyle(sun, GLU_FILL);
    gluQuadricTexture(sun, GL_TRUE);
    gluQuadricNormals(sun, GLU_SMOOTH);
    sunTex = SOIL_load_OGL_texture(images[8], SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
            SOIL_FLAG_NTSC_SAFE_RGB);

    /*setup sky*/
    sky = gluNewQuadric();
    gluQuadricDrawStyle(sky, GLU_FILL);
    gluQuadricTexture(sky, GL_TRUE);
    gluQuadricNormals(sky, GLU_SMOOTH);
    skybox = SOIL_load_OGL_texture("images/textures/space.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS);

}

void reshape(int pw, int ph)
{
    w = pw;
    h = ph;
    if (h == 0) h = 1;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45, 2*(float)(w/h), 1, 10000000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case '=':
            if (cam.mR > 25) {
                cam.mR -=5;
                cam.update();
                glutPostRedisplay();
            }
            break;
        case '-':
            cam.mR += 5;
            cam.update();
            glutPostRedisplay();
            break;
        case 'a':
            cam.mTheta += 1;
            cam.update();
            glutPostRedisplay();
            break;
        case 'd':
            cam.mTheta -= 1;
            cam.update();
            glutPostRedisplay();
            break;
        case 'w':
            if (cam.mPhi < 180) {
                cam.mPhi += 1;
                cam.update();
                glutPostRedisplay();
            }
            break;
        case 's':
            if (cam.mPhi > 1) {
                cam.mPhi -= 1;
                cam.update();
                glutPostRedisplay();
            }
            break;
        default:
            break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    /*Create a window 75% of screen size and center it.*/
    int screen_w = glutGet(GLUT_SCREEN_WIDTH);
    int screen_h = glutGet(GLUT_SCREEN_HEIGHT);
    int window_w = screen_w * .75;
    int window_h = screen_h * .75;
    int x_pos = (screen_w - window_w) / 2;
    int y_pos = (screen_h - window_h) / 2;
    glutInitWindowSize(window_w, window_h);
    glutInitWindowPosition(x_pos, y_pos);
    glutCreateWindow("Solar System Model");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}
