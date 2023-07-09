# compressao-de-dados

<p align="center">
  <img alt="GitHub language count" src="https://img.shields.io/github/languages/count/caiovinisl/compressao-de-dados?color=%2304D361">

  <img alt="Repository size" src="https://img.shields.io/github/repo-size/caiovinisl/compressao-de-dados">
  
  <a href="https://github.com/caiovinisl/metodos-hashing/commits/main">
    <img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/caiovinisl/compressao-de-dados">
  </a>
   
   <a href="https://github.com/caiovinisl/metodos-hashing/stargazers">
    <img alt="Stargazers" src="https://img.shields.io/github/stars/caiovinisl/compressao-de-dados?style=social">
  </a>
  
 
</p>

<h4 align="center"> 
	🚧 Compressão de Dados 🚧
</h4>

<p align="center">
	<img alt="Status Em Desenvolvimento" src="https://img.shields.io/badge/STATUS-EM%20DESENVOLVIMENTO-green">
	<!-- <img alt="Status Concluído" src="https://img.shields.io/badge/STATUS-CONCLU%C3%8DDO-brightgreen"> -->
</p>

<p align="center">
 <a href="#-sobre-o-projeto">Sobre</a> •
 <a href="#-funcionalidades">Funcionalidades</a> •
 <a href="#-como-executar-o-projeto">Como executar</a> • 
 <a href="#-tecnologias">Tecnologias</a>
</p>

## 💻 Sobre o projeto

📄 Compressão de dados - é um projeto para avaliar o realizar a compressão e descompressão de dados de texto, código fonte e imagens.

Projeto desenvolvido durante a matéria MATA54 - Estrutura de Dados II da Universidade Federal da Bahia oferecida pelo professor George Lima.

---

## ⚙️ Funcionalidades

- [x] Compressão de Dados com LZW
- [x] Descompressão de Dados com LZW

---

## 🛣️ Como executar o projeto

#### 🎲 Rodando a aplicação

```bash

# Clone este repositório
$ git clone https://github.com/caiovinisl/compressao-de-dados.git

# Acesse a pasta do projeto no terminal/cmd
$ cd compressao-de-dados

# Acesse a pasta com os programas e insira algum arquivo de texto, código fonte ou imagem no diretório '/entradas'.
# A primeira linha conterá o nome do arquivo. Ex: input.txt

# Compile o código com o método de hashing desejado
$ g++ compressaoLZW.cpp -std=c++17 -o compressaoLZW
ou
$ g++ descompressaoLZW.cpp -std=c++17 -o descompressaoLZW

# Execute o código
$ compressaoLZW.exe
ou
$ descompressaoLZW.exe

# O código será executado e retornará o arquivo comprimido ou descompremido no diretório '/saidas'. Ex: input-compressed.txt

```

## 🛠 Tecnologias

- **[C++](https://cplusplus.com/)**

---
