#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

vetorPrincipal vetorP[TAM];

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar()
{
  for(int i = 0; i < TAM; i++){
    vetorP[i].inicio = NULL;
  }

}

void bubbleSort(int arr[], int n) {
    int trocou;
    do {
        trocou = 0;
        for (int i = 0; i < n -1; i++) {
            if (arr[i] > arr[i + 1]) {
                // Troca os elementos se estiverem fora de ordem
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                trocou = 1;
            }
        }
    } while (trocou);
}


int posicaoValida(int posicao){
  if(posicao > 0 && posicao < 11){
    return 1;
  }
  else return 0;
}
// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}




void inserirNoInicio(Lista *lista,int valor,No *novo){

  novo->valor = valor;
  novo->prox = lista->inicio;
  lista->inicio = novo;
}


/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int temEspaco = 0;
    int posicao_invalida = 0;


    if (!posicaoValida(posicao))
    {
       retorno = POSICAO_INVALIDA;
      
    }
  else
    {
        // testar se existe a estrutura auxiliar
        if (vetorP[posicao - 1].inicio != NULL)
        {
          Noe *aux = vetorP[posicao - 1].inicio;
            if (aux->qtd < aux->tamanho)            
            {
                //insere

                aux->vetorAux[aux->qtd] = valor;
                aux->qtd++;
                retorno = SUCESSO;
            }
            else
            {
                retorno = SEM_ESPACO;
            }
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }
 

    return retorno;
}






/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    int retorno = 0;
 if(posicaoValida(posicao)){
   if(tamanho > 0){
     if(vetorP[posicao-1].inicio == NULL){
       Noe * novo = malloc(sizeof(Noe));
       novo->vetorAux = malloc(tamanho * sizeof(int));
       novo->qtd = 0;
       if(novo->vetorAux){
          vetorP[posicao-1].inicio = novo;
         novo->tamanho = tamanho;
          retorno = SUCESSO;
    
       }
       else
         retorno = SEM_ESPACO_DE_MEMORIA;
       
     }
     else
         retorno = JA_TEM_ESTRUTURA_AUXILIAR;
   }
   else
     retorno = TAMANHO_INVALIDO;
 }
  else
    retorno = POSICAO_INVALIDA;
  
   


    return retorno;
}


/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{

  int retorno = 0;
  if(posicaoValida(posicao)){
    if(vetorP[posicao-1].inicio != NULL){
      Noe * aux = vetorP[posicao-1].inicio;
      if(aux->qtd != 0){
        aux->vetorAux[aux->qtd-1]  = ' ';
            aux->qtd--;
            retorno = SUCESSO;
          }
      else
        retorno = ESTRUTURA_AUXILIAR_VAZIA;

    }
    else
      retorno = SEM_ESTRUTURA_AUXILIAR;
  }
  else
    retorno = POSICAO_INVALIDA;





    return retorno;

  
  
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    int retorno = 0, i, j, achou = 0;
  if(posicaoValida(posicao)){
    if(vetorP[posicao-1].inicio != NULL){
      Noe* aux = vetorP[posicao-1].inicio;
      if(aux->qtd != 0){
        for(i=0;i<aux->qtd;i++){
          if(aux->vetorAux[i] == valor){
            achou = 1;
            for(j=i;j<aux->qtd;j++){
              aux->vetorAux[j] = aux->vetorAux[j+1];
            }
            aux->qtd--;
            retorno = SUCESSO;
          }
          
        }
        if(achou == 0)
          retorno = NUMERO_INEXISTENTE;
      }
      else
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
      
    }
    else
      retorno = SEM_ESTRUTURA_AUXILIAR;
  }
  else
    retorno = POSICAO_INVALIDA;
  



  
    return retorno;
}


