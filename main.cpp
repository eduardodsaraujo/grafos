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
//
// //true = entrada manual. false = pega pelas const abaixo
// const bool inOverride = false;
// const bool logFile = false;
// const bool runBFS = false;
// const bool runDFS = false;
// //nome do arquivo padrão
//
// const string arquivoDefault = "grafo_4";
// // const string arquivoDefault = "dblp";
// // const string arquivoDefault = "live_journal";
//
// //1 = matriz, 2 = lista, qualquer outra coisa = pula direto para as calcular as componentes
// const string estruturaDefault = "2";
//
// //1 para paralelizar o carregamento de matriz em memória, 2 para rodar uma bfs em cada thread, qualquer outra coisa para rodar single
// //     OBSERVAÇÕES: PARA UM LOG PRECISO, UTILIZAR 1 (Paralelizar apenas o carregamento de matriz)
// //     CAUTION: CADA BFS IRÁ ALOCAR SEU PRÓPRIO ESPAÇO EM MEMÓRIA!
// const string ompDefault = "3";
// //1 para calcular as componentes conexas, qualquer outra coisa para fechar direto
// const string componentesDefault = "2";
// //1 para calcular o diâmetro, qualquer outra coisa para fechar direto
// const string diametroDefault = "1";
//
// //Vértice mínimo para iniciar as BFS/DFS
// const int vMin = 1;
// //Vértice máximo para iniciar as BFS/DFS
// const int vMax = 1;
//

int main()
{

    Lista lista;
    lista.carregar("grafo_6");
    clock_t tOpen = clock();
    lista.Pesos(1, false, true);
    lista.maiorGrau(3);
    // lista.vizinhos(343930);

    cout << "Tempo de execução: " << (clock() - tOpen)/(CLOCKS_PER_SEC/1000) << " ms" << endl;
}
