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
    cout << "Lista atual de adjacencia:" << endl;
    for (Adjacency adj : adjacencies) {
        cout << "{ " << adj.originVertex << ", " << adj.destinationVertex << " }" << endl;
    }
    //cout << endl;
}

static void dfs(int firstVertex, int vertexCount, int** m, int vertexToFind = -1) {
    const int n = vertexCount;
    stack<int> stack;
    vector<int> visitados;

    for (int i = 0; i < n; i++) {
        visitados.push_back(0);
    }

    int primeiroVertice = firstVertex;
    stack.push(primeiroVertice);
    cout << endl;
    cout << "Ordem de visitacao de vertices utilizando Depth First Search" << endl;

    int verticeAtual;

    while (!stack.empty()) {
        verticeAtual = stack.top();
        
        if ((visitados.at(verticeAtual) == 0)) {
            cout << verticeAtual + 1 << endl;
            visitados[verticeAtual] = 1; // marked as visited

            if (vertexToFind != -1 && (verticeAtual + 1) == vertexToFind) {
                cout << "Vertice " << vertexToFind << " encontrado." << endl;
                break;
            }
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

        if (stack.empty()) {
            for (int i = 0; i < visitados.size(); i++) {
                if (visitados.at(i) == 0) {
                    stack.push(i);
                    break;
                }

            }
        }
    }

    cout << endl;
}

static void bfs(int firstVertex, int vertexCount, int** m, int vertexToFind = -1) {
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

            if (vertexToFind != -1 && (verticeAtual + 1) == vertexToFind) {
                cout << "Vertice " << vertexToFind << " encontrado." << endl;
                cout << endl;
                break;
            }
        }

        for (int i = 0; i < n; i++) {
            if (m[verticeAtual][i] == 1 && (visitados.at(i) == 0)) {
                queue.push(i);
            }
        }

        if (queue.empty()) {
            for (int i = 0; i < visitados.size(); i++) {
                if (visitados.at(i) == 0) {
                    queue.push(i);
                    break;
                }
          
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
    //MENU #1 - inserção inicial do grafo
    int vertexCount;
    cout << "Informe a quantidade de vertices" << endl;
    cin >> vertexCount;
    vector<Adjacency> adjacencies;
    char option;
    int currentVertex;
    for (int i = 0; i < vertexCount; i++) {
        bool stop = false;
        currentVertex = i + 1;

        while (!stop) {
            cout << endl;
            cout << "Vertice atual: " << currentVertex << endl;
            cout << "Escolha uma opcao: " << endl;
            cout << "a - Adicionar adjacencia ao vertice " << currentVertex << ": " << endl;

            if (i < vertexCount - 1) cout << "b - Ir para o proximo vertice (" << currentVertex + 1 << ") : " << endl;
            if (i == vertexCount - 1) cout << "b - finalizar" << endl;

            cin >> option;

            if (option == 'a') {
                int input;
                cout << endl;
                cout << "Informe uma adjacencia para o vertice " << currentVertex << ":" << endl;
                cin >> input;

                addAdjacency(adjacencies, currentVertex, input);

                cout << endl;
                cout << "Adjacencia adicionada com sucesso!" << endl;
                showAdjacencyList(adjacencies);
            }

            if (option == 'b') {
                stop = true;

                if (i == vertexCount - 1) {
                    cout << endl;
                    cout << "Grafo inserido com sucesso!" << endl;
                    cout << endl;
                }
            }

            
        }
    }
    // MENU #1 END

    int** m = new int* [vertexCount];
    setAdjacencyMatrix(m, vertexCount, adjacencies);

    showAdjacencyList(adjacencies);
    cout << endl;
    showAdjacencyMatrix(m, vertexCount);

    // MAIN LOOP 
    bool stop = false;

    while (!stop) {
        //cout << endl;
        cout << "Selecione uma opcao: " << endl;
        cout << "a - DFS - Depth First Search" << endl;
        cout << "b - BFS - Amplitude" << endl;
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
            cout << endl;
            cout << "DFS - Escolha uma opção: " << endl;
            cout << "a - buscar por vertice especifico" << endl;
            cout << "b - percorrer todo o grafo" << endl;
            cout << "c - Voltar" << endl;
            cin >> subOption;

            if(subOption == 'a') {
                int vertexToFind;
                cout << "Informe o vertice que voce deseja achar:" << endl;
                cin >> vertexToFind;

                cout << "Informe o vertice inicial da busca: " << endl;
                cin >> initialVertex;

                dfs(initialVertex - 1, vertexCount, m, vertexToFind);
            }

            if (subOption == 'b') {
                cout << "Informe o vertice inicial da busca: " << endl;
                cin >> initialVertex;
                dfs(initialVertex - 1, vertexCount, m);
            }

        }
        if (option == 'b') { //BFS - Amplitude
            cout << endl;
            cout << "BFS - Escolha uma opcao: " << endl;
            cout << "a - buscar por vertice especifico" << endl;
            cout << "b - percorrer todo o grafo" << endl;
            cout << "c - Voltar" << endl;
            cin >> subOption;

            if (subOption == 'a') {
                int vertexToFind;
                cout << "Informe o vertice que voce deseja achar:" << endl;
                cin >> vertexToFind;

                cout << "Informe o vertice inicial da busca: " << endl;
                cin >> initialVertex;

                bfs(initialVertex - 1, vertexCount, m, vertexToFind);
            }

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
        if (option == 'e') { // adicionar aresta/arco
            int originVertex, destinationVertex;
            cout << "Informe o vertice de origem: " << endl;
            cin >> originVertex;
            cout << "Informe o vertice de destino: " << endl;
            cin >> destinationVertex;

            addAdjacency(adjacencies, originVertex, destinationVertex);
            setAdjacencyMatrix(m, vertexCount, adjacencies);
        }
        if (option == 'f') { // excluir aresta/arco
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
        if (option == 'g') { // mostrar matriz e lista de adjacencia
            showAdjacencyMatrix(m, vertexCount);
            showAdjacencyList(adjacencies);
        }
        if (option == 'h') stop = true; // sair

    }

    // MAIN LOOP END

    cleanAdjacencyMatrix(m, vertexCount);
}




