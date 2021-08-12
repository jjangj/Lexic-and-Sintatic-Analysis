/* Nome: Jenifer de Jesus Jang 
 * Data de inicio: 15/04/2019
 * Data da ultima alteracao: 29/04/2019
 * Funcao: Analisador sintatico descendente recursivo da linguagem A*/

#include <stdio.h>
#include "analisador_lexico.c"

/*****CABECALHO DAS FUNCOES*******/
void match(token t);
int programa();
int bloco();
int constante();
int variavel();
int comando();
int comando2();
int condicao();
int expr();
int expr2();
int termo();
int termo2();
int fator();
void erro(char c);
/**********************************/

FILE *arq;
token lookahead;

/***************************************************
 * Nome da funcao: main 
 * Funcao: iniciar o analisador sintatico 
 * Parametro: int argc e char *argv[] 
 * Retorno: int 
***************************************************/
int main(int argc, char *argv[]){
  arq= fopen(argv[1], "r");
  if(arq==NULL){
    puts("O arquivo não pode ser aberto");
  }//if
  else{
    lexico(arq);
    lookahead = get_token();
    if(programa()){
      puts("\n********************************");
      puts("\tSintaxe Correta");
      puts("********************************\n");
    }//if
    else{
      erro('m');
    }//else
  }//else
}//main

/***************************************************
 * Nome da funcao: match
 * Funcao: fazer o casamento dos tokens
 * Parametro: token t
 * Retorno: void
***************************************************/
void match(token t){
//  printf("LOOKAHEAD: %s\tTOKEN: %s\n", token_array[lookahead], token_array[t]);
  if(lookahead==t){
    lookahead=get_token();
  }//if
  else{
    printf("Token esperado: %s Token lido: %s\n", token_array[lookahead], token_array[t]);
    erro('m');
  }//else
}//match

/***************************************************
 * Nome da funcao: programa
 * Funcao: simula a producao programa da linguagem A
 * Parametro: -
 * Retorno: int 
***************************************************/
int programa(){
  if(bloco()){
    match(T_PONTO);
    return 1;
  }//if
  else{
    erro('p');
  }//else
}//programa

/***************************************************
 * Nome da funcao: bloco 
 * Funcao: simula a producao bloco da linguagem A
 * Parametro: -
 * Retorno: int 
***************************************************/
int bloco(){
//  puts("BLOCO");
  switch(lookahead){
    case T_CONST:
      match(T_CONST);
      if(constante()){
        match(T_PONTO_VIRGULA);
        if(lookahead == T_VAR){
          bloco();
        }//if
        if(comando()){
          return 1;
        }//if
      }//if
      break;
    case T_VAR:
      match(T_VAR);
      if(variavel()){
        match(T_PONTO_VIRGULA);
        if(lookahead == T_CONST){
          bloco();
        }//if
        if(comando()){
          return 1;
        }//else if
      }//if
      break;
    default:
      if(comando()){
        return 1;
      }//if
      break;
  }//switch
  return 0;//nao caiu em nenhuma das opcoes
}//bloco

/***************************************************
 * Nome da funcao: constante
 * Funcao: simula a producao costante da linguagem A
 * Parametro: -
 * Retorno: int 
***************************************************/
int constante(){
//  puts("CONSTANTE");
  match(T_INDENTIFICADOR);
  match(T_ATRIBUICAO);
  match(T_NUMERO);
  if(lookahead == T_VIRGULA){
    match(T_VIRGULA);
    constante();
  }//if
  return 1;
}//constante

/***************************************************
 * Nome da funcao: variavel 
 * Funcao: simula a producao variavel da linguagem A
 * Parametro: -
 * Retorno: int 
***************************************************/
int variavel(){
//  puts("VARIAVEL");
  match(T_INDENTIFICADOR);
  if(lookahead == T_VIRGULA){
    match(T_VIRGULA);
    variavel();
  }//if
  return 1;
}//variavel

/***************************************************
 * Nome da funcao: comando 
 * Funcao: simula a producao comando da linguagem A
 * Parametro: -
 * Retorno: int 
***************************************************/
int comando(){
//  puts("COMANDO");
  switch(lookahead){
    case T_INDENTIFICADOR:
      match(T_INDENTIFICADOR);
      match(T_ATRIBUICAO);
      if(expr()){
        return 1;
      }//if
      break;
    case T_BEGIN:
      match(T_BEGIN);
      if(comando2()){
        return 1;
      }//if
      break;
    case T_IF:
      match(T_IF);
      if(condicao()){
        match(T_THEN);
        if(comando()){
          return 1;
        }//if
      }//if
      break;
    case T_WHILE:
      match(T_WHILE);
      if(condicao()){
        match(T_DO);
        if(comando()){
          return 1;
        }//if
      }//if
      break;
    case T_WRITE:
      match(T_WRITE);
      if(expr()){
        return 1;
      }//if
      break;
  }//switch
  return 1;
}//comando

/***************************************************
 * Nome da funcao: comando2 
 * Funcao: simula a producao comando2 da linguagem A
 * Parametro: -
 * Retorno: int 
***************************************************/
int comando2(){
// puts("COMANDO2"); 
 if(comando()){
   if(lookahead == T_END){
     match(T_END);
     return 1;
   }//if
   else{
    comando2();
   }//else
 }//if
}//comando2

