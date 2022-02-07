/* verification du code erreur
setcolor(1.0F,0.0F,0.12F);
outtextxy(0, 0, "ERREUR");
*/



#include "graph.h"
#include <math.h>
#include "glut.h"

// include pour la function évaluation
#include <stdio.h>
#include "jeton.h"
#include <stdlib.h>
#include "eval.h"

// création de l'arbre
struct Node * creer_arbre(typejeton Jeton){
      struct Node * node = (struct Node *) malloc(sizeof(struct Node));
      node->jeton=Jeton;
      node->pjeton_preced=NULL;
      node->pjeton_suiv=NULL;
    return node;
}

typejeton jeton_x={VAR};
typejeton jeton_7={REEL,2};
typejeton jeton_plus={OPER,0};
typejeton jeton_fin1={FIN};
typejeton jeton_cos={FUN,0};

// initation des variables
float deb = -10.0;
float fin = 10.0;
int dist = 10;

int erreur = 0;
int quitCalc = 0;
int State = 0;
int inputCalc = 0;
float ant = 0;
int findval = 0;

char gridnumber [20] = {0};
char anttext [20] = {0};
char imtext [20] = {0};
char fonctiontexte[100] = "cos x*2";
int d = 0;
float division[6] = {1,2,5,10,20,50};

// écrit le menu dans la console
void MenuCal(){
    Clean();
    printf("---------------------------\n");
    printf("1) Entrer la fonction \n");
    printf("2) Changer les bornes \n");
    printf("3) Recherche d'un point particulier \n");
    printf("4) Quitter la calculatrice \n");
    printf("---------------------------\n");
    printf("p for zoom \n");
    printf("m for dezoom \n");
    printf("l for left \n");
    printf("r for right \n");
    printf("---------------------------\n");
    printf("Que souhaitez-vous faire ? Entrez le numero ou une lettre: \n");
}

// fonction clean pour rendre la console plus joliue lors de son utilisation
void Clean(){
    for(int i = 0; i < 30; i++){
        printf(".\n");
    }
}

void changediv(){

    dist = abs(fin - deb)/2;

    if (dist <= 15){
        d=0;
    }else if (dist <= 35){
        d=1;
    }else if (dist <= 60){
        d=2;
    }else if (dist <= 100){
        d=3;
    }else if (dist <= 200){
        d=4;
    }else if (dist <= 360){
        d=5;
    }
}

// réaliser l'echelon d'un tableau pour la réalisation du graphique
float echelon(float debut, float fin, float pas,float tab[]){
    float x = debut;
    int val=(fin-debut)/pas;
    for(int i = 0; i<val; i++){
        tab[i]= x;
        x+=pas;
    }
}

int returnErreur(){
    printf("La nvx erreur%d", erreur);
    return erreur;
}

// utilisation de q lorsque le graphique est cliqué
void myKey(int c)
{
  switch(c)
  {
    case 'q':
        quitCalc^=1; /* La bascule passe alternativement de 0 a 1 */
        break;
  }
}

// va dessiner la grille en fonction des valeurs des bornes
void DrawGrid(float a, float b){

    dist = abs(b - a)/2;

    /*
    section de la grille
    */
    setcolor(0.2F,0.2F,0.2F);

    changediv();

    for ( int i = a; i <= b; i+= division[d]){
        setcolor(0.2F,0.2F,0.2F);
        sprintf(gridnumber, "%d", i);
        line(i, -dist, i, dist);
        setcolor(0.5F,0.0F,1.0F);
        outtextxy(i, 0, gridnumber);
    }

    //grid horizontal
    for(int y = 0; y <= dist; y += division[d]){
        setcolor(0.2F,0.2F,0.2F);
        sprintf(gridnumber, "%d", y);
        line(a, y, b, y);
        if(y != 0){
            setcolor(0.5F,0.0F,1.0F);
            outtextxy(a, y, gridnumber);
        }
    }
    for(int y = 0; y >= -dist; y -= division[d]){
        setcolor(0.2F,0.2F,0.2F);
        sprintf(gridnumber, "%d", y);
        line(a, y, b, y);
        if(y != 0){
            setcolor(0.5F,0.0F,1.0F);
            outtextxy(a, y, gridnumber);
        }
    }

     /*
    section du repère
    */
    setcolor(1.0F,1.0F,1.0F);
    line(b,0,a,0);
    line(0,-dist,0,dist);
}

