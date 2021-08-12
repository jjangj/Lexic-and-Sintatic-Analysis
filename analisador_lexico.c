/* Universidade Estadual do Sudoeste da Bahia
 * Nome: Jenifer de Jesus Jang e Stefanie Caroline
 * Data de inicio: 21/01/2019
 * Data da ultima alteracao: 16/02/2019
 * Funcao: Analisador lexico da linguagem A implementado
 * com switch aninhado dentro do while*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/****************DECLARACAO DE TIPOS ENUMERADOS*******************************************/
typedef enum estados{INICIAL, MAIOR, MAIOR_IGUAL, MENOR, MENOR_IGUAL, DIFERENTE, IGUAL, INDENTIFICADOR, NUMERO, ABRE_PARENTESE, FECHA_PARENTESE, PONTO_VIRGULA, VIRGULA, PONTO, DOIS_PONTOS, ATRIBUICAO, MENOS, MAIS, VEZES, DIVIDE, ERRO, ERRO_SIMBOLO, INICIO_ERRO} estado;

typedef enum tokens{T_MAIOR, T_MENOR, T_MENOR_IGUAL, T_MAIOR_IGUAL, T_DIFERENTE, T_IGUAL, T_MAIS, T_MENOS, T_DIVIDE, T_VEZES, T_ATRIBUICAO, T_PONTO, T_DOIS_PONTOS, T_ABR, T_FEC, T_NUMERO, T_INDENTIFICADOR, T_VIRGULA, T_PONTO_VIRGULA, T_CONST, T_VAR, T_BEGIN, T_IF, T_WHILE, T_WRITE, T_END, T_THEN, T_DO} token;
/*****************************************************************************************/

const char *token_array[]={"MAIOR", "MENOR", "MENOR_IGUAL", "MAIOR_IGUAL", "DIFERENTE", "IGUAL", "MAIS", "MENOS", "DIVIDE", "VEZES", "ATRIBUICAO", "PONTO", "DOIS_PONTOS", "ABR", "FEC", "NUMERO", "INDENTIFICADOR", "VIRGULA", "PONTO_VIRGULA", "CONST", "VAR", "BEGIN", "IF", "WHILE", "WRITE", "END", "THEN", "DO"};

/****************PROTOTIPO DE FUNCOES*******************************************/
token automato();//implementacao do automato para recohecimento dos tokens
token get_token(); //retorna o token lido
void init();//inicializa a arvore binaria
int buscar(char *dado);//faz busca na arvore
char* strupr(char* str);//transforma uma string em maiuscula
int compara(char str1[], char str2[]);
/*******************************************************************************/

/****************DECLARACAO DE VARIAVEIS****************************************/
char ch;
char *lexema;
char *ch_ptr;
char *reservada;
int linha=1;
int flag=0;//auxilia na identificacao de erros
int reconhece = 0;
estado atual;
FILE *arquivo;
/*******************************************************************************/

void lexico(FILE *f){ 

  atual=INICIAL;//afd comecando no estado inicial
  init();//inicia a arvore binaria com as palavras reservadas
  arquivo = f; 
  lexema = (char*) malloc (sizeof(char*));//aloca memoria para o lexema 
  reservada = (char*) malloc (sizeof(char*));//aloca memoria para o lexema 

}//lexico

token get_token(){
  token t;
  reconhece = 0;
  while(((ch=fgetc(arquivo))!=EOF) &&(reconhece != 1)){
    t = automato();
  }//while
    printf("token: %s\n", token_array[t]);
  return t;
}//get_token

