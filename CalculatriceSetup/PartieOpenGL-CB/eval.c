#include "jeton.h"
#include <stdio.h>

#include <math.h>

float Evaluateur( Node * arbre, float valeur,int* erreur){
  switch(arbre->jeton.lexem){
    case REEL:{
    return(arbre->jeton.valeur.reel);
    break;
    }
    case FUN:{
    float D = Evaluateur(arbre -> pjeton_suiv, valeur,erreur);
    if (arbre->jeton.valeur.fonction==SIN){
      return sin(D);
    }
    if (arbre->jeton.valeur.fonction==SQRT){
      if (D<0){
        *erreur=1;
        return D='\0';
      }
      if ( D >= 0){
        return sqrt(D);
      }
    }
    if (arbre->jeton.valeur.fonction==LOG){
      if (D>0){
        return log(D); }
      if (D<=0){
        *erreur=2;
        return D=ERREUR; }
    }
    if (arbre->jeton.valeur.fonction==COS){
    return cos(D);
    }
    if (arbre->jeton.valeur.fonction==TAN){
    if (cos(D)==0){
      *erreur=3;
      return ERREUR;
    }
    else {
      return tan(D);
    }
    }
    if (arbre->jeton.valeur.fonction==EXP){
    return exp(D); }
    if (arbre->jeton.valeur.fonction==ENTIER){
    return floor(D); }
    if (arbre->jeton.valeur.fonction==VAL_NEG){
    return -D; }
    break;
    }
    case FIN:{
      break;
    }
    case ERREUR:{
      break;
    }
    case VAR:{
      return valeur;
    }
    case OPER:{

    float A = Evaluateur(arbre -> pjeton_preced, valeur,erreur);
    float B = Evaluateur(arbre -> pjeton_suiv, valeur,erreur);
    if (arbre -> jeton.valeur.operateur == FOIS)
    {
        return A * B;
    }
    if (arbre -> jeton.valeur.operateur == PLUS)
    {
        return A + B;
    }
    if (arbre -> jeton.valeur.operateur == MOINS)
    {
      return A - B;
    }

    if (arbre -> jeton.valeur.operateur == DIV)
    {
      if (B != 0)
      {
        return A / B;
      }
      if (B == 0)
      {
        *erreur=4;
        return B = ERREUR;
      }
    }
    if (arbre -> jeton.valeur.operateur == PUIS)
    {
      return pow(A,B);
    }
    break;
    }
  }
}
