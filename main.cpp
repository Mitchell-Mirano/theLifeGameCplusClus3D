#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <math.h>
#include "./src/map.cpp"
#include "./src/cells/cell.cpp"
#include "./src/colors/colors.cpp"
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
    glOrtho(-5.0, 5.0, -5.0, 5.0, 1.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void Linea(float *X0, float *X1, float *C, float A = 1, int f = 1, int P = 0)
{
    glColor3fv(C);
    glLineWidth(A);
    glEnable(GL_LINE_STIPPLE);
    switch (P)
    {
    case 1:
        glLineStipple(f, 0x0101);
        break;
    case 2:
        glLineStipple(f, 0xAAAA);
        break;
    case 3:
        glLineStipple(f, 0x00FF);
        break;
    case 4:
        glLineStipple(f, 0x0c0F);
        break;
    case 5:
        glLineStipple(f, 0x1C47);
        break;
    default:
        glLineStipple(f, 0xFFFF);
        break;
    }
    glBegin(GL_LINES);
    glVertex3fv(X0);
    glVertex3fv(X1);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glLineWidth(1);
}

void Ejes(int c)
{
    float P[] = {-20.0, 0.0, 0.0}, P1[] = {20.0, 0.0, 0.0};
    float P2[] = {0.0, -20.0, 0.0}, P3[] = {0.0, 20.0, 0.0};
    float P4[] = {0.0, 0.0, -20.0}, P5[] = {0.0, 0.0, 20.0};
    float C1[] = {1, 0, 0}, C2[] = {0, 0, 1}, C3[] = {0, 1, 0};
    switch (c)
    {
    case 0:
    {
        Linea(P, P1, C1, 2, 2, 3);
        Linea(P2, P3, C2, 2, 2, 3);
        Linea(P4, P5, C3, 2, 2, 3);
        break;
    }
    default:
    {
        Linea(P, P1, C1, c);
        Linea(P2, P3, C2, c);
        Linea(P4, P5, C3, c);
    }
    }
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-200, 200, -200, 200);
}

void drawString(float x, float y, float z, char *string) {
  glRasterPos3f(x, y, z);

  for (char* c = string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
  }
}

void drawSquare(float x, float y, float lado)
{
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + lado, y);
    glVertex2f(x + lado, y - lado);
    glVertex2f(x, y - lado);
    glEnd();
}

void drawLines(float x, float y, float lado)
{
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + lado, y);
    glVertex2f(x + lado, y - lado);
    glVertex2f(x, y - lado);
    glEnd();
}

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

void display3D(void)
{
    glClearColor(0, 0, 0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    double cameraX = cos(cameraAngle) * cameraZoom;
    double cameraZ = sin(cameraAngle) * cameraZoom;
    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    // Ejes(3);

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    Cell(red);
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
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

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    // glutInitWindowSize(600, 600);
    // glutInitWindowPosition(150, 30);
    // window1 = glutCreateWindow("ventana 2D");
    // init();
    // glutIdleFunc(idle);
    // glutDisplayFunc(display2D);
    // glutKeyboardFunc(key);
    // glutMouseFunc(mouse2D);

    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(150, 30);
    window2 = glutCreateWindow("ventana 3D");
    // init();
    glutDisplayFunc(display3D);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    glutMouseFunc(mouse3D);
    glutMotionFunc(mouseMotion3D);

    glutMainLoop();

    return 0;
}