token automato(){
  ch_ptr=&ch;//ch_ptr recebe o endereco de ch
  switch(atual){
    case INICIAL://quando estiver no estado inicial
      if(isalpha(ch)){//se for uma letra
        strcat(lexema,ch_ptr);
        atual=INDENTIFICADOR;//passa para o estado INDENTIFICADOR 
      }//if
      else if(isdigit(ch)){//se for um numero
        strcat(lexema,ch_ptr); 
        atual=NUMERO;//passa para o estado NUMERO
      }//else if
      else{//se for qualquer outro caracter
        switch(ch){ 
          case '\n'://se for quebra de linha 
            if(flag==1){
              atual=ERRO;
            }//if
            else{
              strcpy(lexema,"");//copia uma cadeia vazia para lexema (esvazia)
            }//else 
            linha++;
            break;
          case ' '://se for espaco
            if(flag==1){
              atual=ERRO;
            }//if
            else{
              strcpy(lexema,"");//copia uma cadeia vazia para lexema (esvazia)
            }//else
            break;
          case '\t'://se for tabulacao
            if(flag==1){
              atual=ERRO;
            }//if
            else{
              strcpy(lexema,"");
            }//else
            break;
          case '>'://caso maior
            atual=MAIOR;
            strcat(lexema, ch_ptr);//concatena o caracter lido com os anteriores para formar o lexema
            break;
          case '<'://caso menor
            atual=MENOR;
            strcat(lexema, ch_ptr);
            break;
          case '='://caso igual
            atual=IGUAL;
            strcat(lexema, ch_ptr);
            break;
          case ':':
            atual=DOIS_PONTOS;// case dois pontos
            strcat(lexema, ch_ptr);
            break;
          case '-'://case menos
            atual=MENOS;
            strcat(lexema, ch_ptr);
            break;
          case '+'://case mais 
            strcat(lexema, ch_ptr);
            atual=MAIS;
            break;
          case '*'://case vezes
            atual=VEZES;
            strcat(lexema, ch_ptr);
            break;
          case '/'://case divide
            atual=DIVIDE;
            strcat(lexema, ch_ptr);
            break;
          case '('://case abre paretese
            atual=ABRE_PARENTESE;
            strcat(lexema, ch_ptr);
            break;
          case ')'://case fecha parentese
            atual=FECHA_PARENTESE;
            strcat(lexema, ch_ptr);
            break;
          case ','://case virgula
            atual=VIRGULA;
            strcat(lexema, ch_ptr);
            break;
          case '.'://case ponto
            atual=PONTO;
            strcat(lexema, ch_ptr);
            break;
          case ';'://case ponto e virgula
            atual=PONTO_VIRGULA;
            strcat(lexema, ch_ptr);
            break;
          default://se for qualquer outro caracter nao e reconhecido pela linguagem
            strcat(lexema, ch_ptr);
            atual=ERRO_SIMBOLO;
            break;
        }//switch
      }//else
      break;
    case IGUAL://estado IGUAL 
      strcpy(lexema, "");
      atual=INICIAL;
      reconhece =1;
      return T_IGUAL;
    case MAIOR://estado MAIOR 
      switch(ch){
        case '='://case =
          strcat(lexema,ch_ptr);
          atual=MAIOR_IGUAL;    
          break;
        default:
          strcpy(lexema, "");
          atual=INICIAL;
          reconhece =1;
          return T_MAIOR;
      }//switch
      break;
    case MENOR://estado MENOR
      switch(ch){
        case '=':
          strcat(lexema, ch_ptr);
          atual=MENOR_IGUAL;
          break;
        case '>':
          strcat(lexema,ch_ptr);
          atual=DIFERENTE;
          break;
        default:
          strcpy(lexema, "");
          atual=INICIAL;
          reconhece =1;
          return T_MENOR;
      }//switch
      break;
    case MAIOR_IGUAL://estado MAIOR_IGUAL
      strcpy(lexema, "");
      fseek(arquivo,-1, SEEK_CUR);
      atual=INICIAL;
      reconhece =1;
      return T_MAIOR_IGUAL;
    case MENOR_IGUAL://estado MENOR_IGUAL
      strcpy(lexema, "");
      fseek(arquivo,-1, SEEK_CUR);
      atual=INICIAL;
      reconhece =1;
      return T_MENOR_IGUAL;
    case DIFERENTE://estado DIFERENTE
      strcpy(lexema, "");
      fseek(arquivo,-1, SEEK_CUR);
      atual=INICIAL;
      reconhece =1;
      return T_DIFERENTE;
    case MAIS://estado MAIS
      strcpy(lexema, "");
      fseek(arquivo,-1, SEEK_CUR);
      atual=INICIAL;
      reconhece =1;
      return T_MAIS;
    case MENOS://estado MENOS
      strcpy(lexema, "");
      fseek(arquivo,-1, SEEK_CUR);
      atual=INICIAL; 
      reconhece =1;
      return T_MENOS;
    case VEZES://estado VEZES
      strcpy(lexema, "");
      fseek(arquivo,-1, SEEK_CUR);
      atual=INICIAL; 
      reconhece =1;
      return T_VEZES;
    case DIVIDE://estado DIVIDE
      strcpy(lexema, "");
      fseek(arquivo,-1, SEEK_CUR);
      atual=INICIAL; 
      reconhece =1;
      return T_DIVIDE;
    case ABRE_PARENTESE://estado ABRE_PARENTESE
      strcpy(lexema, "");
      fseek(arquivo,-1, SEEK_CUR);
      atual=INICIAL; 
      reconhece =1;
      return T_ABR;
    case FECHA_PARENTESE://estado FECHA_PARENTESE
      strcpy(lexema, "");
      fseek(arquivo,-1, SEEK_CUR);
      atual=INICIAL; 
      reconhece =1;
      return T_FEC;
    case PONTO://estado PONTO
      strcpy(lexema, "");
      fseek(arquivo,-1, SEEK_CUR);
      atual=INICIAL; 
      reconhece =1;
      return T_PONTO;
    case PONTO_VIRGULA://estado PONTO_VIRGULA
      strcpy(lexema, "");
      fseek(arquivo,-1, SEEK_CUR);
      atual=INICIAL; 
      reconhece =1;
      return T_PONTO_VIRGULA;
    case VIRGULA://estado VIRGULA
      strcpy(lexema, "");
      fseek(arquivo,-1, SEEK_CUR);
      atual=INICIAL; 
      reconhece =1;
      return T_VIRGULA;
    case DOIS_PONTOS://estado PONTO
      switch(ch){
        case '=':
          strcat(lexema, ch_ptr);
          atual=ATRIBUICAO; 
          break;
        default://apagar
          atual=ERRO; 
          break;
      }//switch
      break;
    case ATRIBUICAO://estado ATRIBUICAO
      strcpy(lexema, "");
      fseek(arquivo,-1, SEEK_CUR);
      atual=INICIAL; 
      reconhece =1;
      return T_ATRIBUICAO;
    case INDENTIFICADOR://estado INDENTIFICADOR
      if(isalpha(ch)||isdigit(ch)){
        strcat(lexema, ch_ptr);
      }//if
      else if(buscar(lexema)){//verifica se e palavra reservada
        strcpy(reservada, lexema);
        reservada=strupr(reservada);
        strcpy(lexema, "");
        fseek(arquivo,-1, SEEK_CUR);
        atual=INICIAL; 
        reconhece =1;
        if(compara(reservada,"CONST")){
          return T_CONST;
        }//if
        else if(compara(reservada, "VAR")){
          return T_VAR;
        }//else if
        else if(compara(reservada, "BEGIN")){
          return T_BEGIN;
        }//else if
        else if(compara(reservada, "IF")){
          return T_IF;
        }//else if
        else if(compara(reservada, "WHILE")){
          return T_WHILE;
        }//else if
        else if(compara(reservada, "WRITE")){
          return T_WRITE;
        }//else if
        else if(compara(reservada, "END")){
          return T_END;
        }//else if
        else if(compara(reservada, "THEN")){
          return T_THEN;
        }//else if
        else{
          return T_DO;
        }//else
      }//else if
      else if(flag==1){
        atual=ERRO;
      }//else if
      else{//INDENTIFICADOR
        fseek(arquivo,-1, SEEK_CUR);
        strcpy(lexema, "");
        atual=INICIAL; 
        reconhece =1;
        return T_INDENTIFICADOR;
      }//else
      break;
    case NUMERO://estado NUMERO
      if(isdigit(ch)){
        strcat(lexema, ch_ptr);
      }//if
      else if(isalpha(ch)){
        strcat(lexema, ch_ptr);
        flag=1;
        atual=INICIAL;
      }//else if
      else{
        strcpy(lexema, "");
        fseek(arquivo,-1, SEEK_CUR);//volta um caracter no arquivo
        atual=INICIAL; 
        reconhece =1;
        return T_NUMERO;
      }//else
      break;
    case ERRO://case ERRO
      printf("TOKEN: %-20s LEXEMA: %-10s LINHA: %d\n","ID. MAL FORMADO", lexema, linha);
      strcpy(lexema, "");
      fseek(arquivo,-1, SEEK_CUR);
      atual=INICIAL; 
      flag=0;
      reconhece =1;
      break;
    case ERRO_SIMBOLO: //erro de simbolo nao reconhecido
      printf("TOKEN: %-20s LEXEMA: %-10s LINHA: %d\n","SIMBOLO DESCONHECIDO", lexema, linha);
      strcpy(lexema, "");
      fseek(arquivo,-1, SEEK_CUR);
      atual=INICIAL; 
      reconhece =1;
      break;
  }//switch
}//automato

