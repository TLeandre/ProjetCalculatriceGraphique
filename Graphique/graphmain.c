#include <math.h>
#include <stdio.h>
#include "functiongraph.h"

int quit = 0;
int input = 0;

void main(){

    printf("#-- Bienvenue dans notre calculatrice graphique --#\n");

    while (quit == 0){ 
        Menu();
        scanf("%d", &input);
        printf("%d\n",input);

        if(input == 1){
            //fonction qui récupère la fonction et fait le mélange
        }else if(input == 2){
            // fonction qui change les bornes à afficher
        }else if(input == 3){
            // fonction qui affiche le graphique de la fonction avec les bornes 
        }else if(input == 4){
            // fonction qui recherche un point en particuler sur la courbe?
        }else if(input == 5){
            quit = 1;
        }else{
            printf("Ce que vous avez saisi n'est pas valide, veuillez reessayer.\n");
        }
    }

    printf("Merci d'avoir utilisé notre calculatrice !");
    

}