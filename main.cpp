#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <math.h>
#include "./src/map.cpp"
// #include "./src/settings2D.cpp"
#include <cstdlib>
#include <unistd.h>
using namespace std;

bool pauseGame = true;
int window1;
int window2;
GameMap map;

void init()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-200, 200, -200, 200);
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

void display(void)
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

void mouse(int button, int state, int x, int y)
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

int main(int argc, char *argv[])
{
    // map.readMapFromFile("./src/gameMap/map.txt");
    // map.drawMap();

    // for (int i = 0; i < 10; i++){
    //     system("clear");
    //     map.updateMapState();
    //     map.drawMap();
    //     sleep(1);
    // }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(150, 30);
    window1 = glutCreateWindow("ventana 2D");
    init();
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMouseFunc(mouse);

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(150, 30);
    window2 = glutCreateWindow("ventana 3D");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(key);
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}
