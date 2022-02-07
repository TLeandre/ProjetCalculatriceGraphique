
float Evaluateur( Node * arbre, float valeur,int* erreur){ // Definition de la fonction
  switch(arbre->jeton.lexem){
    case REEL:{ // Cas reel
    return(arbre->jeton.valeur.reel);
    break;
    }
    case PAR_OUV:{
      break;
    }
    case PAR_FERM:{
      break;
    }
    case FUN:{ 
          printf("TEST FUN");
          printf("%d",arbre->jeton.valeur.fonction);

   // Cas des fonctions
    float D = Evaluateur(arbre -> pjeton_preced, valeur,erreur);
    if (arbre->jeton.valeur.fonction==0){ // Fonction sin
    printf("TEST SIN");

      return sin(D);
    }
    if (arbre->jeton.valeur.fonction==SQRT){ // Fonction racine carré
      if (D<0){
        *erreur=1; // Erreur si racine est négative
        return D='\0';
      }
      if ( D >= 0){
        return sqrt(D);
      }
    }
    if (arbre->jeton.valeur.fonction==LOG){ // Fonction log
      if (D>0){
        return log(D); }
      if (D<=0){
        *erreur=2;
        return D=ERREUR; } // Erreur si log est négatif
    }
    if (arbre->jeton.valeur.fonction==COS){ // Fonction cos
    return cos(D);
    }
    if (arbre->jeton.valeur.fonction==TAN){ // Fonction tan
    if (cos(D)==0){
      *erreur=3;
      return ERREUR; // erreur sir cos =0
    }
    else {
      return tan(D);
    }
    }
    if (arbre->jeton.valeur.fonction==EXP){ // fonciton exponentielle
    return exp(D); }
    if (arbre->jeton.valeur.fonction==ENTIER){ // Partie entière
    return floor(D); }
    if (arbre->jeton.valeur.fonction==VAL_NEG){ // valeure négative
    return -D; }
    break;
    }
    case FIN:{
      break;
    }

    case VAR:{
      return valeur;
    }
    case OPER:{ // Cas des opérateurs

    float A = Evaluateur(arbre -> pjeton_preced, valeur,erreur);
    float B = Evaluateur(arbre -> pjeton_suiv, valeur,erreur);
    if (arbre -> jeton.valeur.operateur == FOIS) // Cas multiplication
    {
        return A * B;
    }
    if (arbre -> jeton.valeur.operateur == PLUS) // Cas addition
    {
              printf("\nTEST PLUS");

        return A + B;
    }
    if (arbre -> jeton.valeur.operateur == MOINS) // cas soustraction
    {
      return A - B;
    }

    if (arbre -> jeton.valeur.operateur == DIV) // Cas divison
    {
      if (B != 0)
      {
        return A / B;
      }
      if (B == 0)
      {
        *erreur=4;  // Erreur si division par 0
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