/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{

    int retorno = 0,i;


  if(posicaoValida(posicao)){
    if(vetorP[posicao-1].inicio != NULL){
      Noe* aux = vetorP[posicao-1].inicio;
      for(i=0;i<aux->qtd;i++){
        vetorAux[i] = aux->vetorAux[i];
       
      }
      
     retorno = SUCESSO;
    }
    else
      retorno = SEM_ESTRUTURA_AUXILIAR;
  }
  else
    retorno = POSICAO_INVALIDA;

    return retorno;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{

    int retorno = 0,i ;


  if(posicaoValida(posicao)){
    if(vetorP[posicao-1].inicio != NULL){
      Noe * aux = vetorP[posicao-1].inicio;
      for(i=0;i<aux->qtd;i++){
        vetorAux[i] = aux->vetorAux[i];
      }

       bubbleSort(vetorAux, aux->qtd);


     retorno = SUCESSO;
    }
    else
      retorno = SEM_ESTRUTURA_AUXILIAR;
  }
  else
    retorno = POSICAO_INVALIDA;

    return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{

    int retorno = 0, i, j=0,cont = 0, contam;
 for(i=0;i<TAM;i++){
   if(vetorP[i].inicio != NULL){
     Noe * aux = vetorP[i].inicio;
     
       for(j=0;j<aux->qtd;j++){
         vetorAux[contam] = aux->vetorAux[j];
         contam++;
       }
    
   }
    else
     cont++;
   
 }
  
  if(cont == 8)
    retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
  else
    retorno = SUCESSO;





  
    return retorno;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = 0, i, j=0,cont = 0,contam = 0;
   for(i=0;i<TAM;i++){
     if(vetorP[i].inicio != NULL){
       Noe * aux = vetorP[i].inicio;

         for(j=0;j<aux->qtd;j++){
           vetorAux[contam] = aux->vetorAux[j];
           contam++;
         }

     }
      else
       cont++;

   }
  
  bubbleSort(vetorAux, contam);
  if(cont == 8)
    retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
  else
      retorno = SUCESSO;






      return retorno;

}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{

    int retorno = 0;
  int tamanhoresultante = 0;


   if (!posicaoValida(posicao))
      {
         retorno = POSICAO_INVALIDA;

      }
    else
      {
          // testar se existe a estrutura auxiliar
          if (vetorP[posicao - 1].inicio != NULL)
          {
            Noe * aux = vetorP[posicao - 1].inicio;
            tamanhoresultante = aux->tamanho + novoTamanho;
            if(tamanhoresultante > 0)
            {
             
              aux->vetorAux = realloc(aux->vetorAux, tamanhoresultante * sizeof(int));
              if(aux->vetorAux != NULL){
              aux->tamanho = tamanhoresultante;
              if(tamanhoresultante < aux->qtd)
              {
                aux->qtd = tamanhoresultante;
              }
                retorno = SUCESSO;
              }
               else
                retorno = SEM_ESPACO_DE_MEMORIA;
              }
              else
              {
                  retorno = NOVO_TAMANHO_INVALIDO;
              }
          }
          else
          {
              retorno = SEM_ESTRUTURA_AUXILIAR;
          }
      }


      return retorno;
  }

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{

    int retorno = 0;

  if(posicaoValida(posicao)){
    if(vetorP[posicao-1].inicio != NULL){
      Noe * aux = vetorP[posicao-1].inicio;
      if(aux->qtd != 0){
        retorno = aux->qtd;
      }
      else
        retorno = ESTRUTURA_AUXILIAR_VAZIA;

    }
    else
      retorno = SEM_ESTRUTURA_AUXILIAR;
  }
  else
    retorno = POSICAO_INVALIDA;

    return retorno;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
  int i;
  
 Lista * lista;
  lista = malloc(sizeof(Lista));
  

  
  for(i=9;i>=0;i--){
    if(vetorP[i].inicio != NULL){
       
      for(int j=vetorP[i].inicio->qtd-1;j>=0;j--)
      {
          No * novo = malloc(sizeof(No));
       
        
         novo->valor = vetorP[i].inicio->vetorAux[j];
        
          novo->prox = lista->inicio;
         lista->inicio = novo;
       
       }
  }
  }

if (lista != NULL) {
    return lista->inicio;
} else 
    return NULL;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
   No * aux;
  aux = inicio;
  int i = 0;
  while(aux != NULL){
    vetorAux[i] = aux->valor;
    aux = aux->prox;
    i++;
    
  }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
  No * remover;
  remover = *inicio;
  while(remover != NULL){
    No * proximo;
    proximo = remover->prox;
    free(remover);
    remover = proximo;
  }
  *inicio = NULL;
}


/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
}
