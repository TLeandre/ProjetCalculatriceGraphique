#include <windows.h>
#include "glut.h"
#include "graph.h"
#include <stdio.h>

/**
* @file Graph.cpp
*
* @brief présente les quelques fonctionnalités nécessaires dans le cadre de ce projet
* Il contient la définition des méthodes utilisées
*
*/


//donne la moyenne des x dans le tableau
float moyenne(tableau_evaluateur tab[]){
	int x=0;
	int i;
	for(i=0;i<=PAS;i++){
		x+=tab[i].x;
	}
	x=x/(PAS+1);
	return x;
}


static int WindowNumber;
static int Width,Height;
static void (*AppliDraw)(void);
static void (*AppliKey)(int);



/**
* GlutReshape
*
* Cette procédure permet de gerer la taille de la fenetre quand (redimensionnée)
*
* @parma w largeur de la fenetre gl
* @parma h hauteur de la fenetre gl
*/

static void GlutReshape(const int w,const int h)
{
  Width=w;
  Height=h;
  glViewport(0,0,Width,Height);
}

static void GlutIdle(void)
{
//  glutPostRedisplay();
}

static void GlutKey(const unsigned char c,const int x,const int y)
{
  switch(c)
  {
    default:
      if (AppliKey) (*AppliKey)(c);
      break;
  }
  glutPostRedisplay();
}


static void Begin2DDisplay(void)
{
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(-1,1,-1.0,1.0,0.5,1.5);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(0.0F,0.0F,-1.0F);
}

static void End2DDisplay(void)
{
  /* Fin du trace, retour au parametres normaux */
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

static void InitDisplay(void)
{
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glClearColor(0.0F,0.0F,0.0F,0.0F);
}

static void GlutDraw(void)
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  Begin2DDisplay();
  if (AppliDraw) (*AppliDraw)();
  End2DDisplay();
  glutSwapBuffers();
}


/**
* InitGraph
*
* Procedure d'initialisation de la fenetre et de l'environement OpenGL
* L'initialisation de GLUT se trouve dans la procedure
* principale, elle necessite l'emploie des argument de
* la ligne de commande
*
* @parma ac
* @parma av[]
* @parma WinName definit le nom (titre) de la fentre d'affichage
* @parma w definit la largeur de la fenetre
* @parma h definit la hauteur de la fenetre
* @parma Draw définit une méthode de traçage
* @parma Key définit une méthode permettant la détection des touche du clavier
* @parma c entier designant le code ascii d'une touche
*
*/
void InitGraph(int ac,char *av[],
               const char *WinName,const int w,const int h,void (*Draw)(void),
               void (*Key)(int))
{
  glutInit(&ac,av);
  Width=w;
  Height=h;
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(Width,Height);
  WindowNumber=glutCreateWindow(WinName);
  glutReshapeFunc(GlutReshape); /* fonction appelee qd fenetre redimensionnee */
  glutIdleFunc(GlutIdle); /* fonction appelee en boucle */
  AppliKey=Key;
  glutKeyboardFunc(GlutKey);
  AppliDraw=Draw;
  glutDisplayFunc(GlutDraw);
  InitDisplay();
  glutMainLoop();
}


/**
* setcolor
*
* Cette procédure permet de definire une couleur par ces trois composantes
*
* @parma r composante du plan rouge
* @parma v composante du plan vert
* @parma b composante du plan bleu
*
*/
void setcolor(const float r,const float v,const float b)
{
  glColor3f(r,v,b);
}

/**
* line
*
* Cette procédure permet de tracher une ligne entre deux points (x0, y0) et (x1,y1)
*
* @parma x0 abscisse 1er point
* @parma y0 ordonnée 1er point
* @parma x0 abscisse 2eme point
* @parma y0 ordonnée 2eme point
*
*/
void line(const float x0,const float y0,const float x1,const float y1)
{
  glBegin(GL_LINES);
    glVertex2f(x0,y0);
    glVertex2f(x1,y1);
  glEnd();
}

/**
* beginlines
*
* Cette procédure permet
*
* @parma x0
* @parma y0
*
*/
void beginlines(const float x0,const float y0)
{
  glBegin(GL_LINE_STRIP);
  glVertex2f(x0,y0);
}

void lineto(const float x,const float y)
{
  glVertex2f(x,y);
}

void finishlines(void)
{
  glEnd();
}

void bar(const float x0,const float y0,const float x1,const float y1)
{
  glBegin(GL_QUADS);
    glVertex2f(x0,y0);
    glVertex2f(x0,y1);
    glVertex2f(x1,y1);
    glVertex2f(x1,y0);
  glEnd();
}


/**
* outtextxy
*
* Cette procédure permet d'ecrit une chaine de charactère s dans une zone de texte définie par les coordonnées x et y
*
* @parma x abscisse du point (coint gauche superieur) de la zone de texte
* @parma y ordonnée du point (coint gauche superieur) de la zone de texte
* @parma s tableau de charctères
*
*/

void outtextxy(const float x,const float y,char *str)
{
  char *s=str;

  glRasterPos2f(x,y);
  while(*s!='\0')
  {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*s++);
  }
}

