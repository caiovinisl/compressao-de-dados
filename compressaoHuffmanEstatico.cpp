#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <bitset>

using namespace std;

// Estrutura para representar um nó da árvore de Huffman
struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char ch, int freq, HuffmanNode* leftChild, HuffmanNode* rightChild)
        : character(ch), frequency(freq), left(leftChild), right(rightChild) {}
};

// Função para comparar dois nós de Huffman com base em suas frequências
struct CompareNodes {
    bool operator()(HuffmanNode* a, HuffmanNode* b)
    {
        return a->frequency > b->frequency;
    }
};

// Função para construir a árvore de Huffman e retornar o nó raiz
HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& freqMap)
{
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;

    // Cria um nó para cada caractere com sua frequência
    for (const auto& pair : freqMap) {
        pq.push(new HuffmanNode(pair.first, pair.second, nullptr, nullptr));
    }

    // Combina os nós até que reste apenas um nó na fila de prioridade
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        // Cria um novo nó pai com a soma das frequências dos filhos
        // e insere de volta na fila de prioridade
        int sumFreq = left->frequency + right->frequency;
        pq.push(new HuffmanNode('\0', sumFreq, left, right));
    }

    // O último nó na fila de prioridade é o nó raiz da árvore de Huffman
    return pq.top();
}

// Função auxiliar para construir a tabela de codificação
void buildEncodingTable(HuffmanNode* root, const string& code, unordered_map<char, string>& encodingTable)
{
    if (root == nullptr) {
        return;
    }

    // Se o nó atual for uma folha, armazena o código de Huffman correspondente na tabela
    if (!root->left && !root->right) {
        encodingTable[root->character] = code;
    }

    // Percorre a árvore recursivamente
    buildEncodingTable(root->left, code + "0", encodingTable);
    buildEncodingTable(root->right, code + "1", encodingTable);
}

// Função para comprimir um arquivo usando a codificação de Huffman
void compressFile(const string& inputFile)
{
    ifstream file(inputFile, ios::binary);
    if (!file.is_open()) {
        cout << "Erro ao abrir o arquivo de entrada." << endl;
        return;
    }

    // Cria um vetor para armazenar os bytes do arquivo
    vector<unsigned char> bytes(
        (istreambuf_iterator<char>(file)),
        (istreambuf_iterator<char>()));

    // Calcula a frequência de cada byte no arquivo
    unordered_map<char, int> freqMap;
    for (char byte : bytes) {
        freqMap[byte]++;
    }

    // Constrói a árvore de Huffman
    HuffmanNode* root = buildHuffmanTree(freqMap);

    // Constrói a tabela de codificação
    unordered_map<char, string> encodingTable;
    buildEncodingTable(root, "", encodingTable);

    // Cria um novo vetor para armazenar os bytes comprimidos
    vector<unsigned char> compressedBytes;

    // Comprime cada byte do arquivo usando a tabela de codificação
    for (char byte : bytes) {
        string code = encodingTable[byte];
        for (char bit : code) {
            if (bit == '0') {
                compressedBytes.push_back(0);
            } else {
                compressedBytes.push_back(1);
            }
        }
    }

    // Obtém o nome do arquivo de entrada
    string outputFileName = inputFile;
    // Encontra a posição do último ponto na extensão
    size_t extensionPos = outputFileName.find_last_of(".");
    // Insere "-compressed" antes da extensão
    outputFileName.insert(extensionPos, "-compressed");

    // Cria um novo arquivo de saída
    ofstream output(outputFileName, ios::binary);
    if (!output.is_open()) {
        cout << "Erro ao criar o arquivo de saída." << endl;
        return;
    }

    // Escreve os bytes comprimidos no arquivo de saída
    output.write(reinterpret_cast<char*>(compressedBytes.data()), compressedBytes.size());

    // Libera a memória alocada para a árvore de Huffman
    delete root;

    cout << "Arquivo comprimido com sucesso. Nome do arquivo de saída: " << outputFileName << endl;
}

int main()
{
    string inputFile;
    cout << "Digite o nome do arquivo de entrada: ";
    getline(cin, inputFile);

    compressFile(inputFile);

    return 0;
}
