#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <GL/glut.h>

GLint RH = 100;
GLint RV = 100;
GLint Virus = 1;


void ejes(float k)
{
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(-k, 0, 0);
    glVertex3f(k, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, -k, 0);
    glVertex3f(0, k, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -k);
    glVertex3f(0, 0, k);
    glEnd();
}


void esfera(float r)
{
    GLUquadricObj *quadric;
    quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_SMOOTH);
    // gluQuadricNormals(quadric, GLU_SMOOTH);
    gluSphere(quadric, r, RH, RV);
}

void cono(float radio, float altura)
{
    glutSolidCone(radio, altura, RH, RV);
}
