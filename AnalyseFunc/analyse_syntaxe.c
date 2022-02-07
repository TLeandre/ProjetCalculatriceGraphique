int i=0;

int isValid(typejeton *tab){
  printf("isValid");
  while(tab[i].lexem!=FIN){
    printf("isvalid boulce while");
    switch(tab[i].lexem){
      case REEL: return 1; break;
      case VAR : return 1; break;
      
      case PAR_OUV:
        printf("isValid: Par Ouv");
        i++;
        if(isValid(tab)){
          i++;
          if(tab[i].lexem!=OPER && tab[i].lexem!=PAR_FERM){
            return 0;
          }else if(tab[i].lexem==OPER){
            printf("isValid:OPER");
            i++;
            if (isValid(tab)){
                i++;
                if(tab[i].lexem==PAR_FERM){
                  return 1;
                }
                else{
                  return 0;
                }
            }else{ 
              return 0;
            }
          }
          else if(tab[i].lexem==PAR_FERM) {
            printf("isValid:Par Ferm");
            return 1;
          }
        }else{
          return 0;
        }
        break;
        
      case FUN:
        printf("isValid:FUN");
        i++;
        return isValid(tab);
        break;
      
      case OPER:
      i++;
      return isValid(tab);
      break;

      default : return 0;    break;
    }
  } 
}


