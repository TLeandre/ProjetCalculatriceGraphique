#include "analyse_syntaxe.h"


Node *test1;


void ChangeArbre() {
    char entree[255];
       int erreur=0;
      
    scanf("%s", entree);
   // printf("%s", entree);
    typejeton output[MAX_FORMULE];
    printf("=================================\n\n\n");
    analyseLex(entree,output,&erreur);
    printf("=================================\n\n\n");
    
    printf(">>>>%s<<<\n\n",entree);
    
    
    test1 = syntax(output);
    //syntax(output);
}
float ResultArbre(int x){    
  float result =  Evaluateur(test1,x,&erreur);


  if (erreur!=0){
    printf("Code erreur  : %ls", erreur);
  }
  else {
    printf("\nLe resultat de l'arbe est : %f\n", result);
  }
    return result;
}