// grafos-aula-1.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

struct Adjacency {
    int originVertex;
    int destinationVertex;
};

static void addAdjacency(vector<Adjacency>& adjacencies, int origin, int destination) {
    Adjacency adj = {};
    adj.originVertex = origin;
    adj.destinationVertex = destination;
    adjacencies.push_back(adj);
}


static void setAdjacencyMatrix(int** m, int vertexCount, vector<Adjacency> adjacencies) {
    for (int i = 0; i < vertexCount; i++)
        m[i] = new int[vertexCount];

    for (int i = 0; i < vertexCount; i++)
        for (int j = 0; j < vertexCount; j++)
            m[i][j] = 0;

    for (Adjacency adj : adjacencies) {

        int originVertex = adj.originVertex - 1;
        int destinationVertex = adj.destinationVertex - 1;

        m[originVertex][destinationVertex] = 1;
    }
}

static void cleanAdjacencyMatrix(int** m, int vertexCount) {
    for (int i = 0; i < vertexCount; i++)
        delete m[i];

    delete m;
}

static void showAdjacencyMatrix(int** m, int vertexCount) {
    cout << "Matriz de adjacencia:" << endl;
    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
}

static void showAdjacencyList(vector<Adjacency> adjacencies) {
    cout << "Lista de adjacencia:" << endl;
    for (Adjacency adj : adjacencies) {
        cout << "{ " << adj.originVertex << ", " << adj.destinationVertex << " }" << endl;
    }
    cout << endl;
}

static void dfs(int firstVertex, int vertexCount, int** m) {
    const int n = vertexCount;
    stack<int> stack;
    vector<int> visitados;

    for (int i = 0; i < n; i++) {
        visitados.push_back(0);
    }

    int primeiroVertice = firstVertex;
    stack.push(primeiroVertice);
    cout << "Ordem de visitacao de vertices utilizando Depth First Search" << endl;

    int verticeAtual;

    while (!stack.empty()) {
        verticeAtual = stack.top();
        if ((visitados.at(verticeAtual) == 0)) {
            cout << verticeAtual + 1 << endl;
            visitados[verticeAtual] = 1; // marked as visited
        }

        for (int i = 0; i < n; i++) {// find first adjacent edge
            if (m[verticeAtual][i] == 1 && (visitados.at(i) == 0)) {
                stack.push(i);
                break;
            }
            else if (i == n - 1) {
                stack.pop();
            }
        }
    }

    cout << endl;
}

static void bfs(int firstVertex, int vertexCount, int** m) {
    int n = vertexCount;
    queue<int> queue;
    vector<int> visitados;

    for (int i = 0; i < n; i++) {
        visitados.push_back(0);
    }

    queue.push(firstVertex);
    int verticeAtual;

    cout << "Ordem de visitacao de vertices utilizando BFS - Amplitude" << endl;

    while (!queue.empty()) {
        verticeAtual = queue.front();
        queue.pop();
        if ((visitados.at(verticeAtual) == 0)) {
            cout << verticeAtual + 1 << endl;
            visitados[verticeAtual] = 1; // marked as visited
        }

        for (int i = 0; i < n; i++) {// find first adjacent edge
            if (m[verticeAtual][i] == 1 && (visitados.at(i) == 0)) {
                queue.push(i);
            }
        }
    }
}


static bool vertexExists(vector<Adjacency> adjacencies, int vertexToInsert) {
    bool exists = false;
    for (Adjacency adj : adjacencies) {
        if (adj.originVertex == vertexToInsert || adj.destinationVertex == vertexToInsert) {
            exists = true;
            break;
        }
    }

    return exists;
}

