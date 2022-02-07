// énumération des différents types de lexems existants
typedef enum{
    REEL,OPER,FUN,ERREUR,FIN,PAR_OUV,PAR_FERM,VAR 
}typelexem;

//énumération des différnents types d'opérateurs éxistants
typedef enum{
    PLUS,MOINS,FOIS,DIV,PUIS
}typeoperateur;

//énumération des différents types de fonctions éxistantes
typedef enum{
    SIN,SQRT,LOG,COS,TAN,EXP,ENTIER,VAL_NEG
}typefonction;

//énumération des différents types de valeurs éxistantes
typedef union{
    float reel;
    typefonction fonction;
    typeoperateur operateur;
    //typeerreur erreur;
}typevaleur;

// énumération des différents types de jetons éxistants
typedef struct
{
    typelexem lexem;
    typevaleur valeur;
}typejeton;

//déclaration de l'arbre
typedef struct Node
{
    typejeton jeton;
    struct Node *pjeton_preced;//fils gauche
    struct Node *pjeton_suiv;
} Node;
typedef Node *Arbre;
