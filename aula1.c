/* GLC G
 * G = <{E}{a,+},P,E> 
 * P = < E->
 * P = <E -> aX, X -> +aX | lambda}
 * analisador sintatico descendente recursivo
*/

#include <stdio.h>
#include <stdlib.h>

char lookahead;
void E();
void X();
void error();
void match(char x);

int main(){
  lookahead = getchar();
  E();
  if(lookahead =='\n'){
    printf("sintaxe correta\n");
  }//if
  else{
    error();
  }//else

  return 0;
}//main

void E(){
  if (lookahead == 'a'){
    match('a');
    X();
  }
  else{
    error();
  }
}

//X -> +aX
void X(){
  if(lookahead=='+'){
    match('+');
    match('a');
    X();
 }
 else{
   return;
 }//else
}//X

void error(){
  puts("erro lexico/sintatico\n"); 
  exit(1);
}//error

void match(char x){
  if(x==lookahead){
    lookahead=getchar();
  }
  else{
    error();
  }
}//match


