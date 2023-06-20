#include <iostream>
#include <fstream>
#include <unordered_map>

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

// Função para reconstruir a árvore de Huffman a partir dos dados comprimidos
HuffmanNode* rebuildHuffmanTree(ifstream& input)
{
    char bit;
    input.read(&bit, sizeof(char));

    if (bit == '1') {
        char character;
        input.read(&character, sizeof(char));
        return new HuffmanNode(character, 0, nullptr, nullptr);
    }

    HuffmanNode* left = rebuildHuffmanTree(input);
    HuffmanNode* right = rebuildHuffmanTree(input);
    return new HuffmanNode('\0', 0, left, right);
}

// Função para descomprimir um arquivo usando a codificação de Huffman
void decompressFile(const string& inputFile)
{
    ifstream input(inputFile, ios::binary);
    if (!input.is_open()) {
        cout << "Erro ao abrir o arquivo de entrada." << endl;
        return;
    }

    // Reconstrói a árvore de Huffman a partir dos dados comprimidos
    HuffmanNode* root = rebuildHuffmanTree(input);

    // Cria o nome do arquivo de saída
    size_t dotIndex = inputFile.find_last_of('.');
    string outputFile = inputFile.substr(0, dotIndex) + "-decompressed" + inputFile.substr(dotIndex);

    // Cria um arquivo de saída para armazenar os bytes descomprimidos
    ofstream output(outputFile, ios::binary);
    if (!output.is_open()) {
        cout << "Erro ao criar o arquivo de saída." << endl;
        delete root;
        return;
    }

    HuffmanNode* currentNode = root;
    char bit;
    while (input.read(&bit, sizeof(char))) {
        if (bit == '0') {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }

        if (!currentNode->left && !currentNode->right) {
            output.write(&currentNode->character, sizeof(char));
            currentNode = root;
        }
    }

    // Libera a memória alocada para a árvore de Huffman
    delete root;

    cout << "Arquivo descomprimido com sucesso. Nome do arquivo de saída: " << outputFile << endl;
}

int main()
{
    string inputFile;
    cout << "Digite o nome do arquivo de entrada: ";
    getline(cin, inputFile);

    decompressFile(inputFile);

    return 0;
}
