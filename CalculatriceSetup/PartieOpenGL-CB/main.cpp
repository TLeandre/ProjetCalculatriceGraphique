/**************************
 * Includes
 *
 **************************/

#include "graph.h"

int bascule=0;

/**
* myKey
*
* Gestion des touches du clavier
*
* @parma c code ascci definissant une touche du clavier
*
*/
void myKey(int c)
{
  switch(c)
  {
    case 'a':
      bascule^=1; /* La bascule passe alternativement de 0 a 1 */
      break;
  }
}

/**
* myDraw
*
* Procédure
*
*/
void myDraw(void)
{
  /* trace une ligne blanche diagonale */
  setcolor(1.0F,1.0F,1.0F);
  line(-1.0,-1.0,1.0,1.0);

  if (bascule)
  {
    /* Trace un rectangle rouge a l'ecran si active
     * par appui de la touche 'a' */
    setcolor(1.0F,0.0F,0.0F);
    bar(-0.5F,-0.5F,0.5F,0.5F);
  }
  /* ecrit le message "bonjour" en jaune */
  setcolor(1.0F,1.0F,0.0F);
  outtextxy(0.0,0.0,"Bonjour");
}


/**
* main
*
* La fonction principale avec deux arguments permettant de récupérer les éléments en ligne de comment.
*
* Dans  cet  exemple  les  fonctions  (dites  callback)  myDraw  et  myKey  sont  installées  ici  par
* l'appel  InitGraph  en  tant  que fonctions  réagissantes  aux  évènements  de  "re-dessinage"  (pour  myDraw)
* et  aux  évènements  d'appui  sur  une  touche  du
* clavier (myKey).
µ
* @parma ac : nombre de parametres
* @parma av : tableau contenant les parametres
*
*/
int main(int ac,char *av[])
{
  InitGraph(ac,av,"Essai Glut",640,480,myDraw,myKey);
  return 0;
}


