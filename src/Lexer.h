
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

    // -------------------------
    // Identificadores
    // -------------------------

    bool esInicioIdentificador(char c);
    bool esParteIdentificador(char c);

    string leerIdentificador();


    // -------------------------
    // Numeros
    // -------------------------

    string leerNumero();


    // -------------------------
    // Strings y char
    // -------------------------

    Token leerCadena();
    Token leerCaracter();


    // -------------------------
    // Operadores
    // -------------------------

    string leerOperador();


    // -------------------------
    // Comentarios
    // -------------------------

    void saltarComentarioLinea();
    bool saltarComentarioBloque();


    // -------------------------
    // Clasificacion
    // -------------------------

    Token identificarPalabra(const string& palabra);
    Token identificarOperador(const string& operador);


public:

    Lexer(const string& codigo);

    vector<Token> analizar();
};

#endif