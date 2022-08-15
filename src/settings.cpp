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
#include <string>
#include <cstring>
using namespace std;

float separation = 1;
float x_init = -10;
float y_init = -10;
bool leftMouseButtonDown = false;
bool rightMouseButtonDown = false;
int mouseXPos = 0;
int mouseYPos = 0;
double cameraY = 15;
double cameraAngle = 0;
double cameraZoom = 15;
bool pauseGame = true;
int window1;
int window2;
GameMap map;


void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 40.0);
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

    case ' ':
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
    int cellsAlive = map.getCellsAlive();
    string cellsAliveString = to_string(cellsAlive);
    string s = "Cells alive: " + cellsAliveString;
    int n = s.length();
    char char_array[n + 1];
    strcpy(char_array, s.c_str());
    drawString(-195.0, 185.0, 0.0, char_array, white);
    glutSwapBuffers();
}

void mouse2D(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // cout << "WINDOW " << glutGet(GLUT_WINDOW_WIDTH) << ", " << glutGet(GLUT_WINDOW_HEIGHT) << endl;
        int i = y/(glutGet(GLUT_WINDOW_HEIGHT)/20);
        int j = x/(glutGet(GLUT_WINDOW_WIDTH)/20);
        // cout << i << "," << j << endl;
        // cout << "Left mouse button pressed at " << x << ", " << y << endl;
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
    // Ejes(3);
    glColor3f(0.5, 0.5, 0.5);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex3f(-40, 0, 40);
    glVertex3f(-40, 0, -40);
    glVertex3f(40, 0, -40);
    glVertex3f(40, 0, 40);
    glEnd();

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            glPushMatrix();
            glTranslated(x_init + separation * i, 1, y_init + separation * j);
            glScalef(0.025, 0.025, 0.025);
            if (map.getMapValue(j,i) == 1)
            {
                Cell(green);
            }
            else
            {
                glScalef(0.5, 0.5, 0.5);
                Cell(red);
            }
            glPopMatrix();
        }
    }
    int cellsAlive = map.getCellsAlive();
    string cellsAliveString = to_string(cellsAlive);
    string s = "Cells alive: " + cellsAliveString;
    int n = s.length();
    char char_array[n + 1];
    strcpy(char_array, s.c_str());
    drawString(0.0, 10.0, 0.0, char_array, white);

    glFlush();
    glutSwapBuffers();
}

void mouse3D(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        leftMouseButtonDown = (state == GLUT_DOWN);
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
    }
    mouseXPos = x;
    mouseYPos = y;
    // cout << "x: " << x << " y: " << y << endl;
    glutPostRedisplay();
}
