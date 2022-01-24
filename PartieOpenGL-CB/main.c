/**************************
 * Includes
 *
 **************************/

#include "graph.h"
#include <math.h>
#include "glut.h"
#include "functiongraph.h"

int bascule=0;
int quit = 0;
int input = 0;


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
      scanf("%d", &input);
      printf("%d\n",input);
      glutPostRedisplay();
      break;
  }
}

void DrawGrid(void){
    int intervalle = 5;
    setcolor(0.1F,0.1F,0.1F);

    for ( int i = -100; i < 105; i+= intervalle){
        line(i, -100, i, 100);
        line(-100, i, 100, i);
    }



}

void DrawLine(void){
    DrawGrid();

    setcolor(1.0F,1.0F,1.0F);
    line(0,100,0,-100);
    line(100,0,-100,0);

    float deb = -50;
    float fin = 50;
    float pas = 0.1;
    int val = (fin-deb)/pas;
    float tab[val];

    echelon(deb, fin, pas, tab);

    for(int i = 1; i < val; i++){
        line(tab[i-1], fonction(tab[i-1]),tab[i], fonction(tab[i]));
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
void main(int ac,char *av[])
{
  printf("#-- Bienvenue dans notre calculatrice graphique --#\n");

    while (quit == 0){
        Menu();
        scanf("%d", &input);
        printf("%d\n",input);

        if(input == 1){
            //fonction qui récupère la fonction et fait le mélange
        }else if(input == 2){
            /*fonction qui rescale le graphe*/
            resizeScale(200.0, 200.0);
        }else if(input == 3){
            InitGraph(ac,av,"Calculatrice Graphique",960,1080,DrawLine,myKey);
        }else if(input == 4){
            // fonction qui recherche un point en particuler sur la courbe?
        }else if(input == 5){
            quit = 1;
        }else{
            printf("Ce que vous avez saisi n'est pas valide, veuillez reessayer.\n");
        }
        input  = 0 ;
    }

    printf("Merci d'avoir utilisé notre calculatrice !");
}
