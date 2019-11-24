#include <bits/stdc++.h>
#include <omp.h>
#include <time.h>
#include "Lista.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <algorithm>

//TODO:

using namespace std;

typedef pair<double, double> par;

Lista::bubbleSort(std::vector < vector < int> > &lista, int tamanho) //Ordena um vetor por bubblesort, começando por i = 1
{
  for (int i = 1; i <= tamanho-1; i++)
  {
    for (int j = 1; j <= tamanho-i-1; j++)
    {
      if (lista[j].size() < lista[j+1].size())
      {
         vector<int> aux = lista[j];
         lista[j] = lista[j+1];
         lista[j+1] = aux;
      }
    }
  }
}

Lista::carregar(std::string arquivo, bool pesos = false, bool direcionado = false, bool inverter = false)
{
  //Abre o arquivo
  string inputFile = arquivo+".txt";
  std::ifstream inFile(inputFile.c_str());

  //Caso consiga abrir o arquivo, preenche a Lista
  if (inFile.is_open())
  {
    //Carrega o numero de vertices
    string linha;
    getline(inFile, linha);
    //Dá cast para int...
    stringstream linhaInt(linha);
    nArestas = 0;
    linhaInt >> nVertices;
    vertMax = nVertices+1; //Índice para auxiliar loops e matrizes
    listaAdj.resize(vertMax); //Redimensiona a lista
    listaPesos.resize(vertMax);
    negativo = false;

    for (int i = 1; i <= nVertices; i++)
    {
      listaAdj[i].push_back(i); //Adiciona um vértice do elemento para ele mesmo. Pode ser útil no futuro, e evita bugs com índice 0
      listaPesos[i].push_back(i); //Adiciona um vértice do elemento para ele mesmo. Pode ser útil no futuro, e evita bugs com índice 0
    }

    //Inicializa a Lista e redimensiona os vértices
    // cout << "Carregando a Lista..." << endl;

    //Caso rode apenas uma thread com BFS, carrega na memória em várias threads
    //Preenche a Lista conforme o arquivo

    int v, a;
    if (!pesos)
    {
      while (inFile >> v >> a)
      {
        //Adiciona a aresta ao vetor
        if(v <= vertMax && a <= vertMax)
        {
          if (!inverter)
          {
            listaAdj[v].push_back(a);
          }
          else
          {
            listaAdj[a].push_back(v);
          }

          if (!direcionado)
          {
              listaAdj[a].push_back(v);
          }
          nArestas++;
        }
      }
    }
    else
    {
      double w;
      while (inFile >> v >> a >> w)
      {
        //Adiciona a aresta ao vetor
        if(v <= vertMax && a <= vertMax)
        {
          if (direcionado)
          {
            if (!inverter)
            {
              listaAdj[v].push_back(a);
              listaPesos[v].push_back(w);
            }
            else
            {
              listaAdj[a].push_back(v);
              listaPesos[a].push_back(w);
            }
          }
          else
          {
            listaAdj[a].push_back(v);
            listaPesos[a].push_back(w);
          }

          if (w < 0)
          {
            negativo = true;
          }
          nArestas++;
        }
      }
    }
    cout << listaAdj[1][1] << " " << listaPesos[1][1] << endl;
    // cout << "Lista carregada com sucesso!" << endl;
  }
  inFile.close();
}

