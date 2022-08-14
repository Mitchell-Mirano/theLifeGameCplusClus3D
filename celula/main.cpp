///////// LIBRERIAS /////////////
#include <stdio.h>//esta libreria sirve para utilizar el printf
//(el printf esta dentro de la libreria)
#include <math.h> // sirve para utilizar funciones matematicas
//#include <windows.h> // sirve para utilizar la funcion Sleep
//Sleep(hace que se vea mas lento la ejecucion)
#include <gl/glut.h>// herramienta para opengl
#include<GL/glu.h> // herramienta para opengl que facilita el uso de texturas
//sirve para utilizar la funcion gluSphere
//#define M_PI 3.141592654 // define la constante M_PI

float black[] = {0,0,0}, white[]={1,1,1}, blue[] = {0,0,1}, sky[]={0,0.8,1}, rosa[]={0.737255,0.560784,0.560784};
float red[] = {1,0,0}, green[]={0,1,0}, yellow[]={1,1,0},violet[]={1,0,1}, firebrick[]={0.556863,0.137255,0.137255};
float cyan[]={0,1,1}, pink[]={1,0.5,0.5}, orange[]={1,0.5,0}, darkgreen[]={0.1,0.6,0.184314}, gray[]={0.37,0.34,0.34};
float ab[]={0,0};

void ejes(float k)
{
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(-k,0,0);
    glVertex3f(k,0,0);
    glColor3f(0,1,0);
    glVertex3f(0,-k,0);
    glVertex3f(0,k,0);
    glColor3f(0,0,1);
    glVertex3f(0,0,-k);
    glVertex3f(0,0,k);
    glEnd();
}

///////// variables boolenas ///////////
GLboolean Solido=false;
GLboolean Textura=false;
GLboolean Pausa = false;
//Una variable booleana es aquella que puede ser (V o F)///////////////////

////////// Definimos las constantes de luminosidad ////////////

GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };// Esta luz no proviene de una sola fuente sino de luces que estan larededor.
                                                     //para simular esto usamos constantes de iluminacion ambiental que siempre le dan al objeto algo de color.
GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };//Simula el impacto direccional que tiene un objeto sobre otro objeto (cuanto mas un objeto mire hacia la fuente de luz mas brillante se vuelve)
GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };// Simula el punto brillante de la luz que aparece en el objeto, estos reflejos especulares estan + inclinados al color de la luz que al color del objeto.
GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };//

GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat high_shininess[] = { 100.0f };
////////////////////////////////////////////////////////////////
///// TEXTURA//////////////
GLubyte* data;
GLUquadricObj *obj = gluNewQuadric();
GLUquadricObj *obj_reverse = gluNewQuadric();
GLint Nom[12];

//LoadBMP : carga une imagen de 24bmp
#define EXIT {fclose(fichier);return -1;}
#define CTOI(C) (*(int*)&C)

int LoadBMP(char *File)// carga une imagen en formato bmp
{
unsigned char *Data;
FILE *fichier;
unsigned char Header[0x36];
GLuint DataPos,DataSize;
GLint Components;
GLsizei Width,Height;
GLenum Format,Type;
GLuint Name[1];

fichier = fopen(File,"rb");if (!fichier) return -1;
if (fread(Header,1,0x36,fichier)!=0x36) EXIT;
if (Header[0]!='B' || Header[1]!='M') EXIT;
if (CTOI(Header[0x1E])!=0) EXIT;
if (CTOI(Header[0x1C])!=24) EXIT;

DataPos = CTOI(Header[0x0A]);
DataSize = CTOI(Header[0x22]);

Width = CTOI(Header[0x12]);
Height = CTOI(Header[0x16]);
Type = GL_UNSIGNED_BYTE;
Format = GL_RGB;
Components = 3;

if (DataSize==0) DataSize=Width*Height*Components;
if (DataPos==0) DataPos=0x36;

fseek(fichier,DataPos,0);
Data = new unsigned char[DataSize];
if (!Data) EXIT;

if (fread(Data,1,DataSize,fichier)!=DataSize)
{
delete Data;
fclose(fichier);
return -1;
}

fclose(fichier);

unsigned char t;
for (int x=0;x<Width*Height;x++)
{
t=Data[x*3];
Data[x*3]=Data[x*3+2];
Data[x*3+2]=t;
}

glGenTextures(1, Name);
glBindTexture(GL_TEXTURE_2D, Name[0]);


glTexImage2D(GL_TEXTURE_2D,0,Components,Width,Height,0,GL_RGB,GL_UNSIGNED_BYTE,Data);

return Name[0];
}
////////////////////////////////////////////////////////////////////////////////
GLint RH=100;
GLint RV=100;
GLint Virus =1;

void esfera(float r){
    GLUquadricObj *quadric;
    quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_SMOOTH);
    //gluQuadricNormals(quadric, GLU_SMOOTH);
    gluSphere(quadric,r,RH,RV);
}
void cono(float radio,float altura){
     glutSolidCone(radio,altura,RH,RV);
}

