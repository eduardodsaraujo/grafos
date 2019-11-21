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
    // std::string grafo = "grafo_teste_1";
    // lista.carregar(grafo, false);
    // cout << lista.bipartido() << endl;
    // lista.emparelhamento(grafo);

    std::string grafo = "grafo_peso_0";
    lista.carregar(grafo, true);
    lista.BellmanFord(3, grafo);
}
