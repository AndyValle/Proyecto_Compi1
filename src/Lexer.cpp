#include "Lexer.h"

#include <cctype>


Lexer::Lexer(const string& codigo) {

    this->codigo = codigo;
    this->posicion = 0;
}


// --------------------------------------------------
// AUTOMATA DE IDENTIFICADORES
// --------------------------------------------------

bool Lexer::esInicioIdentificador(char c) {

    return isalpha(static_cast<unsigned char>(c)) || c == '_';
}


bool Lexer::esParteIdentificador(char c) {

    return isalnum(static_cast<unsigned char>(c)) || c == '_';
}


string Lexer::leerIdentificador() {

    string palabra;

    while (posicion < codigo.size() &&
           esParteIdentificador(codigo[posicion])) {

        palabra += codigo[posicion];
        posicion++;
    }

    return palabra;
}


// --------------------------------------------------
// AUTOMATA DE NUMEROS
// --------------------------------------------------

string Lexer::leerNumero() {

    string numero;

    // Leer parte entera
    while (posicion < codigo.size() &&
           isdigit(static_cast<unsigned char>(codigo[posicion]))) {

        numero += codigo[posicion];
        posicion++;
    }


    // Revisar si tiene parte decimal
    if (posicion < codigo.size() &&
        codigo[posicion] == '.') {

        // Solo aceptar decimal si despues del punto hay un numero
        if (posicion + 1 < codigo.size() &&
            isdigit(static_cast<unsigned char>(codigo[posicion + 1]))) {

            numero += '.';
            posicion++;

            while (posicion < codigo.size() &&
                   isdigit(static_cast<unsigned char>(codigo[posicion]))) {

                numero += codigo[posicion];
                posicion++;
            }
        }
    }

    return numero;
}


// --------------------------------------------------
// AUTOMATA DE OPERADORES
// --------------------------------------------------

string Lexer::leerOperador() {

    string operador;

    char actual = codigo[posicion];

    operador += actual;
    posicion++;


    if (posicion < codigo.size()) {

        char siguiente = codigo[posicion];

        // Operadores de dos caracteres
        if ((actual == '&' && siguiente == '&') ||
            (actual == '|' && siguiente == '|') ||
            (actual == '-' && siguiente == '>') ||
            (actual == '=' && siguiente == '=') ||
            (actual == '!' && siguiente == '=') ||
            (actual == '<' && siguiente == '=') ||
            (actual == '>' && siguiente == '=')) {

            operador += siguiente;
            posicion++;
        }
    }

    return operador;
}


// --------------------------------------------------
// PALABRAS RESERVADAS
// --------------------------------------------------

Token Lexer::identificarPalabra(const string& palabra) {

    if (palabra == "let")
        return Token(TokenType::LET, palabra);

    if (palabra == "fn")
        return Token(TokenType::FN, palabra);

    if (palabra == "if")
        return Token(TokenType::IF, palabra);

    if (palabra == "else")
        return Token(TokenType::ELSE, palabra);

    if (palabra == "while")
        return Token(TokenType::WHILE, palabra);

    if (palabra == "for")
        return Token(TokenType::FOR, palabra);

    if (palabra == "return")
        return Token(TokenType::RETURN, palabra);


    // Tipos de datos

    if (palabra == "i32")
        return Token(TokenType::I32, palabra);

    if (palabra == "f64")
        return Token(TokenType::F64, palabra);

    if (palabra == "bool")
        return Token(TokenType::BOOL, palabra);

    if (palabra == "char")
        return Token(TokenType::CHAR, palabra);

    if (palabra == "str")
        return Token(TokenType::STR, palabra);


    // Si no es palabra reservada, es identificador

    return Token(TokenType::IDENTIFIER, palabra);
}


// --------------------------------------------------
// IDENTIFICAR OPERADORES
// --------------------------------------------------

