#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <math.h>
#include "./map.cpp"
#include "./cells/cell.cpp"
#include "./colors/colors.cpp"
#include <cstdlib>
#include <unistd.h>
using namespace std;


bool leftMouseButtonDown = false;
bool rightMouseButtonDown = false;
int mouseXPos = 0;
int mouseYPos = 0;
double cameraY = 0;
double cameraAngle = 0;
double cameraZoom = 10;
bool pauseGame = true;
int window1;
int window2;
GameMap map;

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void idle(void)
{
    if (!pauseGame)
    {
        map.updateMapState();
        usleep(100000);
    }
    glutPostRedisplay();
    if (glutGetWindow() != window1)
    {
        glutSetWindow(window1);
    } else
    {
        glutSetWindow(window2);
    }
    glutPostRedisplay();
}

void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
    case 'q':
    {
        exit(EXIT_SUCCESS);
        break;
    }
    case 'p':
    {
        pauseGame = !pauseGame;
        break;
    }
    }
    glutPostRedisplay();
}

// * ---- 2D -----

void display2D(void)
{
    glClearColor(0.1, 0.3, 0.1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (map.getMapValue(i, j) == 1)
            {
                glColor3f(1, 1, 1);
            }
            else
            {
                glColor3f(0, 0, 0);
            }
            drawSquare(-200 + (j * 20), 200 - (i * 20), 20);
            glColor3f(0.5, 0.5, 0.5);
            drawLines(-200 + (j * 20), 200 - (i * 20), 20);
        }
    }
    // drawString(0.0, 0.0, 0.0, "Esto es una prueba");
    glutSwapBuffers();
}

void mouse2D(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        cout << "WINDOW " << glutGet(GLUT_WINDOW_WIDTH) << ", " << glutGet(GLUT_WINDOW_HEIGHT) << endl;
        int i = y/(glutGet(GLUT_WINDOW_HEIGHT)/20);
        int j = x/(glutGet(GLUT_WINDOW_WIDTH)/20);
        cout << i << "," << j << endl;
        cout << "Left mouse button pressed at " << x << ", " << y << endl;
        map.updateMapValue(i, j);
    }

    glutPostRedisplay();
}

// * ---- 3D -----

void display3D(void)
{
    glClearColor(0, 0, 0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    double cameraX = cos(cameraAngle) * cameraZoom;
    double cameraZ = sin(cameraAngle) * cameraZoom;
    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    Ejes(3);

    glPushMatrix();
    glScalef(0.05, 0.05, 0.05);
    Cell(red);
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void mouse3D(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        leftMouseButtonDown = (state == GLUT_DOWN);
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        rightMouseButtonDown = (state == GLUT_DOWN);
    }
    else if (button == 3)
    {
        cameraZoom -= 0.1;
    }
    else if (button == 4)
    {
        cameraZoom += 0.1;
    }

    glutPostRedisplay();
}

void mouseMotion3D(int x, int y)
{
    if (leftMouseButtonDown)
    {
        if (x > mouseXPos)
            cameraAngle += 0.01;
        else if (x < mouseXPos)
            cameraAngle -= 0.01;
        if (y > mouseYPos)
            cameraY += 0.1;
        else if (y < mouseYPos)
            cameraY -= 0.1;
    }
    mouseXPos = x;
    mouseYPos = y;
    cout << "x: " << x << " y: " << y << endl;
    glutPostRedisplay();
}
