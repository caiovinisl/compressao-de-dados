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
    std::vector<int> compressedData;
    std::string current;

    while (inFile.read(reinterpret_cast<char*>(&code), sizeof(code))) {
        compressedData.push_back(code);
    }

    std::string previous = dictionary[compressedData[0]];
    std::string output = previous;
    
    for (int i = 1; i < compressedData.size(); ++i) {
        int currentCode = compressedData[i];
        std::string entry;
        
        if (currentCode < dictionary.size()) {
            entry = dictionary[currentCode];
        } else if (currentCode == dictionary.size()) {
            entry = previous + previous[0];
        } else {
            std::cerr << "Erro: Código inválido encontrado durante a descompressão.\n";
            return;
        }
        
        output += entry;
        
        dictionary.push_back(previous + entry[0]);
        previous = entry;
    }

    outFile.write(output.c_str(), output.length());

    inFile.close();
    outFile.close();

    // Cálculo da taxa de compressão
    double compressedSize = fs::file_size(inputFile);
    double uncompressedSize = fs::file_size(outputFile);
    double compressionRatio = uncompressedSize / compressedSize;
    double entropy = 8.0;  // Estimativa de entropia para sequências de 8 bits
    double compressionRatioPercentage = (1.0 - compressionRatio) * 100.0;
    double entropyPercentage = (1.0 - (entropy / 8.0)) * 100.0;

    std::cout << "Descompressao concluida com sucesso!\n";
    std::cout << "Taxa de compressao: " << compressionRatioPercentage << "%\n";
    std::cout << "Entropia estimada: " << entropyPercentage << "%\n";
}

int main() {
    std::string compressedFilename;
    std::cout << "Digite o nome do arquivo comprimido: ";
    std::cin >> compressedFilename;

    std::string inputFile = "entradas/" + compressedFilename;
    std::string originalFilename = compressedFilename.substr(0, compressedFilename.find_last_of('-'));

    // Obter a extensão do arquivo original
    std::string extension = fs::path(originalFilename).extension().string();

    std::string decompressedFilename = "saidas/" + originalFilename + "-decompressed" + extension;

    // Cria o diretório de saída se não existir
    fs::create_directory("saidas");

    // Descomprime o arquivo comprimido
    decompress(inputFile, decompressedFilename);

    return 0;
}