Lista::BFS(int inicio, std::string outputName = "", bool log = false)
{
  std::vector <bool> explorados(vertMax, false);

  nivel.clear(); //Limpa a lista de níveis
  nivel.resize(vertMax); //Redimensiona a lista conforme necessário
  nivel[inicio] = 0; //Coloca o nível do vértice inicial como 0

  pai.clear(); //Limpa a lista de pais
  pai.resize(vertMax); //Redimensiona a lista conforme necessário
  pai[inicio] = inicio; //Coloca o pai do vértice inicial como ele mesmo

  std::list <int> fila; //Cria uma fila S
  fila.push_back(inicio); //Adiciona o vértice inicial à fila

  ofstream output;
  if(log)
  {
    output.open((outputName+".csv").c_str()); //Inicializa o arquivo
    output << "Vertice;Pai;Grau" << endl; //Adiciona o título
    output << inicio << ";;0" << endl; //Adiciona a origem
  }

  while (fila.size() != 0)
  {
    int v;
    v = fila.front(); //Pega o vértice atual
    fila.pop_front();  //Remove o vértice atual da fila

    explorados[v] = true;

    for (int i = 1; i <= listaAdj[v].size()-1; i++) //Varre o array de vértices
    {
      int w;
      w = listaAdj[v][i];

      if (!explorados[w])
      {
        explorados[w] = true;
        fila.push_back(w);
        nivel[w] = nivel[v] + 1; //O nível dele será o nível de quem descobiru ele +1
        pai[w] = v; //O pai dele será quem o descobriu

        if (log)
        {
          output << w << ";" << pai[w] << ";" << nivel[w] << endl; //Adiciona a linha no arquivo
        }
      }
    }
  }

  if (log)
  {
    output.close(); //Fecha o arquivo
  }
  // cout << "BFS executada com sucesso!" << endl;
}

Lista::DFS(int inicio, std::string outputName = "", bool log = false)
{
  std::vector <bool> explorados(vertMax, false); //Cria a lista de vértices explorados

  nivel.clear(); //Limpa a lista de níveis
  nivel.resize(vertMax); //Redimensiona a lista conforme necessário
  nivel[inicio] = 0; //Coloca o nível do vértice inicial como 0

  pai.clear(); //Limpa a lista de pais
  pai.resize(vertMax); //Redimensiona a lista conforme necessário
  pai[inicio] = inicio; //Coloca o pai do vértice inicial como ele mesmo

  std::list <int> fila; //Cria uma fila S
  fila.push_back(inicio); //Adiciona o vértice inicial à fila


  std::ostringstream inicioStr;
  inicioStr << inicio; //Dá cast para string.....

  ofstream output;
  if(log)
  {
    output.open((outputName+".csv").c_str()); //Inicializa o arquivo
    output << "Vertice;Pai;Grau" << endl; //Adiciona o título
    output << inicioStr << ";;0" << endl; //Adiciona a origem
  }

  while (fila.size() != 0)
  {
    int v;
    v = fila.back(); //Pega o vértice atual
    fila.pop_back();  //Remove o vértice atual da fila

    explorados[v] = true;
    for (int i = 0; i <= listaAdj[v].size()-1; i++) //Varre o array de vértices
    {
      int w;
      w = listaAdj[v][i];

      if (!explorados[w])
      {
        explorados[w] = true;
        fila.push_back(w);
        nivel[w] = nivel[v] + 1; //O nível dele será o nível de quem descobiru ele +1
        pai[w] = v; //O pai dele será quem o descobriu
        if (log)
        {
          output << w << ";" << pai[w] << ";" << nivel[w] << endl; //Adiciona a linha no arquivo
        }
      }
    }
  }
  if (log)
  {
    output.close(); //Fecha o arquivo
  }
  // cout << "DFS executada com sucesso!" << endl;

}

Lista::BFScomponentes(int inicio, std::vector<bool> &explorados, std::vector<int> &elementos)
{
  int aux = 0;

  std::list <int> fila; //Cria uma fila S
  fila.push_back(inicio); //Adiciona o vértice inicial à fila
  elementos.push_back(inicio); //Adiciona o vértice inicial à lista de componentes

  while (fila.size() != 0)
  {
    int v;
    v = fila.front(); //Pega o vértice atual
    fila.pop_front();  //Remove o vértice atual da fila
    explorados[v] = true;

    for (int i = 1; i <= listaAdj[v].size()-1; i++) //Varre o array de vértices
    {
      int w;
      w = listaAdj[v][i];
      if (!explorados[w])
      {
        explorados[w] = true;
        elementos.push_back(w); //Adiciona W na lsita de elementos da componente
        fila.push_back(w);
      }
    }
  }
  return aux;
}

