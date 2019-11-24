#ifndef LISTA_H
#define LISTA_H
#include <iostream>
#include <string>
#include <vector>



class Lista
{
  public:
    carregar(std::string arquivo, bool pesos, bool direcionado, bool inverter);
    caminho(int in);
    excentricidade();
    minimumSpanningTree();
    maiorGrau(int quant);
    vizinhos(int vert);
    BFS(int inicio, std::string outputName, bool log);
    DFS(int inicio, std::string outputName, bool log);
    Pesos(int inicio, bool logFile, bool mst);
    int BFSdiametro(int inicio, std::vector<bool> explorados);
    geraEstatisticas(std::string fileName);
    componentes(std::string outputName);
    diametro(std::string inputFile);
    grauCalc(std::string outputName);
    caminhos(int inicio, int fim);
    caminhosColaboradores();
    bool negativo;
    bool bipartido();
    BFSpair(std::vector <int> &parU, std::vector <int> &parV);
    DFSpair(int u, std::vector <int> &parU, std::vector <int> &parV);
    emparelhamento(std::string outputName);
    BellmanFord(int inicio, std::string outputName);
    FloydWarshall(std::string);
  protected:

  private:
    BFScomponentes(int inicio, std::vector<bool> &explorados, std::vector<int> &elementos);
    bool bipartidoComponente(int inicio, std::vector<bool> &explorados);
    bubbleSort(std::vector < vector < int> > &lista, int tamanho); //Bubble Sort
    std::vector <int> elemComponentes; //Elementos (vértices) pertencentes às componentes
    int nVertices; //Núero de vértices
    int vertMax;   //Índice do maior vértice. Será nVertices+1, utilizado para auxiliar loops
    int nArestas; //Número de arestas
    std::vector < std::vector<int> > listaAdj; //Usado para representar a lista.
    std::vector < std::vector<double> > listaPesos; //Usado para representar os pesos.
    std::vector <double> distOrigem; //Lista da distância até a origem
    std::vector <int> grau; //Lista de níveis
    std::vector <int> nivel; //Lista de níveis
    std::vector <int> pai; //Lista de pais
    std::string inputFile; //Nome do arquivo de entrada
    std::vector <int> cor; //Lista de cores
};

#endif // LISTA_H