int main()
{

    int presentationBalancer = 0;

    //MENU #1 - inserção inicial do grafo
    int vertexCount;
    cout << "Informe a quantidade de vertices" << endl;
    cin >> vertexCount;
    vector<Adjacency> adjacencies;
    char option;
    for (int i = 0; i < vertexCount; i++) {
        bool stop = false;

        while (!stop) {
            cout << "Escolha uma opcao:" << endl;
            cout << "a - Adicionar adjacencia ao vertice " << i + 1 << ": " << endl;

            if (i < vertexCount - 1) cout << "b - Ir para o proximo vertice (" << i + 2 << ") : " << endl;
            if (i == vertexCount - 1) cout << "b - finalizar" << endl;

            cin >> option;

            if (option == 'a') {
                int input;
                cout << "Informe a adjacencia ao vertice " << i + 1 << ":" << endl;
                cin >> input;

                addAdjacency(adjacencies, i + 1, input);

                cout << "adjacencia adicionada com sucesso!" << endl;
            }

            if (option == 'b') {
                stop = true;
            }
        }
    }
    // MENU #1 END

    int** m = new int* [vertexCount];
    setAdjacencyMatrix(m, vertexCount, adjacencies);

    showAdjacencyList(adjacencies);
    showAdjacencyMatrix(m, vertexCount);

    // MAIN LOOP 
    bool stop = false;

    while (!stop) {
        cout << "Selecione uma das opcoes: " << endl;
        cout << "a - DFS - Depth First Search" << endl;
        cout << "b - BFF - Amplitude" << endl;
        cout << "c - Incluir vertice" << endl;
        cout << "d - Excluir vertice" << endl;
        cout << "e - Adicionar aresta/arco" << endl;
        cout << "f - Excluir aresta/arco" << endl;
        cout << "g - Mostrar matriz e lista de adjacencia" << endl;
        cout << "h - Sair" << endl;

        cin >> option;

        char subOption;
        int initialVertex;

        if (option == 'a') { // DFS - Depth First Search
            cout << "a - buscar por vertice especifico" << endl;
            cout << "b - percorrer todo o grafo" << endl;
            cout << "c - Voltar" << endl;
            cin >> subOption;

            if (subOption == 'b') {
                cout << "Informe o vertice inicial da busca: " << endl;
                cin >> initialVertex;
                dfs(initialVertex - 1, vertexCount, m);
            }

        }
        if (option == 'b') { //BFS - Amplitude
            cout << "a - buscar por vertice especifico" << endl;
            cout << "b - percorrer todo o grafo" << endl;
            cout << "c - Voltar" << endl;
            cin >> subOption;

            if (subOption == 'b') {
                cout << "Informe o vertice inicial da busca: " << endl;
                cin >> initialVertex;
                bfs(initialVertex - 1, vertexCount, m);
            }
        }
        if (option == 'c') {// add vertexes

            int vertexToAdd = vertexCount + 1;

            cout << "Para adicionar o vertice  " << vertexToAdd << " informe suas adjacencias " << endl;
            bool optionCstop = false;
            int adjacencyToAdd;
            bool firstIteration = true;
            while (!optionCstop) {
                cout << "Informe uma adjacencia do vertice " << vertexToAdd << " ( pressione 0 para voltar )" << endl;
                cin >> adjacencyToAdd;

                if (adjacencyToAdd == 0) optionCstop = true;
                else {
                    if (firstIteration) {
                        vertexCount++;
                        firstIteration = false;
                    }
                    addAdjacency(adjacencies, vertexCount, adjacencyToAdd);
                    //cleanAdjacencyMatrix(m, vertexCount);
                    setAdjacencyMatrix(m, vertexCount, adjacencies);

                    cout << "Adjacencia adicionada com sucesso!" << endl;
                }

            }


        }
        if (option == 'd') { // excluir vertice
            int input;
            cout << "Informe o vertice que deseja excluir ou pressione 0 para voltar: " << endl;
            cin >> input;


            if (input > vertexCount || input < 0) {
                cout << "Vertice invalido!" << endl;
            }
            else if (input != 0) {

                bool stop = false;
                int positionToDelete;
                int index = 0;

                while (!stop) {


                    for (Adjacency adj : adjacencies) {
                        if (adj.originVertex == input || adj.destinationVertex == input) {
                            positionToDelete = index;
                            index++;
                            break;
                        }

                        if (index == adjacencies.size() - 1) {
                            stop = true;
                            positionToDelete = 0;
                        }

                        index++;
                    }


                    if (!stop) {
                        adjacencies.erase(adjacencies.begin() + positionToDelete);


                        //IF IT WAS THE LAST ONE OF THAT VERTEX NUMBER, THEN IT NECESSARY TO DECREASE THE VERTEX COUNT
                        bool found = false;
                        for (Adjacency adj : adjacencies) {
                            if (adj.originVertex == input || adj.destinationVertex == input) {
                                found = true;
                                break;
                            }
                        }

                        if (!found) {
                            vertexCount--;
                        }

                        //cleanAdjacencyMatrix(m, vertexCount);
                        setAdjacencyMatrix(m, vertexCount, adjacencies);

                    }


                    index = 0;
                }

            }


        }
        if (option == 'e') {
            int originVertex, destinationVertex;
            cout << "Informe o vertice de origem: " << endl;
            cin >> originVertex;
            cout << "Informe o vertice de destino: " << endl;
            cin >> destinationVertex;

            addAdjacency(adjacencies, originVertex, destinationVertex);
            setAdjacencyMatrix(m, vertexCount, adjacencies);
        }
        if (option == 'f') {
            int originVertex, destinationVertex;
            cout << "Informe o vertice de origem: " << endl;
            cin >> originVertex;
            cout << "Informe o vertice de destino: " << endl;
            cin >> destinationVertex;


            int indexToDelete = 0;
            int index = 0;
            for (Adjacency adj : adjacencies) {
                if (adj.originVertex == originVertex && adj.destinationVertex == destinationVertex) {
                    indexToDelete = index;
                    break;
                }
                index++;
            }

            adjacencies.erase(adjacencies.begin() + indexToDelete);

            if (!vertexExists(adjacencies, originVertex)) vertexCount--;
            if (!vertexExists(adjacencies, destinationVertex)) vertexCount--;

            setAdjacencyMatrix(m, vertexCount, adjacencies);

        }
        if (option == 'g') {
            showAdjacencyMatrix(m, vertexCount);
            showAdjacencyList(adjacencies);
        }
        if (option == 'h') stop = true;

    }

    // MAIN LOOP END


    const int n = 6; //quantidade de vertices
    const int linhas = 11;
    const int colunas = 2; // a quantidade de colunas é sempre 2


    // a, b, c, d, e, f, g, h, i
    // 1, 2, 3, 4, 5, 6, 7, 8, 9


    ;
    //primeiro exemplo
   /*
 int listaAdjacencia[linhas][colunas] = {
       {1,2},
       {1,4},
       {1,6},
       {1,9},
       {2,1},
       {2,3},
       {2,4},
       {2,5},
       {3,2},
       {3,4},
       {3,5},
       {3,6},
       {4,1},
       {4,2},
       {4,3},
       {5,2},
       {5,3},
       {5,6},
       {6,1},
       {6,3},
       {6,5},
    };    */


    // segundo exemplo
    int listaAdjacencia[linhas][colunas] = {
      {1,2},
      {1,6},
      {2,3},
      {2,4},
      {3,5},
      {3,6},
      {4,1},
      {4,3},
      {5,2},
      {5,6},
      {6,5},
    };


    int matriz[n][n] = {};

    for (int i = 0; i < linhas; i++) {

        int verticeOrigem = listaAdjacencia[i][0] - 1;
        int verticeDestino = listaAdjacencia[i][1] - 1;

        matriz[verticeOrigem][verticeDestino] = 1;

    }


    cout << "Matriz de adjacencia:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;



    //DFS - Depth First Search
    stack<int> stack;
    vector<int> visitados;

    for (int i = 0; i < n; i++) {
        visitados.push_back(0);
    }

    int primeiroVertice = 0;
    stack.push(primeiroVertice);
    cout << "Ordem de visitacao de vertices utilizando Depth First Search" << endl;

    int verticeAtual;

    while (!stack.empty()) {
        verticeAtual = stack.top();
        if ((visitados.at(verticeAtual) == 0)) {
            cout << verticeAtual + 1 << endl;
            visitados[verticeAtual] = 1; // marked as visited
        }

        for (int i = 0; i < n; i++) {// find first adjacent edge
            if (matriz[verticeAtual][i] == 1 && (visitados.at(i) == 0)) {
                stack.push(i);
                break;
            }
            else if (i == n - 1) {
                stack.pop();
            }
        }
    }


    //BFS - Amplitude
    queue<int> queue;
    vector<int> visitados2;

    for (int i = 0; i < n; i++) {
        visitados2.push_back(0);
    }

    queue.push(primeiroVertice);
    int verticeAtual2;

    cout << "Ordem de visitacao de vertices utilizando BFS - Amplitude" << endl;

    while (!queue.empty()) {
        verticeAtual2 = queue.front();
        queue.pop();
        if ((visitados2.at(verticeAtual2) == 0)) {
            cout << verticeAtual2 + 1 << endl;
            visitados2[verticeAtual2] = 1; // marked as visited
        }

        for (int i = 0; i < n; i++) {// find first adjacent edge
            if (matriz[verticeAtual2][i] == 1 && (visitados2.at(i) == 0)) {
                queue.push(i);
            }
        }
    }


    cleanAdjacencyMatrix(m, vertexCount);

}






// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