/***************************************************
 * Nome da funcao: condicao 
 * Funcao: simula a producao condicao da linguagem A
 * Parametro: -
 * Retorno: int 
***************************************************/
int condicao(){
//  puts("CONDICAO");
  if(expr()){
    switch(lookahead){
      case T_IGUAL:
        match(T_IGUAL);
        if(expr()){
          return 1;
        }//if
        break;
      case T_DIFERENTE:
        match(T_DIFERENTE);
        if(expr()){
          return 1;
        }//if
        break;
      case T_MENOR:
        match(T_MENOR);
        if(expr()){
          return 1;
        }//if
        break;
      case T_MAIOR:
        match(T_MAIOR);
        if(expr()){
          return 1;
        }//if
        break;
      case T_MENOR_IGUAL:
        match(T_MENOR_IGUAL);
        if(expr()){
          return 1;
        }//if
        break;
      case T_MAIOR_IGUAL:
        match(T_MAIOR_IGUAL);
        if(expr()){
          return 1;
        }//if
        break;
      default:
        erro('c');
        break;
    }//switch
  }//if
}//condicao

/***************************************************
 * Nome da funcao: expr 
 * Funcao: simula a producao expr da linguagem A
 * Parametro: -
 * Retorno: int 
***************************************************/
int expr(){
//  puts("EXPRESSAO");
  if(termo()){
    if(lookahead == T_MAIS || lookahead == T_MENOS){
      if(expr2()){
        //tirei o match ponto e virgula daqui
        return 1;
      }//if
    }//if
    else if(lookahead == T_PONTO_VIRGULA){
      match(T_PONTO_VIRGULA);
      return 1;
    }//else if
    else if(lookahead == T_THEN){
      return 1;
    }//else if
  }//if
}//expr

/***************************************************
 * Nome da funcao: expr2 
 * Funcao: simula a producao expr2 da linguagem A
 * Parametro: -
 * Retorno: int 
***************************************************/
int expr2(){
//  puts("EXPRESSAO2");
  switch(lookahead){
    case T_MAIS:
      match(T_MAIS);
      if(termo()){
        return 1;
      }//if
      erro('x');
    case T_MENOS:
      match(T_MENOS);
      if(termo()){
        return 1;
      }//if
      erro('x');
    default:
      erro('x');
  }//switch
}//expr2

/***************************************************
 * Nome da funcao: termo 
 * Funcao: simula a producao termo da linguagem A
 * Parametro: -
 * Retorno: int 
***************************************************/
int termo(){
//  puts("TERMO");
  int flag = 1;
  if(fator()){
    while(flag){
      if(lookahead == T_VEZES || lookahead == T_DIVIDE){
        if(termo2()){
          flag=1;
        }//if
        else{
          flag=0;
        }//else
      }//if
      else{
        switch(lookahead){
          case T_PONTO_VIRGULA:
            match(T_PONTO_VIRGULA);
            return 1; 
          case T_DO:
            return 1;
          case T_MAIS:
            return 1;
          case T_MENOS:
            return 1;
          case T_MENOR_IGUAL:
            return 1;
          case T_MAIOR_IGUAL:
            return 1;
          case T_MENOR:
            return 1;
          case T_MAIOR:
            return 1;
          case T_IGUAL:
            return 1;
          case T_DIFERENTE:
            return 1;
          default:
            //printf("lookahead in termo: %s\n", token_array[lookahead]);  
            return 0;
        }//switch
      }//else
    }//while
  }//if
}//termo

/***************************************************
 * Nome da funcao: termo2 
 * Funcao: simula a producao termo2 da linguagem A
 * Parametro: -
 * Retorno: int 
***************************************************/
int termo2(){
//  puts("TERMO2");
  switch(lookahead){
    case T_VEZES:
      match(T_VEZES);
      if(fator()){
        return 1;
      }//if
      erro('t');
    case T_DIVIDE:
      match(T_DIVIDE);
      if(fator()){
        return 1;
      }//if
    default:
      return 1;
  }//switch
}//termo2

/***************************************************
 * Nome da funcao: fator 
 * Funcao: simula a producao fator da linguagem A
 * Parametro: -
 * Retorno: int 
***************************************************/
int fator(){
//  puts("FATOR");
  switch(lookahead){
    case T_INDENTIFICADOR:
      match(T_INDENTIFICADOR);
      return 1;
    case T_NUMERO:
      match(T_NUMERO);
      return 1;
    case T_ABR:
      match(T_ABR);
      if(expr()){
        match(T_FEC);
        return 1;
      }//if
    default:
      erro('f');
  }//switch
}//fator

/***************************************************
 * Nome da funcao: erro 
 * Funcao: imprime que houve erro sintatico e em 
 * qual funcao aconteceu.
 * Parametro: char funcao 
 * Retorno: int 
***************************************************/
void erro(char funcao){
  puts("\n********************************");
  printf("\tErro Sintatico em %c\n\n", funcao);
  puts("********************************\n");
  exit(1);
}//erro