// fonction principal qui va tourner en boucle une fois le programme lancé
void DrawLine(){
    // import de l'arbre pour les tests
    jeton_cos.valeur.fonction=COS;
    jeton_plus.valeur.operateur=FOIS;

    struct  Node * test1 = creer_arbre(jeton_cos);
    struct  Node * test2 = creer_arbre(jeton_plus);
    struct  Node * test3 = creer_arbre(jeton_x);
    struct  Node * test4 = creer_arbre(jeton_7);
    struct  Node * test5 = creer_arbre(jeton_fin1);
    struct  Node * test6 = creer_arbre(jeton_fin1);
    struct  Node * test7 = creer_arbre(jeton_fin1);

    test1->pjeton_suiv = test2;
    test1->pjeton_preced = test6;
    test2->pjeton_suiv = test3;
    test2->pjeton_preced = test4;

    // boucle while qui réalise le menu utilisateur
    while(State == 1){
        MenuCal();
        scanf("%c", &inputCalc);


        if(inputCalc == '1'){// changer de fonction
            //fonction qui récupère la fonction et fait le mélange
            scanf("%s", fonctiontexte);
            printf("fc %s",fonctiontexte);
            State = 0;
        }else if(inputCalc == '2'){// changer les bornes d'affichages
            int GB = 0;

            while (GB != 1){
                printf("entrer la valeur la plus petite : ");
                scanf("%f", &deb);
                printf("entrer la valeur la plus grande : ");
                scanf("%f", &fin);


                if(deb < fin){
                    GB = 1;
                }else{
                    printf("Les valeurs des bornes ne sont pas correct, veuillez réessayer\n");
                }
            }
            State = 0;
        }else if(inputCalc == '3'){
            int GV = 0;

            while (GV != 1){
                printf("entrer la valeur recherchee : ");
                scanf("%f", &ant);
                if (ant >= deb && ant <= fin){
                    findval = 1;
                    GV = 1;
                }else{
                    printf("La valeur recherche n'est pas compris entre les bornes, veuillez réessayer\n");
                }
            }
            State = 0;
        }else if(inputCalc == '4'){// quitte la calculatrice
            printf("Merci d'avoir utilisé notre calculatrice\n");
            End();
        }else if(inputCalc == 'p'){
            deb+=division[d];
            fin-=division[d];
            State=0;
        }else if(inputCalc == 'm'){
            deb-=division[d];
            fin+=division[d];
            State=0;
        }else if(inputCalc == 'l'){
            deb-=division[d];
            fin-=division[d];
            State=0;
        }else if(inputCalc == 'r'){
            deb+=division[d];
            fin+=division[d];
            State=0;
        }else{
            printf("Ce que vous avez saisi n'est pas valide, veuillez reessayer.\n");
        }
    }

    // boucle while qui afficher le graphique lors d'un changement de bornes ou de fonction
    while(State == 0){

        // affiche de la fonction entré par l'utilisateur
        setcolor(1.0F,0.0F,0.0F);
        char ft[] = "fonction : ";
        strcat(ft, fonctiontexte);
        outtextxy((fin+deb)/2 , (dist)-division[d], ft);

        resizeScale(deb, fin);

        DrawGrid(deb, fin);

        // realisation du tableau de valeur de la fonction
        float pas = 0.01;
        int val = (fin-deb)/pas;
        float tab[val];

        echelon(deb, fin, pas, tab);

        // affiche ligne par ligne de la fonction
        for(int i = 1; i < val; i++){
            line(tab[i-1], Evaluateur(test1,tab[i-1],&erreur),tab[i], Evaluateur(test1,tab[i],&erreur));
        }

        if (findval == 1){
            // calcul l'image
            float im = Evaluateur(test1,ant,&erreur);

            // crée les deux lignes
            setcolor(1.0F,0.0F,0.0F);
            line(deb, im, fin, im);
            line(ant, -dist, ant, dist);

            // conversiont en text de l'antecedent et de l'image
            sprintf(anttext, "%f", ant );
            char at[] = "antecedent : ";

            sprintf(imtext, "%f", im );
            char it[] = ", image : ";

            // combinaison de tous les textes
            strcat(at, anttext);
            strcat(at, it);
            if(erreur == 0){
                strcat(at, imtext);
            }else{
                strcat(at, "Erreur");
            }


            // affichage du texte sur le graphique
            outtextxy(deb+division[d], division[d]-dist  , at);

            findval = 0;
        }


        State = 1;
        printf("\n\n\nMerci de reCliquer sur le graphique pour continuer a utiliser la calculatrice");

    }

}