virus(){
glPushMatrix();
    esfera(10);
    glTranslatef(0,0,7);
    cono(4,10);
glPopMatrix();

 glPushMatrix();
    glRotated(180,1,0,0);
    glTranslatef(0,0,7);
    cono(4,10);
glPopMatrix();

glPushMatrix();
    glRotated(90,0,1,0);
    glTranslatef(0,0,7);
    cono(4,10);
glPopMatrix();

glPushMatrix();
    glRotated(-90,0,1,0);
    glTranslatef(0,0,7);
    cono(4,10);
glPopMatrix();
//espina azul
glPushMatrix();
    glRotated(-90,1,0,0);
    glTranslatef(0,0,7);
    cono(4,10);
glPopMatrix();

glPushMatrix();
    glRotated(90,1,0,0);
    glTranslatef(0,0,7);
    cono(4,10);
glPopMatrix();
}
void display(void) {
    glBindTexture(GL_TEXTURE_2D, Nom[9]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
glLightfv(GL_LIGHT0, GL_POSITION, light_position);

/* material*/

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    ejes(500);

 for (int n=0;n<Virus;n++){

if (Textura == false){// si la textura es verdadera no se le asigna colores alos planetas
    //glColor3f(0.73, 0.73, 0.73);
    glColor3fv(green);
}

glPushMatrix();
if (Textura==true){
glBindTexture(GL_TEXTURE_2D, Nom[1]);// hace mallado en la imagen
//gluQuadricTexture(obj, GL_TRUE );// hace la cuadratura en el objeto
//gluQuadricDrawStyle(obj, GLU_FILL);//dibuja la cuadratura en el objeto
//gluSphere(obj,10,RH/2,RV/2); //crea la esfera utilizando la cudratura texturizada
 virus();
 glColor3fv(black);
}

else{//cuando no hay texturas grafica en solido o en malla
       virus();
glColor3fv(white);
}

glPopMatrix();
}

    glFlush ();
    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(-50,50,-50,50,0.5,1000);
   //gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 60.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
      gluLookAt (30.0, 30.0, 30.0, 0, 0, 0.0, 0, 0, 1);
      //gluLookAt(0,0,30, 0,0,0, 0,1,0);//VISTA FRONTAL
    //gluLookAt(30,0,0, 0,0,0, 0,1,0);//VISTA LATERAL 1
    //gluLookAt(0,30,0, 0,0,0, 1,0,0);//VISTA SUPERIOR VERT-ROJO  HOR-VERDE
    //gluLookAt(0,30,0, 0,0,0, 0,0,1);//VISTA FRONTAL ZX
    //gluLookAt(30,0,0, 0,0,0, 0,0,1);//VISTA LATERAL VERT-VERDE HORI-AZUL

}

void Inicializacion(void)
{
glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );/* modo en el q va a dibujarse*/
glutInitWindowSize (800, 600); /* tama�o de ventana*/
glutInitWindowPosition (100, 100);/*posicion de la ventana */
glutCreateWindow ("VIRUS");/* crea la ventana de nombre sistema solar*/

GLfloat position1 [] = { 0, 0.0F, 0.0F, 1.0F };/* declaramos el vector position*/
/* activa efectos de luminosidad y sombreado */
glLightfv(GL_LIGHT0, GL_POSITION, position1);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glShadeModel (GL_SMOOTH);
/* propiedades de luminosidad y sombreado */
glEnable(GL_DEPTH_TEST);
glEnable(GL_COLOR_MATERIAL);
glEnable(GL_TEXTURE_2D);
glMatrixMode (GL_MODELVIEW);
/* se carga las imagenes que van a ser de textura */

//Nom[1] = LoadBMP("C:\Users\sony\Desktop\codigo Virus\virus.bmp");
Nom[1] = LoadBMP("virus.bmp");
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

//Nom[9] = LoadBMP("universo.bmp");
//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

glDepthFunc(GL_LESS);
glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
void keyboard(unsigned char key, int x, int y)
{
switch (key) {

case 't':case 'T':{//activa la textura
if (Textura==true)
    Textura = false;
else Textura = true;
break;
}

}
glMatrixMode(GL_MODELVIEW);
//reshape(w,h);// reactualiza la ventana (traslaciones y acercamientos)
}
void Mensaje(){

printf(" =================================================================\n");
printf(" == Proyecto JUEGO DE LA VIDA ==\n");
printf(" =================================================================\n\n ");

printf(" INTEGRANTES : \n");
printf(" \tGRUPO 2\n");

printf(" TECLA \t FUNCION\n\n");
printf(" [t]\t Activar o desactivar Textura \n");
printf("\n\n");


}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    Mensaje();//llama a la funcion mensaje
    Inicializacion(); //inicializamos la ecena
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // controlar el teclado
    glClearColor(1,1,1,1);
    //glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glutMainLoop();
    return EXIT_SUCCESS;
}
