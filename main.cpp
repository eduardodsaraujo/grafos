#include "Matriz.h"
#include "Matriz.cpp"
#include "Lista.h"
#include "Lista.cpp"

#include <omp.h>
#include <stdio.h>
#include <time.h>

#include <iostream>
#include <string>
#include <sstream>


using namespace std;
//Não Bipartidos: 7, 8 e 9
//Mais de 1 comp: 8
int main()
{
  std::string grafo = "grafo_teste_6";

    Lista lista;
    lista.carregar(grafo);
    lista.bipartido();
    lista.emparelhamento(grafo);
}
