#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "./src/settings.cpp"


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(150, 100);
    window1 = glutCreateWindow("ventana 2D");
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-200, 200, -200, 200);
    glutIdleFunc(idle);
    glutDisplayFunc(display2D);
    glutKeyboardFunc(key);
    glutMouseFunc(mouse2D);

    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(950, 100);
    window2 = glutCreateWindow("ventana 3D");
    glutDisplayFunc(display3D);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    glutMouseFunc(mouse3D);
    glutMotionFunc(mouseMotion3D);

    glutMainLoop();

    return 0;
}