Token Lexer::identificarOperador(const string& op) {

    if (op == "+")
        return Token(TokenType::PLUS, op);

    if (op == "-")
        return Token(TokenType::MINUS, op);

    if (op == "*")
        return Token(TokenType::MULTIPLY, op);

    if (op == "/")
        return Token(TokenType::DIVIDE, op);

    if (op == "&&")
        return Token(TokenType::AND, op);

    if (op == "||")
        return Token(TokenType::OR, op);

    if (op == "!")
        return Token(TokenType::NOT, op);

    if (op == "=")
        return Token(TokenType::ASSIGN, op);

    if (op == "==")
        return Token(TokenType::EQUAL, op);

    if (op == "!=")
        return Token(TokenType::NOT_EQUAL, op);

    if (op == "<")
        return Token(TokenType::LESS, op);

    if (op == ">")
        return Token(TokenType::GREATER, op);

    if (op == "<=")
        return Token(TokenType::LESS_EQUAL, op);

    if (op == ">=")
        return Token(TokenType::GREATER_EQUAL, op);

    if (op == "->")
        return Token(TokenType::ARROW, op);


    return Token(TokenType::UNKNOWN, op);
}


// --------------------------------------------------
// ANALIZADOR LEXICO PRINCIPAL
// --------------------------------------------------

vector<Token> Lexer::analizar() {

    vector<Token> tokens;


    while (posicion < codigo.size()) {

        char actual = codigo[posicion];


        // --------------------------------------------------
        // IGNORAR ESPACIOS, TABS Y SALTOS DE LINEA
        // --------------------------------------------------

        if (isspace(static_cast<unsigned char>(actual))) {

            posicion++;
            continue;
        }


        // --------------------------------------------------
        // IDENTIFICADORES Y PALABRAS RESERVADAS
        // --------------------------------------------------

        if (esInicioIdentificador(actual)) {

            string palabra = leerIdentificador();

            tokens.push_back(
                identificarPalabra(palabra)
            );

            continue;
        }


        // --------------------------------------------------
        // NUMEROS
        // --------------------------------------------------

        if (isdigit(static_cast<unsigned char>(actual))) {

            string numero = leerNumero();


            if (numero.find('.') != string::npos) {

                tokens.push_back(
                    Token(TokenType::DECIMAL, numero)
                );

            } else {

                tokens.push_back(
                    Token(TokenType::INTEGER, numero)
                );
            }

            continue;
        }


        // --------------------------------------------------
        // DELIMITADORES
        // --------------------------------------------------

        switch (actual) {

            case '(':

                tokens.push_back(
                    Token(TokenType::LEFT_PAREN, "(")
                );

                posicion++;
                continue;


            case ')':

                tokens.push_back(
                    Token(TokenType::RIGHT_PAREN, ")")
                );

                posicion++;
                continue;


            case '{':

                tokens.push_back(
                    Token(TokenType::LEFT_BRACE, "{")
                );

                posicion++;
                continue;


            case '}':

                tokens.push_back(
                    Token(TokenType::RIGHT_BRACE, "}")
                );

                posicion++;
                continue;


            case '[':

                tokens.push_back(
                    Token(TokenType::LEFT_BRACKET, "[")
                );

                posicion++;
                continue;


            case ']':

                tokens.push_back(
                    Token(TokenType::RIGHT_BRACKET, "]")
                );

                posicion++;
                continue;


            case ',':

                tokens.push_back(
                    Token(TokenType::COMMA, ",")
                );

                posicion++;
                continue;


            case ';':

                tokens.push_back(
                    Token(TokenType::SEMICOLON, ";")
                );

                posicion++;
                continue;


            case ':':

                tokens.push_back(
                    Token(TokenType::COLON, ":")
                );

                posicion++;
                continue;
        }


        // --------------------------------------------------
        // OPERADORES
        // --------------------------------------------------

        if (actual == '+' ||
            actual == '-' ||
            actual == '*' ||
            actual == '/' ||
            actual == '&' ||
            actual == '|' ||
            actual == '!' ||
            actual == '=' ||
            actual == '<' ||
            actual == '>') {

            string operador = leerOperador();

            tokens.push_back(
                identificarOperador(operador)
            );

            continue;
        }


        // --------------------------------------------------
        // CARACTER DESCONOCIDO
        // --------------------------------------------------

        tokens.push_back(
            Token(
                TokenType::UNKNOWN,
                string(1, actual)
            )
        );

        posicion++;
    }


    // Token que indica que terminamos de leer el codigo

    tokens.push_back(
        Token(TokenType::END_OF_FILE, "")
    );


    return tokens;
}