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
    Lista lista;
    Lista lista2;
    // std::string grafo = "grafo_teste_1";
    // lista.carregar(grafo, false);
    // cout << lista.bipartido() << endl;
    // lista.emparelhamento(grafo);

    std::string grafo = "ER_50";
    lista.carregar(grafo, true, true, true);
    lista.BellmanFord(1, grafo);
    lista2.carregar(grafo, true, true, false);
    lista2.FloydWarshall(grafo);
}
