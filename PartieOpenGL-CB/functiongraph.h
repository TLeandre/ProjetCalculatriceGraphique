#include <math.h>
#include <stdio.h>

void Menu(){

    Clean();
    printf("Menu \n");
    printf("1) entrer la fonction \n");
    printf("2) changer les bornes \n");
    printf("3) afficher le graphique \n");
    printf("4) trouver un point en particulier\n");
    printf("5) quitter la calculatrice \n");
    printf("que souhaitez-vous faire ? Entrez le numero : \n");
}

void Clean(){
    for(int i = 0; i < 20; i++){
        printf(".\n");
    }
}

void Draw(){
    printf("vous avez afficher votre graphique");
}

float fonction(float x){
    return sin(x);
}

float echelon(float debut, float fin, float pas,float tab[]){
    float x = debut;
    int val=(fin-debut)/pas;
    for(int i = 0; i<val; i++){
        tab[i]= x;
        x+=pas;
    }
}
