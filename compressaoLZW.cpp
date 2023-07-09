#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <filesystem>

namespace fs = std::filesystem;

// Função para comprimir um arquivo usando o algoritmo LZW
void compress(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    if (!inFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de entrada.\n";
        return;
    }

    if (!outFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de saída.\n";
        return;
    }

    // Inicializa o dicionário com os caracteres ASCII
    std::unordered_map<std::string, int> dictionary;
    for (int i = 0; i < 256; ++i) {
        std::string ch = std::string(1, static_cast<char>(i));
        dictionary[ch] = i;
    }

    std::string current;
    char ch;
    std::vector<int> compressedData;

    while (inFile.get(ch)) {
        std::string next = current + ch;

        if (dictionary.find(next) != dictionary.end()) {
            // O próximo caractere faz parte do dicionário
            current = next;
        } else {
            // O próximo caractere não existe no dicionário
            compressedData.push_back(dictionary[current]);

            // Adiciona a nova entrada no dicionário
            dictionary[next] = dictionary.size();

            // Reinicializa o current
            current = std::string(1, ch);
        }
    }

    // Trata o último caractere
    if (!current.empty()) {
        compressedData.push_back(dictionary[current]);
    }

    // Escreve os dados comprimidos no arquivo de saída
    for (const int& code : compressedData) {
        outFile.write(reinterpret_cast<const char*>(&code), sizeof(code));
    }

    inFile.close();
    outFile.close();

    // Cálculo da taxa de compressão
    double uncompressedSize = fs::file_size(inputFile);
    double compressedSize = fs::file_size(outputFile);
    double compressionRatio = compressedSize / uncompressedSize;
    double entropy = 8.0;  // Estimativa de entropia para sequências de 8 bits
    double compressionRatioPercentage = (1.0 - compressionRatio) * 100.0;
    double entropyPercentage = (1.0 - (entropy / 8.0)) * 100.0;

    std::cout << "Compressao concluida com sucesso!\n";
    std::cout << "Taxa de compressao: " << compressionRatioPercentage << "%\n";
    std::cout << "Entropia estimada: " << entropyPercentage << "%\n";
}

int main() {
    std::string inputFilename;
    std::cout << "Digite o nome do arquivo de entrada: ";
    std::cin >> inputFilename;

    std::string inputFile = "entradas/" + inputFilename;
    std::string compressedFilename = "saidas/" + inputFilename + "-compressed.bin";

    // Cria o diretório de saída se não existir
    fs::create_directory("saidas");

    // Comprime o arquivo de entrada
    compress(inputFile, compressedFilename);

    return 0;
}