int Lista::BFSdiametro(int inicio, std::vector<bool> explorados)
{
  int aux = 0;
  std::vector <int> nivelLight(vertMax, -1); //Cria uma lista de níveis interna

  std::list <int> fila; //Cria uma fila S
  fila.push_back(inicio); //Adiciona o vértice inicial à fila
  nivelLight[inicio] = 0;

  while (fila.size() != 0)
  {
    int v;
    v = fila.front(); //Pega o vértice atual
    fila.pop_front();  //Remove o vértice atual da fila
    explorados[v] = true;

    for (int i = 1; i <= listaAdj[v].size()-1; i++) //Varre o array de vértices
    {
      int w;
      w = listaAdj[v][i];
      // cout << w << endl;
      if (!explorados[w])
      {
        explorados[w] = true;
        fila.push_back(w);
        nivelLight[w] = nivelLight[v] + 1; //O nível dele será o nível de quem descobiru ele +1
        if (nivelLight[w] > aux) //Verifica se o nível novo é maior do que o atual máximo
        {
          aux = nivelLight[w];
        }
      }
    }
  }
  return aux;
}

Lista::geraEstatisticas(std::string fileName)
{
  ofstream output;
  output.open((fileName+".txt").c_str());

  //Retorna o número de vértices e arestas
  output << "Numero de vertices: " << nVertices <<endl;
  output << "Numero de arestas : " << nArestas <<endl;

  //Retorna os pais dos vértices pedidos
  output << "Pai do vertice 10: " << pai[10] << endl;
  output << "Pai do vertice 20: " << pai[20] << endl;
  output << "Pai do vertice 30: " << pai[30] << endl;

  int grauMin, grauMax;
  double grauMed, grauMediano;

  output.close();
}

Lista::componentes(std::string outputName)
{
  std::vector <bool> explorados(vertMax, false);
  std::vector < vector < int > > componentes;
  int nComponentes = 0;
  clock_t tInicio = clock();

  for (int i = 1; i < nVertices; i++)
  {
    if (!explorados[i])
    {
      if( listaAdj[i][0] == i )
      {
        std::vector<int> elementos;
        nComponentes++;
        if (listaAdj[i].size() == 1)
        {
          elementos.push_back(i);
        }
        else
        {
          BFScomponentes(i, explorados, elementos);
        }
        componentes.push_back(elementos);
      }
    }
  }

  clock_t tFinal = clock();
  tFinal =  (clock() - tInicio)/(CLOCKS_PER_SEC/1000);

  ofstream outputComponentes;
  outputComponentes.open((outputName+"_componentes.txt").c_str());


  outputComponentes << "Numero de componentes: " << nComponentes << endl;
  outputComponentes << "Tempo de execucao: " << tFinal << " ms" << endl;

  // Calcula a ordem dos elementos
  bubbleSort(componentes, nComponentes);

  // Imprime os elementos no arquivo de saída
  for (int i = 1; i <= nComponentes; i++)
  {
    outputComponentes << "N de elementos: " << componentes[i-1].size() << ". Elementos: ";
    for (int j = 0; j <= componentes[i-1].size()-1; j++)
    {
      outputComponentes << componentes[i-1][j] << " ";
    }
    outputComponentes << endl;
  }
  outputComponentes.close();
  grauCalc(outputName);
}

Lista::grauCalc(std::string outputName)
{
 //Cálculo de grau
 ofstream outputGraus;
 outputGraus.open((outputName+"_graus.txt").c_str());

 //Calcula o grau máximo e a média
 int grauMin, grauMax;
 double grauMed, grauMediano;
 std::vector <int> arrayGrau;

 grauMax = 0;
 grauMed = 0;
 for (int i = 1; i <= nVertices; i++)
 {
   arrayGrau.push_back(listaAdj[i].size()-1);
   grauMed = grauMed + listaAdj[i].size() - 1;
   if ((listaAdj[i].size() - 1) > grauMax) //Se o vértice i tiver grau maior do que grauMax, atualiza
   {
     grauMax = listaAdj[i].size() - 1;
   }
 }
 grauMed = grauMed / nVertices; //Divide a soma total dos graus pelo número de vértices para calcular a média

 //Calcula o grau mínimo
 grauMin = grauMax; //Coloca o grau mínimo igual ao máximo
 for (int i = 1; i <= vertMax; i++)
 {
   if ((listaAdj[i].size()-1) < grauMin) //Se o vértice i tiver grau menor do que grauMin e não for a origem, atualiza
   {
     grauMin = listaAdj[i].size() - 1;
   }
 }

 //Calcula a mediana
 sort(arrayGrau.begin(), arrayGrau.end());
 if (arrayGrau.size() % 2)
 {
   grauMediano = (arrayGrau[nVertices/2-1] + arrayGrau[nVertices/2]) / 2;
 }
 else
 {
   grauMediano = arrayGrau[nVertices/2];
 }

 outputGraus << "Grau minimo: " << grauMin << endl;
 outputGraus << "Grau maximo: " << grauMax << endl;
 outputGraus << "Grau Medio : " << grauMed << endl;
 outputGraus << "Mediana    : " << grauMediano << endl;
}

