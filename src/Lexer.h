#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

#include "Token.h"

using namespace std;

class Lexer {

private:

    string codigo;
    size_t posicion;

    // Automata de identificadores
    bool esInicioIdentificador(char c);
    bool esParteIdentificador(char c);

    string leerIdentificador();

    // Automata de numeros
    string leerNumero();

    // Automata de operadores
    string leerOperador();

    // Clasificacion de tokens
    Token identificarPalabra(const string& palabra);
    Token identificarOperador(const string& operador);

public:

    Lexer(const string& codigo);

    vector<Token> analizar();
};

#endif