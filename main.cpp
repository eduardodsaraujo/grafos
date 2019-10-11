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

//true = entrada manual. false = pega pelas const abaixo
const bool inOverride = false;
const bool logFile = false;
const bool runBFS = false;
const bool runDFS = false;
//nome do arquivo padrão

const string arquivoDefault = "grafo_1";
// const string arquivoDefault = "dblp";
// const string arquivoDefault = "live_journal";

//1 = matriz, 2 = lista, qualquer outra coisa = pula direto para as calcular as componentes
const string estruturaDefault = "2";

//1 para paralelizar o carregamento de matriz em memória, 2 para rodar uma bfs em cada thread, qualquer outra coisa para rodar single
//     OBSERVAÇÕES: PARA UM LOG PRECISO, UTILIZAR 1 (Paralelizar apenas o carregamento de matriz)
//     CAUTION: CADA BFS IRÁ ALOCAR SEU PRÓPRIO ESPAÇO EM MEMÓRIA!
const string ompDefault = "3";
//1 para calcular as componentes conexas, qualquer outra coisa para fechar direto
const string componentesDefault = "2";
//1 para calcular o diâmetro, qualquer outra coisa para fechar direto
const string diametroDefault = "1";

//Vértice mínimo para iniciar as BFS/DFS
const int vMin = 1;
//Vértice máximo para iniciar as BFS/DFS
const int vMax = 1;


int main()
{

    Lista lista;
    clock_t tOpen = clock();

  /*  for (int i = 1; i <= 100; i++)
    {
      lista.Pesos(i, false, false);
      lista.excentricidade();
    }*/
    // 2722,Edsger W. Dijkstra
    // 11365,Alan M. Turing
    // 471365,J. B. Kruskal
    // 5709,Jon M. Kleinberg
    // 11386,Éva Tardos
    // 343930,Daniel R. Figueiredo

    // lista.buscaNomes("123");

    // lista.carregar("rede_colaboracao");
    lista.carregar("grafo_1");
    lista.Pesos(1, false, true);

    lista.maiorGrau(3);
    // lista.Pesos(343930, false, true);
    // lista.vizinhos(343930);
    // lista.caminho(11365);
    // lista.caminho(471365);
    // lista.caminho(11365);
    // lista.caminho(5709);
    // lista.caminho(11386);
    // lista.caminho(343930);
    // lista.minimumSpanningTree();
    // lista.distanrciaMedia();

    cout << "Tempo de execução: " << (clock() - tOpen)/(CLOCKS_PER_SEC/1000) << " ms" << endl;


    // lista.maiorGrau(1);
  
}
