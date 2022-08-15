#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "./src/settings.cpp"

void Mensaje(){

printf(" =================================================================\n");
printf("\t\t == PROYECTO DEL JUEGO DE LA VIDA ==\n");
printf(" =================================================================\n\n ");

printf(" GRUPO 2: \n");
printf(" \tBalboa Palma Merly \n");
printf(" \tMirano Caro Mitchell\n");
printf(" \tVáquez Dávila Sebastian\n");

printf(" =================================================================\n");
printf("\t\t == REGLAS DEL JUEGO DE LA VIDA==\n");
printf(" =================================================================\n\n ");

printf(" [1]\t Si una celula esta viva y tiene dos o tres vecinas vivas, sobrevive\n");
printf(" [2]\t Si una celula esta muerta y tiene tres vecinas vivas, nace \n");
printf(" [3]\t Si una celula esta viva y tiene mas de tres vecinas vivas, muere\n");


printf(" =================================================================\n");
printf("\t\t == fUNCION DE LAS TECLAS Y MOUSE==\n");
printf(" =================================================================\n\n ");

printf(" [p]\t Pausar y empezar la escena del juego\n");
printf(" [Barra espaciadora]\t Pausa o Inicia el juego \n");
printf(" [Mouse]\t Mueve la escena del juego \n");

printf("\n\n");
}



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    Mensaje();
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
    // glClearColor(1, 1, 1, 1);
    // glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glutMainLoop();

    return 0;
}