Lista::diametro(string outputName)
{
  //Cria um arquivo de saída
  ofstream outputDiametro;
  outputDiametro.open((outputName+"_diametro.txt").c_str());

  clock_t tInicio = clock();
  clock_t tFinal = clock();

  int diametro = 0;
  int verticesAnalisados = 0;
  std::vector<int> auxGraus(vertMax, 0); //Cria um vetor para armazenar os gruas máximos inicializando em cada vértice
  std::vector<int> elementos;


  #pragma omp parallel for
  for(int i = 1; i <= nVertices; i++)
  {
    if ( (tFinal - tInicio)/(CLOCKS_PER_SEC) > 1800)
    {
      verticesAnalisados = i;
      i = nVertices;
    }
    std::vector <bool> explorados(vertMax, false);  //Coloca todos os vértices como não explorados
    auxGraus[i] = BFSdiametro(i, explorados); //Calcula a BFS a partir de cada vértice

    tFinal = clock();
  }

  //For utilizado para calcular o maior valor. Poderia colocar dentro do for anterior, mas assim não perde tempo sincronizando as threads
  for (int i = 1; i <= nVertices; i++)
  {

    if (auxGraus[i] > diametro)
    {
        diametro = auxGraus[i];
    }
  }
  outputDiametro << "Vertices Analisados: " << verticesAnalisados << "/" << nVertices << endl;
  outputDiametro << "Diametro do grafo: " << diametro << endl;
  outputDiametro << "Tempo de execucao: " << (tFinal - tInicio)/(CLOCKS_PER_SEC/1000) << " ms" << endl;
  outputDiametro.close();
}

Lista::DijkstraPrim(int inicio, bool mst = false)
{

  std::vector <bool> explorados(vertMax, false);
  std::vector <double> distancia(vertMax, 99999999);

  distancia[inicio] = 0;
  pai.clear(); //Limpa a lista de pais
  pai.resize(vertMax); //Redimensiona a lista conforme necessário
  pai[inicio] = inicio; //Coloca o pai do vértice inicial como ele mesmo

  distOrigem.resize(vertMax); //Redimensiona a lista conforme necessário

  priority_queue< par, vector <par> , greater<par> > fila;

  fila.push(make_pair(distancia[inicio], inicio));

  while (!fila.empty())
  {
    int u;
    u = fila.top().second; //Pega o vértice atual
    fila.pop();  //Remove o vértice atual da fila

    explorados[u] = true;
    distOrigem[u] = distancia[u];

    for (int i = 1; i <= listaAdj[u].size()-1; i++) //Varre o array de vértices
    {

      int v;
      double pesoUV;
      v = listaAdj[u][i];
      pesoUV = listaPesos[u][i];

      if (!explorados[v])
      {
        if (!mst)
        //Dijkstra
        {
          if(distancia[v] > (distancia[u] + pesoUV))
          {
            distancia[v] = distancia[u] + pesoUV;
            fila.push(make_pair(distancia[v], v));
            pai[v] = u;
            // cout << u << " " << listaAdj[u][i] << " " << distancia[v] << endl; //Debug
          }
        }
        else
        //Prim
        {
          if(distancia[v] > pesoUV)
          {
            distancia[v] = pesoUV;
            fila.push(make_pair(distancia[v], v));
            pai[v] = u;
            // cout << u << " " << listaAdj[u][i] << " " << listaPesos[u][i] << " " << distancia[v] << endl; //Debug
          }
        }
      }
    }
  }
}

