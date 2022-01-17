/**************************
 * Includes
 *
 **************************/

#include "graph.h"
#include <math.h>
#include "glut.h"

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
      glutPostRedisplay();
      break;
  }
}

float fonction(float x){
    return sin(x)*10;
}

float echelon(float debut, float fin, float pas,float tab[]){
    float x = debut;
    int val=(fin-debut)/pas;
    for(int i = 0; i<val; i++){
        tab[i]= x;
        x+=pas;
    }
}

void DrawLine(void){
    line(0,100,0,-100);
    line(100,0,-100,0);

    float deb = 10;
    float fin = 500;
    float pas = 0.1;
    int val = (fin-deb)/pas;
    float tab[val];

    echelon(deb, fin, pas, tab);

    for( int i = 0; i < val; i++){
        printf("%f\n", tab[i]);
    }

    for (int i = 1; i<val; i++){
        line(tab[i-1],fonction(tab[i-1]),tab[i],fonction(tab[i]));
    }

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
  InitGraph(ac,av,"Calculatrice Graphique",960,1080,DrawLine,myKey);
  return 0;
}
