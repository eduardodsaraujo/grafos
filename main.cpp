#include <string>
#include <omp.h>
#include <stdio.h>
#include <time.h>

#include "src/Lista.cpp"
#include "src/Matriz.cpp"
#include "include/Matriz.h"
#include "include/Lista.h"
#include "include/Constantes.h"

using namespace std;

int main()
{
  //Define o arquivo de entrada
  string inputFile;
  if (Constantes::inOverride == true)
  {
    cout << "Insira o nome do arquivo: ";
    cin >> inputFile;
  }
  else
  {
    inputFile = Constantes::arquivoDefault;
  }


  //Define o tipo de estrutura a ser utilizado
  string estrutura;
  if (Constantes::inOverride == true)
  {
    cout << "Digite o tipo de estrutura a ser utilizado - 1 para matriz, 2 para lista, e qualquer outra tecla para pular: ";
    cin >> estrutura;
  }
  else
  {
    estrutura = Constantes::estruturaDefault;
  }

  //Define as opções de paralelização
  string ompSettings;
  if (Constantes::inOverride == true)
  {
    if (estrutura == "1")
    {
      cout << "Digite a parte a ser paralelizada - 1 para  o carregamento da matriz e 2 para as BFS/DFS: ";
      cin >> ompSettings;
    }
    else
    {
      cout << "Digite 1 para rodar em single-thread e 2 para rodar em paralelo: ";
      cin >> ompSettings;
    }
  }
  else
  {
    ompSettings = Constantes::ompDefault;
  }


  std::ofstream openTime;
  openTime.open("run_log.txt");
  clock_t tOpen = clock();

  //Caso o usuário escolha MATRIZ:
  if (estrutura == "1")
  {
    clock_t tInicio = clock();

    //Carrega a matriz em memória
    Matriz matriz;
    if (ompSettings == "1")
    {
      matriz.carregar(inputFile, ompSettings);
    }

    //Inicia o timer
    ofstream executionTime;
    executionTime.open((inputFile+"_log_matrizAdj.txt").c_str());
    executionTime << "Tempo para iniciar o vetor: " << (clock() - tInicio)/(CLOCKS_PER_SEC/1000) << " ms" << endl;

    //BFS e DFS para cada ponto. Roda em paralelo caso seja escolhida a opção 2
    #pragma omp parallel for if (ompSettings == "2")
    for (int i = Constantes::vMin; i <= Constantes::vMax; i++)
    {
      if (ompSettings == "1")
      {
        std::ostringstream nomeSaida;
        nomeSaida << i; //Dá cast para string

        //BFS
        if (Constantes::runBFS == true)
        {
          tInicio = clock();
          // cout << "Iniciando a BFS em matriz com inicio no vertice " << i << endl;
          matriz.BFS(i, (inputFile+"_DFS_MatrizAdj_"+nomeSaida.str()).c_str(), Constantes::log);
          if (Constantes::log == true)
          {
            matriz.geraEstatisticas((inputFile+"_BFS_"+nomeSaida.str()).c_str());
            executionTime << "Tempo para rodar a BFS a partir do vértice " << i << ": " << (clock() - tInicio)/(CLOCKS_PER_SEC/1000) << " ms" << endl;
          }
        }

        //DFS
        if (Constantes::runDFS == true)
        {
          tInicio = clock();
          // cout << "Iniciando a DFS em matriz com inicio no vertice " << i << endl;
          matriz.DFS(i, (inputFile+"_DFS_MatrizAdj_"+nomeSaida.str()).c_str(), Constantes::log);
          if (Constantes::log == true)
          {
            matriz.geraEstatisticas((inputFile+"_DFS_"+nomeSaida.str()).c_str());
            executionTime << "Tempo para rodar a DFS a partir do vértice " << i << ": " << (clock() - tInicio)/(CLOCKS_PER_SEC/1000) << " ms" << endl;
          }
        }
      }
      else
      {
        std::ostringstream nomeSaida;
        nomeSaida << i; //Dá cast para string

        //Inicializa uma matriz interno
        //TODO: Criar uma classe SÓ PARA A MATRIZ, para poder compartilhar
        Matriz matrizInt;
        matrizInt.carregar(inputFile, ompSettings);

        //BFS
        if (Constantes::runBFS == true)
        {
          tInicio = clock();
          // cout << "Iniciando a BFS em matriz com inicio no vertice " << i << endl;
          matrizInt.BFS(i, (inputFile+"_BFS_MatrizAdj_"+nomeSaida.str()).c_str(), Constantes::log);
          if (Constantes::log == true)
          {
            matrizInt.geraEstatisticas((inputFile+"_BFS_"+nomeSaida.str()).c_str());
            executionTime << "Tempo para rodar a BFS a partir do vértice " << i << ": " << (clock() - tInicio)/(CLOCKS_PER_SEC/1000) << " ms" << endl;
          }
        }

        //DFS
        if (Constantes::runDFS == true)
        {
          tInicio = clock();
          // cout << "Iniciando a DFS em matriz com inicio no vertice " << i << endl;
          matrizInt.DFS(i, (inputFile+"_DFS_MatrizAdj_"+nomeSaida.str()).c_str(), Constantes::log);
          if (Constantes::log == true)
          {
            matrizInt.geraEstatisticas((inputFile+"_DFS_"+nomeSaida.str()).c_str());
            executionTime << "Tempo para rodar a BFS a partir do vértice " << i << ": " << (clock() - tInicio)/(CLOCKS_PER_SEC/1000) << " ms" << endl;
          }
        }
      }
    }
    executionTime.close(); //Finaliza o timer
  }
  //Caso o usuário escolha LISTA
  else if (estrutura == "2")
  {
    clock_t tInicio = clock();

    //Carrega a matriz em memória
    Lista lista;
    if (ompSettings == "1")
    {
      lista.carregar(inputFile);
    }

    //Inicia o timer
    ofstream executionTime;
    executionTime.open((inputFile+"_log_listaAdj.txt").c_str());
    executionTime << "Tempo para iniciar o vetor: " << (clock() - tInicio)/(CLOCKS_PER_SEC/1000) << " ms" << endl;

    //BFS e DFS para cada ponto. Roda em paralelo caso seja escolhida a opção 2
    #pragma omp parallel for if (ompSettings == "2")
    for (int i = Constantes::vMin; i <= Constantes::vMax; i++)
    {
      if (ompSettings == "1")
      {
        std::ostringstream nomeSaida;
        nomeSaida << i; //Dá cast para string

        //BFS
        if (Constantes::runBFS == true)
        {
          tInicio = clock();
          // cout << "Iniciando a BFS em lista com inicio no vertice " << i << endl;
          lista.BFS(i, (inputFile+"_BFS_ListaAdj_"+nomeSaida.str()).c_str(), Constantes::log);
          if (Constantes::log == true)
          {
            lista.geraEstatisticas((inputFile+"_BFS_"+nomeSaida.str()).c_str());
            executionTime << "Tempo para rodar a BFS a partir do vértice " << i << ": " << (clock() - tInicio)/(CLOCKS_PER_SEC/1000) << " ms" << endl;
          }
        }

        //DFS
        if (Constantes::runDFS == true)
        {
          tInicio = clock();
          // cout << "Iniciando a DFS em lista com inicio no vertice " << i << endl;
          lista.DFS(i, (inputFile+"_DFS_ListaAdj_"+nomeSaida.str()).c_str(), Constantes::log);
          if (Constantes::log == true)
          {
            lista.geraEstatisticas((inputFile+"_DFS_"+nomeSaida.str()).c_str());
            executionTime << "Tempo para rodar a DFS a partir do vértice " << i << ": " << (clock() - tInicio)/(CLOCKS_PER_SEC/1000) << " ms" << endl;
          }
        }
      }
      else
      {
        std::ostringstream nomeSaida;
        nomeSaida << i; //Dá cast para string

        //Inicializa uma matriz interno
        //TODO: Criar uma classe SÓ PARA A MATRIZ, para poder compartilhar
        Lista listaInt;
        listaInt.carregar(inputFile);

        //BFS
        if (Constantes::runBFS == true)
        {
          tInicio = clock();
          cout << "Iniciando a BFS em lista com inicio no vertice " << i << endl;
          listaInt.BFS(i, (inputFile+"_BFS_ListaAdj_"+nomeSaida.str()).c_str(), Constantes::log);
          if (Constantes::log == true)
          {
            listaInt.geraEstatisticas((inputFile+"_BFS_"+nomeSaida.str()).c_str());
            executionTime << "Tempo para rodar a BFS a partir do vértice " << i << ": " << (clock() - tInicio)/(CLOCKS_PER_SEC/1000) << " ms" << endl;
          }
        }

        //DFS
        if (Constantes::runDFS == true)
        {
          tInicio = clock();
          cout << "Iniciando a DFS em lista com inicio no vertice " << i << endl;
          listaInt.DFS(i, (inputFile+"_DFS_ListaAdj_"+nomeSaida.str()).c_str(), Constantes::log);
          if (Constantes::log == true)
          {
            listaInt.geraEstatisticas((inputFile+"_DFS_"+nomeSaida.str()).c_str());
            executionTime << "Tempo para rodar a DFS a partir do vértice " << i << ": " << (clock() - tInicio)/(CLOCKS_PER_SEC/1000) << " ms" << endl;
          }
        }
      }
    }
    executionTime.close(); //Finaliza o timer
  }

  openTime << "Tempo de execução: " << (clock() - tOpen)/(CLOCKS_PER_SEC/1000) << " ms" << endl;

  //Define se irá ser feito cálculo de componentes
  string calcularComponentes;
  if (Constantes::inOverride == true)
  {
    cout << "Deseja calcular a quantidade de componentes? Digite 1 para sim, e qualquer outra tecla para sair: ";
    cin >> calcularComponentes;
  }

  else
  {
    calcularComponentes = Constantes::componentesDefault;
  }

  //Caso inicie, inicia uma lista para calcular as componentes conexas
  if(calcularComponentes == "1")
  {
    Lista lista;
    lista.carregar(inputFile);
    lista.componentes(inputFile);
  }

  //Define se irá ser feito cálculo de diâmetro
  string calcularDiametro;
  if (Constantes::inOverride == true)
  {
    cout << "Deseja calcular o diâmetro? Digite 1 para sim, e qualquer outra tecla para sair: ";
    cin >> calcularDiametro;
  }

  else
  {
    calcularDiametro = Constantes::diametroDefault;
  }

  //Caso inicie, inicia uma lista para calcular as componentes conexas
  if(calcularDiametro == "1")
  {
    Lista lista;
    lista.carregar(inputFile);
    lista.diametro(inputFile);
  }
}