Lista::excentricidade()
{
  double distMax = 0;
  for(int i= 1; i <= nVertices; i++)
  {
    if (distOrigem[i] > distMax)
    {
      distMax = distOrigem[i];
    }
  }
  cout << distMax << endl;
}

Lista::minimumSpanningTree()
{
  ofstream output;
  output.open("runlog.txt");

  int peso = 0;
  for (int i = 1; i <= nVertices; i++)
  {
    output << pai[i] << " " << i << " " << distOrigem[i] << endl;
    peso = peso + distOrigem[i];
  }
  output.close();
  cout << peso << endl;;
}

Lista::maiorGrau(int quant)
{
  std::vector <int> grau(vertMax, 0);

  for (int i = 1; i <= nVertices; i++)
  {
    grau[pai[i]]++;
    grau[i]++;
  }

  for (int i = 1; i <= quant+1; i++)
  {
    int max = *std::max_element(grau.begin(), grau.end());
    int temp = 0;
    int it = 0;
    while (temp != max)
    {
      temp = grau[it];
      it++;
    }
    cout << it-1 << " " << grau[it-1] << endl;
    grau[it-1] = 0;
  }
}

Lista::vizinhos(int vert)
{
  cout << pai[vert] << endl;
  for(int i = 1; i <= nVertices; i++)
  {
    if(pai[i] == vert)
    {
      cout << i << endl;
    }
  }
}

Lista::caminhos(int inicio, int fim)
{
  cout << inicio << ": " << distOrigem[inicio] << " / Caminho: ";
  int v = inicio;
  while (v != fim)
  {
    cout << v << ";";
    v = pai[v];
  }
  cout << fim << endl;
}

Lista::caminhosColaboradores()
{
  int v = 11365;
  cout << "Alan M. Turing: " << distOrigem[v] << " / Caminho: ";
  if (distOrigem[v] != 0)
  {
    while (v != 2722)
    {
      cout << v << ";";
      v = pai[v];
    }
    cout << "Edsger W. Dijkstra";
  }
  cout << endl;


  v = 471365;
  cout << "J. B. Kruskal: " << distOrigem[v] << " / Caminho: ";
  while (v != 2722)
  {
    cout << v << ";";
    v = pai[v];
  }
  cout << "Edsger W. Dijkstra" << endl;


  v = 5709;
  cout << "Jon M. Kleinberg: " << distOrigem[v] << " / Caminho: ";
  while (v != 2722)
  {
    cout << v << ";";
    v = pai[v];
  }
  cout << "Edsger W. Dijkstra" << endl;


  v = 11386;
  cout << "Eva Tardos: " << distOrigem[v] << " / Caminho: ";
  while (v != 2722)
  {
    cout << v << ";";
    v = pai[v];
  }
  cout << "Edsger W. Dijkstra" << endl;


  v = 343930;
  cout << "Daniel R. Figueiredo: " << distOrigem[v] << " / Caminho: ";
  while (v != 2722)
  {
    cout << v << ";";
    v = pai[v];
  }
  cout << "Edsger W. Dijkstra" << endl;

}

bool Lista::bipartidoComponente(int inicio, std::vector<bool> &explorados)
{
  std::list <int> fila; //Cria uma fila S
  fila.push_back(inicio); //Adiciona o vértice inicial à fila
  cor[inicio] = 1;

  while (fila.size() != 0)
  {
    int v;
    v = fila.front(); //Pega o vértice atual
    fila.pop_front();  //Remove o vértice atual da fila

    explorados[v] = true;

    for (int i = 1; i <= listaAdj[v].size()-1; i++) //Varre o array de vértices
    {
      int w;
      w = listaAdj[v][i];

      if (!explorados[w])
      {
        cor[w] = 1-cor[v];
        explorados[w] = true;
        fila.push_back(w);
      } else {
        if (cor[w] == cor[v])
        {
          return false;
        }
      }
    }
  }
   return true;
}

