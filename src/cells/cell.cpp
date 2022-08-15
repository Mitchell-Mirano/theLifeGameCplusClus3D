#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "../glut_functions/glut_functions.cpp"



GLfloat light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};  // Esta luz no proviene de una sola fuente sino de luces que estan larededor.
                                                     // para simular esto usamos constantes de iluminacion ambiental que siempre le dan al objeto algo de color.
GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};  // Simula el impacto direccional que tiene un objeto sobre otro objeto (cuanto mas un objeto mire hacia la fuente de luz mas brillante se vuelve)
GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Simula el punto brillante de la luz que aparece en el objeto, estos reflejos especulares estan + inclinados al color de la luz que al color del objeto.
GLfloat light_position[] = {2.0f, 5.0f, 5.0f, 0.0f}; //

GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat high_shininess[] = {100.0f};


void Cell(float* color)
{
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    /* material*/

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


    glColor3fv(color);
    glPushMatrix();
    esfera(10);
    glTranslatef(0, 0, 7);
    cono(4, 10);
    glPopMatrix();

    glPushMatrix();
    glRotated(180, 1, 0, 0);
    glTranslatef(0, 0, 7);
    cono(4, 10);
    glPopMatrix();

    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslatef(0, 0, 7);
    cono(4, 10);
    glPopMatrix();

    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    glTranslatef(0, 0, 7);
    cono(4, 10);
    glPopMatrix();
    // espina azul
    glPushMatrix();
    glRotated(-90, 1, 0, 0);
    glTranslatef(0, 0, 7);
    cono(4, 10);
    glPopMatrix();

    glPushMatrix();
    glRotated(90, 1, 0, 0);
    glTranslatef(0, 0, 7);
    cono(4, 10);
    glPopMatrix();
}