Node *transfert(typejeton*L){
  Node *A;

  //定义一个变量，用来判断括号的结尾
  int NB_PAR_ENSUITE = 0;
  //定义一个新的index，用来循环
  int index_loop = 0;
  
  //循环开头+递归
  loop_start:
 
  switch((L+index_loop)->lexem){


    case FUN:
    
    //当没有括号时and之后没有OPER，直接把FUN拆成（FUN+REEL）或（FUN+VAR）的形式
    if(     (  (L+index_loop+1)->lexem != PAR_OUV && (L+index_loop+2)->lexem != OPER    ) || ((L+index_loop+2)->lexem == FIN) ){

    A = (Node *)malloc(sizeof(Node)) ;
    (*A).jeton.valeur.fonction=(L+index_loop)->valeur.fonction;
    (*A).jeton.lexem=(L+index_loop)->lexem;

    (*A).pjeton_preced = (Node *)malloc(sizeof(Node)) ;
    (*A).pjeton_preced = transfert(L+index_loop+1);

    (*A).pjeton_suiv = (Node *)malloc(sizeof(Node)) ;
    (*A).pjeton_suiv = NULL;
    return A;
    }
    //c'est bon


    else if((L+index_loop+1)->lexem == PAR_OUV){
      A = (Node *)malloc(sizeof(Node)) ;
      (*A).pjeton_preced = (Node *)malloc(sizeof(Node)) ;
      (*A).pjeton_suiv = (Node *)malloc(sizeof(Node)) ;
      
      for(int index=0;(L+index_loop+index)->lexem!=FIN;index++){
      if( (L+index+index_loop)->lexem ==PAR_FERM && NB_PAR_ENSUITE==1){
        
        if ( (L+index+1+index_loop)->lexem == OPER ){
        (*A).jeton.valeur.operateur = (L+index+1+index_loop)->valeur.operateur;
        (*A).jeton.lexem=(L+index+1+index_loop)->lexem;

        (*A).pjeton_suiv = (Node *)malloc(sizeof(Node)) ;
        (*A).pjeton_suiv = transfert(L+index+2+index_loop);

        (L+index+1+index_loop)->lexem = FIN;
        (*A).pjeton_preced = (Node *)malloc(sizeof(Node)) ;
        (*A).pjeton_preced = transfert(L);
        return A;
        }
        else if ( (L+index+1+index_loop)->lexem == FIN ){
          
        (*A).jeton.valeur.fonction=(L+index_loop)->valeur.fonction;
        (*A).jeton.lexem=(L+index_loop)->lexem;
        (L+index+index_loop)->lexem=FIN;
        (*A).pjeton_preced = transfert(L+index_loop+2);
        (*A).pjeton_suiv = NULL;
        
        return A;

        }
        
        
      }
      else if( (L+index+index_loop)->lexem == PAR_FERM && NB_PAR_ENSUITE!=0){
        
        NB_PAR_ENSUITE--;
        
        
        
      }
      else if( (L+index+index_loop)->lexem ==PAR_OUV){
        
        NB_PAR_ENSUITE++;
    
 
      }
    }

      
    }
    else if((L+index_loop+2)->lexem == OPER){
      index_loop++;
      goto loop_start;
      }
  
    
    //case VAR 和 REEL一样 可以直接结尾
    

    case OPER:
    
    A = (Node *)malloc(sizeof(Node)) ;
    (*A).jeton.valeur.operateur = (L+index_loop)->valeur.operateur;
    (*A).jeton.lexem=(L+index_loop)->lexem;

    (*A).pjeton_suiv = (Node *)malloc(sizeof(Node)) ;
    (*A).pjeton_suiv = transfert(L+index_loop+1);
    
    (L+index_loop)->lexem=FIN;
    (*A).pjeton_preced = (Node *)malloc(sizeof(Node)) ;
    
    if((L+index_loop-2)->lexem==FUN ){
      
    (*A).pjeton_preced = transfert(L+index_loop-2);
    return A;

    }
    else{
    (*A).pjeton_preced = transfert(L+index_loop-1);
    return A;
    }
    
  
    case PAR_OUV:
    
    for(int index=0;(L+index)->lexem!=FIN;index++){
      if( (L+index+index_loop)->lexem ==PAR_FERM && NB_PAR_ENSUITE==1){
  
        if ( (L+index+1+index_loop)->lexem == OPER ){
        A = (Node *)malloc(sizeof(Node)) ;
        (*A).jeton.valeur.operateur = (L+index+1+index_loop)->valeur.operateur;
        (*A).jeton.lexem=(L+index+1+index_loop)->lexem;

        (*A).pjeton_suiv = (Node *)malloc(sizeof(Node)) ;
        (*A).pjeton_suiv = transfert(L+index+2+index_loop);

        (L+index+1+index_loop)->lexem = FIN;
        (*A).pjeton_preced = (Node *)malloc(sizeof(Node)) ;
        (*A).pjeton_preced = transfert(L+index_loop);
        return A;
        }
        else if ( (L+index+1+index_loop)->lexem == FIN ){
        (L+index+index_loop)->lexem = FIN;
        return transfert(L+1+index_loop);
        }
        
        
      }
      else if( (L+index)->lexem ==PAR_FERM && NB_PAR_ENSUITE!=0){
        NB_PAR_ENSUITE--;
      }
      else if( (L+index)->lexem ==PAR_OUV){
        NB_PAR_ENSUITE++;
      }


    }


    //管了之前的括号，之后的括号不用管了，因为之前测试过语法，是对的
    case PAR_FERM:
    break;
    case VAR:
    if( (L+index_loop+1)->lexem != OPER ){
      
    A = (Node *)malloc(sizeof(Node)) ;
    (*A).jeton.valeur.reel=(L+index_loop)->valeur.reel;
    (*A).jeton.lexem=(L+index_loop)->lexem;

    (*A).pjeton_preced = (Node *)malloc(sizeof(Node)) ;
    (*A).pjeton_preced = NULL;

    (*A).pjeton_suiv = (Node *)malloc(sizeof(Node)) ;
    (*A).pjeton_suiv = NULL;
    return A;
    }
    else if( (L+index_loop+1)->lexem == OPER ){
      
      index_loop++;
      
      goto loop_start;
    }
    break;
    //c'est bon
    //case VAR 和 REEL一样 可以直接结尾
    case REEL:
    if( (L+index_loop+1)->lexem != OPER ){
    A = (Node *)malloc(sizeof(Node)) ;
    (*A).jeton.valeur.reel=(L+index_loop)->valeur.reel;
    (*A).jeton.lexem=(L+index_loop)->lexem;

    (*A).pjeton_preced = (Node *)malloc(sizeof(Node)) ;
    (*A).pjeton_preced = NULL;

    (*A).pjeton_suiv = (Node *)malloc(sizeof(Node)) ;
    (*A).pjeton_suiv = NULL;
    return A;
    }
    else if( (L+index_loop+1)->lexem == OPER ){
      index_loop++;
      goto loop_start;
    }
    break;
    //c'est bon
    //补全情况
    case FIN:
    exit(1);
    //补全情况
    case ERREUR:
    exit(1);
  }
  return NULL;
}

Node *syntax(typejeton*L){
  i=0;
  if (isValid(L)){
    return transfert(L);
  }
  else {
    printf("Erreur grammaire, veuilliez réessayer.");
    return 0;
  }
}