bool Lista::bipartido()
{
  cor.resize(vertMax, -1);
  std::vector <bool> explorados(vertMax, false);
  for (int i = 1; i < nVertices; i++)
  {
    if (!explorados[i])
    {
      if(!bipartidoComponente(i, explorados))
      {
        return false;
      };
    }
  }
  return true;
}

Lista::BFSpair(std::vector <int> &parU, std::vector <int> &parV)
{
  std::list <int> fila; //Cria uma fila S

  for (int u = 1; u <= nVertices; u++)
  {
    if (parU[u] == 0) //Caso o vértice U seja exposto, adiciona à fila
    {
      nivel[u] = 0;
      fila.push_back(u);
    } else  //Caso contrário, marca a distância como "infinito"
    {
      nivel[u] = 100000;
    }
  }

  nivel[0] = 100000;
  while (fila.size() != 0)
  {
    int u;
    u = fila.front(); //Pega o vértice atual
    fila.pop_front();  //Remove o vértice atual da fila

    if(nivel[u] < nivel[0])
    {
      for (int i = 1; i <= listaAdj[u].size()-1; i++) //Varre os vizinhos do vértice
      {
        int v = listaAdj[u][i];
        nivel[parV[v]] = nivel[u] + 1;
        if(parV[v] == 0) //Caso ele seja exposto (ou seja, está pareado com o 0), encontrou um caminho aumentante
        {
          // nivel[0] = nivel[u] + 1;
          return true;
        }
        if (nivel[parV[v]] == 100000) //Caso esteja emparelhado, verifica se o par já foi adicionado à fila
        {
          fila.push_back(parV[v]); //Caso não tenha sido, será adicionado nesse momento
        }
      }
    }
  }
  return false; //Se chegar aqui não encontrou caminho aumentante, logo, convergiu
}

Lista::DFSpair(int u, std::vector <int> &parU, std::vector <int> &parV)
{
  if (u != 0)
  {
    for (int i = 1; i <= listaAdj[u].size()-1; i++) //Varre os vizinhos do vértice
    {
      int v = listaAdj[u][i];
      if(nivel[parV[v]] == nivel[u] + 1)
      {
        if(DFSpair(parV[v], parU, parV))
        {
          parV[v] = u;
          parU[u] = v;
          return true;
        }
      }
    }
    nivel[u] = 100000;
    return false;
  }
  return true;
}

Lista::emparelhamento(std::string outputName = "temp")
{
  std::vector <int> parU(vertMax, -1); //Vértices do lado esquerdo
  std::vector <int> parV(vertMax, -1); //Vértices do lado direito
  for (int i = 1; i <= nVertices; i++)
  {
    if (cor[i] == 0)
    {
      parU[i] = 0;
    } else
      parV[i] = 0;
  }

  int n = 0;
  nivel.clear(); //Limpa a lista de níveis
  nivel.resize(vertMax); //Redimensiona a lista conforme necessário

  clock_t tInicio = clock();
  while (BFSpair(parU, parV))
  {
    n++;
    // cout << n << endl;

    for(int u = 1; u <= nVertices; u++)
    {
      if(parU[u] == 0)
      {
        DFSpair(u, parU, parV);
      }
    }
  }
  clock_t tFinal = clock();
  tFinal =  (clock() - tInicio)/(CLOCKS_PER_SEC/1000);

  cout << "Tempo decorrido: " << tFinal << " ms" << endl;

  ofstream output;
  output.open((outputName+"_result.txt").c_str());
  int emparelhamentoMaximo = 0;
  for (int i = 1; i <= nVertices; i++)
  {
    if(cor[i] == 0)
    {
      emparelhamentoMaximo++;
      output << parU[i] << " " << i << endl; //Adiciona o título
    }
  }
  output.close();
  cout << "Emparelhamento: " << emparelhamentoMaximo << endl;
}

