#ifndef CONSTANTES_H
#define CONSTANTES_H

using namespace std;

// Constantes Globais
namespace Constantes
{
  //true = entrada manual. false = pega pelas const abaixo
  const bool inOverride = false;
  const bool log = false;
  const bool runBFS = true;
  const bool runDFS = false;

  //nome do arquivo padrão
  const string arquivoDefault = "as_graph";

  //1 = matriz, 2 = lista, qualquer outra coisa = pula direto para as calcular as componentes
  const string estruturaDefault = "1";

  //1 para paralelizar o carregamento de matriz em memória, 2 para rodar uma bfs em cada thread, qualquer outra coisa para rodar single
  //     OBSERVAÇÕES: PARA UM LOG PRECISO, UTILIZAR 1 (Paralelizar apenas o carregamento de matriz)
  //     CAUTION: CADA BFS IRÁ ALOCAR SEU PRÓPRIO ESPAÇO EM MEMÓRIA!
  const string ompDefault = "1";

  //1 para calcular as componentes conexas, qualquer outra coisa para fechar direto
  const string componentesDefault = "2";

  //1 para calcular o diâmetro, qualquer outra coisa para fechar direto
  const string diametroDefault = "2";

  //Vértice mínimo para iniciar as BFS/DFS
  const int vMin = 1;

  //Vértice máximo para iniciar as BFS/DFS
  const int vMax = 1;
}

#endif