struct no{
  char dado[5];//5 porque o tamanho da maior palavra reservada e 5
  struct no *direita;
  struct no *esquerda;
};

struct no *raiz; //Ponteiro da raiz
struct no *alocar; //Ponteiro para fazer alocação

int buscar(char *dado) {
  struct no *ponteiro;
  ponteiro = raiz;
  while (ponteiro) { 
    if (strcmp(dado, ponteiro->dado)==0) //Faz a comparação de strings
      return 1; //Retorna ponteiro se o encontrar
    if (strcmp(dado, ponteiro->dado)>0)
      ponteiro = ponteiro->direita;
    else
      ponteiro = ponteiro->esquerda; 
  }//while
  return 0; 
}//buscar

void inserir(char *dado) {
  alocar = (struct no *) malloc(sizeof(struct no)); //Faz alocação na memória
  if (!alocar) { //Se não for possível a alocação, sai do programa
    printf("Falta de memória"); 
    exit(0);
  }
  strcpy(alocar->dado, dado); //Copia o dado para o novo nó alocado
  if (!raiz) { //Se não houver elemento ainda na árvore, insere na raiz
    raiz = alocar;
  }
  else{ //se não...
    struct no *ponteiro=raiz; 
    struct no *ponteiroAnterior=NULL;
    while (ponteiro) { //Faz a busca do lugar ao qual deve ser inserido o nó
      ponteiroAnterior = ponteiro;
      if (strcmp(dado, ponteiro->dado)==0) {
        printf("\nDado inserido já existe!");
        return;
      }//if
      if (strcmp(dado, ponteiro->dado)>0){
        ponteiro = ponteiro->direita;
      }//if
      else {
        ponteiro = ponteiro->esquerda; 
      }//else
    }//while
    if(strcmp(dado, ponteiroAnterior->dado)>0) {
      ponteiroAnterior->direita = alocar; 
      //atribui o endereço de alocação ao ponteiro da direita do no anterior
    }//if 
    else{
      ponteiroAnterior->esquerda = alocar;
      //atribui o endereço de alocação ao ponteiro da esquerda do no anterior
    }//else
  }//else
}//inserir

void init(){
  inserir("if");
  inserir("end");
  inserir("do");
  inserir("const");
  inserir("begin");
  inserir("then");
  inserir("var");
  inserir("while");
  inserir("write");
}//init

char *strupr(char *str){
  unsigned char *p = (unsigned char *)str;
  while (*p) {
    *p = toupper(*p);
    p++;
  }//while
  return str;
}//strupr 

int compara(char str1[], char str2[]){
  int tamanho = strlen(str1);  
  int tamanho2 = strlen(str2);
  if(tamanho != tamanho2){
    return 0;
  }//if
  for(int i = 0; i < tamanho; i++){
    if(str1[i]!=str2[i]){
      return 0;
    }//if
  }//for
  return 1;
}

