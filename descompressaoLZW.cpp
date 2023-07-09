#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

// Função para descomprimir um arquivo usando o algoritmo LZW
void decompress(const std::string& inputFile, const std::string& outputFile) {
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
    std::vector<std::string> dictionary;
    for (int i = 0; i < 256; ++i) {
        dictionary.push_back(std::string(1, static_cast<char>(i)));
    }

    int code;
    std::vector<std::string> decompressedData;
    std::string previous;
    char ch;

    while (inFile.read(reinterpret_cast<char*>(&code), sizeof(code))) {
        std::string current;

        if (code < dictionary.size()) {
            // O código está no dicionário
            current = dictionary[code];
        } else {
            // Código inválido
            current = previous + previous[0];
        }

        decompressedData.push_back(current);

        // Adiciona a nova entrada no dicionário
        dictionary.push_back(previous + current[0]);

        previous = current;
    }

    // Escreve os dados descomprimidos no arquivo de saída
    for (const std::string& data : decompressedData) {
        for (const char& ch : data) {
            outFile.put(ch);
        }
    }

    inFile.close();
    outFile.close();
}

int main() {
    std::string compressedFilename;
    std::cout << "Digite o nome do arquivo comprimido: ";
    std::cin >> compressedFilename;

    std::string inputFile = "entradas/" + compressedFilename;
    std::string decompressedFilename = "saidas/" + compressedFilename.substr(0, compressedFilename.find_last_of('.')) + "-decompressed.txt";

    // Cria o diretório de saída se não existir
    fs::create_directory("saidas");

    // Descomprime o arquivo comprimido
    decompress(inputFile, decompressedFilename);

    std::cout << "Descompressao concluida com sucesso!\n";

    return 0;
}
