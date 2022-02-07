/*

===TYPE D'ERREURS===

*5  = opérateur inconnu
*6  = fonction non reconnue
*7  = manque parenthese dans le nombre négatif
*8  = trop de point 
*9  = manque de parenthese
*10 = nombre ou parenthèse mal placé pres d'une variable 
*11 = opérateur mal placé ou 2 ou plus opérateurs de suite
*12 = probleme début
*13 = opérateur directement apres une fonction
*14 = caractère non reconnu
*15 = fonction mal placée
*16 = nombre directement après une fonction
*17 = mauvaise fin
*18 = parenthèse ouv mal placée 
*19 = parenthèse ferm mal placée


*/
// FONCTION DE DETECTION

int *erreur;
int est_chiffre(char c);
int est_lettre(char c);
int est_operateur(char c);
int est_var(char c);
typejeton assign_operateur (char c,int* erreur);
typejeton assign_fonction (char str[],int* erreur);

int est_chiffre(char c)
{
    int a=0;
    if((c>='0')&& (c<='9'))
    {
        a=1;
    }
    return a;
}
int est_lettre(char c)
{
    int a=0;
    if((c>='a'&& c<='z')||(c>='A'&& c<='Z'))
    {
        a=1;
    }
    return a;
}
int est_operateur(char c)
{
    int a=0;
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='^')
    {
        a=1;
    }
    return a;
}
int est_var(char c)
{
    int a=0;
    if (c=='x' || c=='X')
    {
      a=1;
    }
    return a;
}
// assignation des opérateurs à leur jeton (lexem et valeur)
typejeton assign_operateur(char c,int *erreur)
{
    typejeton t;

    switch(c)
    {
    case '+':
        t.lexem=OPER;
        t.valeur.operateur=PLUS;
        break;

    case '-':

        t.lexem=OPER;
        t.valeur.operateur=MOINS;
        break;

    case '*':

        t.lexem=OPER;
        t.valeur.operateur=FOIS;
        break;

    case '/':

        t.lexem=OPER;
        t.valeur.operateur=DIV;
        break;
        
    case '^' :

        t.lexem=OPER;
        t.valeur.operateur=PUIS;
        break;
    default:
        *erreur=5;
    }
    return t;
}
// assignation des "lettre" en fonctions (lexem et valeur) 
typejeton assign_fonction(char str[],int *erreur)
{
    typejeton t;

    if (strcmp(str,"SIN")==0 || strcmp(str,"sin")==0 )
    {
        t.lexem=FUN;
        t.valeur.fonction=SIN;
    }
    else if(strcmp(str,"COS")==0 || strcmp(str,"cos")==0 )
    {
        t.lexem=FUN;
        t.valeur.fonction=COS;
    }
    else if(strcmp(str,"TAN")==0 || strcmp(str,"tan")==0 )
    {
        t.lexem=FUN;
        t.valeur.fonction=TAN;
    }
    else if(strcmp(str,"EXP")==0 || strcmp(str,"exp")==0 )
    {
        t.lexem=FUN;
        t.valeur.fonction=EXP;
    }
    
    else if(strcmp(str,"LN")==0 || strcmp(str,"ln")==0 )
    {
        t.lexem=FUN;
        t.valeur.fonction=LOG;
    }
    
    else if(strcmp(str,"SQRT")==0 || strcmp(str,"sqrt")==0 )
    {
        t.lexem=FUN;
        t.valeur.fonction=SQRT;
    }
    else if(strcmp(str,"VAL_NEG")==0 || strcmp(str,"val_neg")==0 )
    {
        t.lexem=FUN;
        t.valeur.fonction=VAL_NEG;
    }
    else if(strcmp(str,"ENTIER")==0 || strcmp(str,"entier")==0 )
    {
        t.lexem=FUN;
        t.valeur.fonction=ENTIER;
    }
    else
    {
        t.lexem=ERREUR;
        *erreur=6;
    }

    return t;
}
///************************************************************************************
void analyseLex(char input[],typejeton output[MAX_FORMULE],int *erreur)
{
    int ic=0;
    int it=0;
    int j=0;
    int po=0;
    int pf=0;
    //vérifie le début de input 
    if (est_operateur(input[ic])|| input[ic]==')') 
    {
        printf("probleme début\n");
        *erreur=12;
    }
    else {
        //parcours input
        for (it=0; output[it-1].lexem!=FIN; it++)
        {
            j=0;
            //check si c'est fini en vérifiant le dernier lexem 
            if (ic>strlen(input)-1)// pour vérifier qu'on a bien retré quelque chose dans l'input
            {
              printf("fin\n");
              output[it].lexem=FIN;
              if (output[it-1].lexem==PAR_OUV || output[it-1].lexem==FUN || output[it-1].lexem==OPER)
              {
                *erreur=17;
              }
              printf("=====----->%c=======\n",output[it].lexem);
            }
            // check si c'est un nombre + check erreur
            else if ((input[ic-1]=='(' && input[ic]=='-' && est_chiffre(input[ic+1])==1) || est_chiffre(input[ic])==1)// cdt: les nombres négatifs seront avec des parenthèse pour éviter confusion avec opérateur -
            {   
                printf("else if nombre \n");
                int numero_par=0;
                int i=0 ;
                int compteur=0;
                if (input[ic-1]=='(' && input[ic]=='-')
                {
                  printf("nombre négatif détecté\n");
                  numero_par=1;
                }

                char strN[MAX_FORMULE]="";
                float valeur;

                strN[j]=input[ic];
                j++;
                ic++;
                while((input[ic]=='.')||(est_chiffre(input[ic])==1))
                {
                  printf("while nombre\n");
                  strN[j]=input[ic];
                  ic++;
                  j++;
                } 
                if (numero_par==1)
                {
                  if (input[ic]!=')'){
                    printf("oublie de ) ds neg\n");
                    *erreur=7;
                  }
                }
                for(i=0;i<strlen(strN);i++)
                {
                  if(strN[i]=='.')
                  {
                    compteur++;
                  }
                }
                if(compteur>1)
                {
                  printf(" trop de points\n");
                  *erreur=8;
                }
                else if (output[it-1].lexem==FUN)
                {
                    printf("nombre directement apres une fonction\n" );
                    *erreur=16;
                }
                output[it].lexem=REEL;
                output[it].valeur.reel=atof(strN);
                printf("============%c----->%f===========\n",output[it].lexem,output[it].valeur.reel);
            }
            // check si c'est une variable + check erreur
            else if (est_var(input[ic])==1)
            {   
                if (est_chiffre(input[ic+1])==1 && it!=0|| output[it-1].lexem==REEL && it!=0|| output[it-1].lexem==VAR && it!=0|| output[it-1].lexem==FUN && it!=0|| input[ic+1]=='('||input[ic-1]==')' && it!=0)
                {
                    printf("variable mal placée\n");
                    *erreur=10;
                }
                printf("lexem variable\n");
                output[it].lexem=VAR;
                ic++;
            }
            // check lettre pour voir si fonction  + check erreur
            else if (est_lettre(input[ic])==1)
            {
                printf("lexem lettre \n");
                char strL[taille_fct]="";
                int non_var=1;
                strL[j]=input[ic];
                ic++;
                j++;

                while(est_lettre(input[ic])==1 && non_var==1)
                {
                    strL[j]=input[ic];
                    ic++;
                    j++;
                    if ((input[ic]=='x' || input[ic]=='X'))
                        non_var=0;
                }
                output[it]=assign_fonction(strL,erreur);
                if (output[it-1].lexem==PAR_FERM && it!=0|| output[it-1].lexem==FUN  && it!=0 || output[it-1].lexem==REEL  && it!=0 || output[it-1].lexem==VAR  && it!=0)
                {
                    printf("fonction mal placée\n");
                    *erreur=15;
                }
            }
            // Check si operateur + check erreur
            else if (est_operateur(input[ic])==1)
            {
                printf("lexem opérateur \n");          
                output[it]=assign_operateur(input[ic],erreur);
                if (output[it-1].lexem==OPER && it!=0 || output[it-1].lexem==PAR_OUV && it!=0 ||output[it-1].lexem==FUN && it!=0)
                {
                    printf("opérateur mal placée\n");
                    *erreur=11;
                }
                ic++;  
                
            }
            // check si PAR OUV  + check erreur 
            else if (input[ic]=='(')
            {
                printf("lexem ( \n");
                output[it].lexem=PAR_OUV;
                if (output[it-1].lexem==PAR_FERM && it!=0 || output[it-1].lexem==REEL && it!=0|| output[it-1].lexem==VAR && it!=0)
                {
                    *erreur=18;
                }
                po++;
                ic++;
            }
            // check si PAR FERM + check erreur 
            else if (input[ic]==')')
            {
                printf("lexem ) \n");           
                output[it].lexem=PAR_FERM;
                if (output[it-1].lexem==PAR_OUV || output[it-1].lexem==FUN|| output[it-1].lexem==OPER)
                {
                    *erreur=19;
                }
                pf++;
                ic++;
            }
            // caractère non reconnu ( ex : '¨';'$'...)
            else
            {
                printf("caractère non reconnu\n");
                *erreur=14;
            }
            // check si erreur a été modifié ds ce cas sors de la procédure void
            if (*erreur!=0)
            {
                output[0]=output[it];
                break;
            }
            
        }
    }
    // Check les parenthèses (seulement si il n'y pas eu d'erreur au préalable pour pas modifier l'erreur)
    if (output[it-1].lexem==FIN && pf!=po)
    {
        printf("erreur de parenthèse\n");
        *erreur=9;
    }
}
