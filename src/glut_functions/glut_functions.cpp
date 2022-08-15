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

void drawString(float x, float y, float z, char *string, float *color) {
  glColor3fv(color);
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