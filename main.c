#include "main.h"

/*Función que inserta números aleatorios en una lista*/
void inserta_datos_de_prueba(Lista lista);

int main()
{
    // Se crea la lista
    Lista lista = crea_lista();
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se insertan datos de prueba
    inserta_datos_de_prueba(lista);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento de la lista
    Elemento *borrado = quita_elemento(lista, 0);
    if (borrado != NULL) {free(borrado->valor);}
    free(borrado);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento que no existe en la lista
    quita_elemento(lista, longitud(lista));
    printf("La lista tiene %d elementos\n", longitud(lista));

    //Se imprime la lista antes de ordenar
    imprime_lista_int(lista);
    ordena_lista(lista, &cmp_int);

    //Se imprime la lista después de ordenar
    imprime_lista_int(lista);

    //Se libera la memoria ocupada
    borra_lista(lista);
}

void inserta_datos_de_prueba(Lista lista)
{
    srand(time(NULL));
    int *num_a_insertar;
    int indice;
    for (indice = 0; indice < 20; ++indice) {
        num_a_insertar = malloc(sizeof(int));
        *num_a_insertar = rand() % 100;
        inserta_elemento(lista, num_a_insertar);
    };
}

/*Compara 2 'Elemento' que contienen como valor un 'int'*/
int cmp_int(const void* a, const void* b){
    // Los apuntadores se pasan a enteros.
    int _a = *(int *)a;
    int _b = *(int *)b;
    //Comparamos
    if(_a == _b){
          return 0;
          }
    if(_a > _b){
          return 1;
          }
    return -1;
    }

/*Función que ordena una lista usando una función comparadora*/
//Recomiendo apoyarte de tu función 'cmp_int', qsort y un arreglo
void ordena_lista(Lista lista, int(*cmp)(const void*, const void*)){
  int i,j; //indices para recorrer la lista
  Elemento *aux,*aux2,*elemAnt;
  for(i = 1; i < longitud(lista); i++){
    j = 1;
    aux = *lista;
    elemAnt = NULL;
    while(j <= (longitud(lista) - i)){
      aux2 = aux->siguiente;
      if((*cmp)(aux->valor,aux2->valor) == 1){
        aux->siguiente = aux2->siguiente;
        aux2->siguiente = aux;
        if(elemAnt == NULL){
          *lista = aux2;
          elemAnt = *lista;
        }else{
          elemAnt->siguiente = aux2;
          elemAnt = aux2;
        }
        aux = elemAnt->siguiente;
      }else{
        elemAnt = aux;
        aux = aux2;
      }
      j++;
    }
  }
}

/*Libera(free) la memoria ocupada por la lista, sus elementos y valores*/
//No se te olvide liberar la memoria de cada elementoslemento y su valor.
void borra_lista(Lista lista){
  size_t n = 0;
  for(n = 0; n < longitud(lista)-1; n++){
    quita_elemento(lista,n);
  }
  Elemento *aux = *lista, *aux2 = NULL;
  while(aux != NULL){
    aux2 = aux;
    aux = aux->siguiente;
    free(aux2);
  }
  *lista = NULL;
}

/*Remueve un elemento de una lista en una posición dada*/
//Si la posición no coincide con ningún elemento se regresa NULL
Elemento *quita_elemento(Lista lista, size_t posicion){
  size_t n = 0;
  Elemento *aux = *lista;
  Elemento *elemAnt = aux, *elemAct = aux;
  void *valores = NULL;

  size_t numElem = longitud(lista);
  if(posicion >= numElem || posicion < 0)
    return NULL;

  for(n = 0; n < posicion; n++){
    elemAnt = elemAct;
    elemAct = elemAct->siguiente;
  }

  if(elemAct == aux)
    aux = aux->siguiente;
  else
    valores = elemAct->valor;
  free(elemAct);
  *lista = aux;
  return valores;
}

/*Imprime los elementos de la lista como enteros*/
void imprime_lista_int(Lista lista){
  size_t n = 0;
  Elemento *aux = *lista;
  printf("[");
  for(n = 0; n < longitud(lista); n++){
    int _a = *(int *)aux->valor;
    printf("%d ",_a);
    aux = aux->siguiente;
  }
  printf("]\n");
}

/*Crea una lista vacía*/
Lista crea_lista(){
  Elemento *l = NULL;
  l = malloc(sizeof(Elemento));
}

/*Inserta un elemento en la lista y se regresa el nuevo tamaño de la lista*/
int inserta_elemento(Lista lista, void *dato){  
  Elemento *aux = *lista;
  Elemento *aux2 = NULL;
  aux2 = (Elemento *)malloc(sizeof(Elemento));
  aux2->valor = dato;
  aux2->siguiente = aux;
  aux = aux2;
  *lista = aux;
  return longitud(lista);
}

/*Regresa el número de elementos en la lista*/
size_t longitud(Lista lista){
  Elemento *aux = *lista;
  size_t n;
  n = 0;
  while(aux !=  NULL){
    n++;
    aux = aux->siguiente;
  }
  return n;
}