Lista::BellmanFord(int inicio, std::string outputName = "temp")
{
  distOrigem.resize(vertMax); //Redimensiona a lista conforme necessário
  distOrigem.clear(); //Limpa a lista de níveis
  distOrigem.resize(vertMax); //Redimensiona a lista conforme necessário
  pai.clear(); //Limpa a lista de pais
  pai.resize(vertMax); //Redimensiona a lista conforme necessário
  pai[inicio] = inicio; //Coloca o pai do vértice inicial como ele mesmo

  clock_t tInicio = clock();

  for (int i = 1; i <= nVertices; i++)
  {
    distOrigem[i] = 10000000;  //Define todas as distâncias como "infinito"
  }
  distOrigem[inicio] = 0; //Coloca o nível do vértice inicial como 0

  for (int i = 1; i <= nVertices+1; i++)
  {
    bool continuar = false;
    for (int v = 1; v <= nVertices; v++)
    {
      for (int j = 1; j <= listaAdj[v].size()-1; j++) //Varre o array de vértices
      {
        int w = listaAdj[v][j];

        double distV = distOrigem[v];
        double distW = distOrigem[w] + listaPesos[v][j];
        if (distW < distV)
        {
          pai[v] = w;
          distOrigem[v] = distW;
          continuar = true;
        }
      }
    }
    if (!continuar)
    {
      clock_t tFinal = clock();
      tFinal =  (clock() - tInicio)/(CLOCKS_PER_SEC/1000);
      cout << "Convergiu em " << tInicio << " ms" <<  endl;

      ofstream output;
      output.open((outputName+"_resultBF.txt").c_str());

      for (int i = 1; i <= nVertices; i++)
      {

        output << i << "-" << pai[i] << " Dist: " << distOrigem[i] << endl;
      }
      output.close();
      return true;
    }
    if ((i == nVertices+1) && continuar)
    {
      cout << "Ciclo negativo!!" << endl;
      return false;
    }
  }

}

Lista::FloydWarshall(std::string outputName = "temp")
{
  std::vector <std::vector<double> > distancias;
  distancias.resize(nVertices+1);

  clock_t tInicio = clock();

  //Inicializa a matriz
  for(int i = 0; i <= nVertices; i++)
  {

    distancias[i].resize(nVertices+1);
    for (int j = 1; j <= nVertices; j++)
    {
      distancias[i][j] = 10000000;
    }
    distancias[0][i] = i;
    distancias[i][i] = 0;
    if (i > 0)
    {
      for (int j = 1; j <= listaAdj[i].size()-1; j++)
      {
        int v = listaAdj[i][j];
        distancias[i][v] = listaPesos[i][j];
      }
    }
  }
  //Algoritmo de Floyd-Warshall

  for(int i = 1; i <= nVertices; i++)
  {
    // bool continuar = false;
    for (int j = 1; j <= nVertices; j++)
    {
      for (int k = 1; k <= nVertices; k++)
      {
        if(distancias[j][k] > (distancias[j][i] + distancias[i][k]))
        {
          distancias[j][k] = (distancias[j][i] + distancias[i][k]);
          // continuar = true;
        }
      }
    }
    // if (!continuar)
    // {
    //   i = nVertices;
    // }
  }

  clock_t tFinal = clock();
  tFinal =  (clock() - tInicio)/(CLOCKS_PER_SEC/1000);
  cout << "Convergiu em " << tInicio << " ms" <<  endl;

  //Exporta a matriz
  ofstream output;
  output.open((outputName+"_resultFW.txt").c_str());
  for (int i = 0; i <= nVertices; i++)
  {
    output << i;
    for (int j = 1; j <= nVertices; j++)
    {
      output << " " << distancias[i][j];
    }
    output << endl;
  }
}

Lista::Pesos(std::string outputName = "temp", int inicio = 0, bool mst = false)
{
  if (inicio == 0)
  {
    cout << "Rodando Floyd-Warshall..." << endl;
    FloydWarshall(outputName);
  }
  else
  {
    if (negativo)
    {
      cout << "Rodando Bellman-Ford..." << endl;
      BellmanFord(inicio, outputName);
    }
    else
    {
      cout << "Rodando Dijkstra/Prim..." << endl;
      DijkstraPrim(inicio, mst);
    }
  }
}
