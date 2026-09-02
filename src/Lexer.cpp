
#include "Lexer.h"

#include <cctype>


// ==================================================
// CONSTRUCTOR
// ==================================================

Lexer::Lexer(const string& codigo) {

    this->codigo = codigo;
    this->posicion = 0;
}


// ==================================================
// AUTOMATA DE IDENTIFICADORES
// ==================================================

bool Lexer::esInicioIdentificador(char c) {

    return isalpha(static_cast<unsigned char>(c)) || c == '_';
}


bool Lexer::esParteIdentificador(char c) {

    return isalnum(static_cast<unsigned char>(c)) || c == '_';
}


string Lexer::leerIdentificador() {

    string palabra;

    while (
        posicion < codigo.size() &&
        esParteIdentificador(codigo[posicion])
    ) {

        palabra += codigo[posicion];

        posicion++;
    }

    return palabra;
}


// ==================================================
// AUTOMATA DE NUMEROS
// ==================================================

string Lexer::leerNumero() {

    string numero;


    // Leer parte entera
    while (
        posicion < codigo.size() &&
        isdigit(static_cast<unsigned char>(codigo[posicion]))
    ) {

        numero += codigo[posicion];

        posicion++;
    }


    // Revisar si existe parte decimal
    if (
        posicion < codigo.size() &&
        codigo[posicion] == '.'
    ) {

        // Solo tomamos el punto si despues hay un numero
        if (
            posicion + 1 < codigo.size() &&
            isdigit(
                static_cast<unsigned char>(
                    codigo[posicion + 1]
                )
            )
        ) {

            numero += '.';

            posicion++;


            while (
                posicion < codigo.size() &&
                isdigit(
                    static_cast<unsigned char>(
                        codigo[posicion]
                    )
                )
            ) {

                numero += codigo[posicion];

                posicion++;
            }
        }
    }

    return numero;
}


// ==================================================
// AUTOMATA DE CADENAS
// Ejemplo: "Hola mundo"
// ==================================================

Token Lexer::leerCadena() {

    string cadena;

    // Guardamos la comilla inicial
    cadena += codigo[posicion];

    posicion++;


    while (posicion < codigo.size()) {

        char actual = codigo[posicion];


        // Si encontramos la comilla final
        if (actual == '"') {

            cadena += actual;

            posicion++;

            return Token(
                TokenType::STRING_LITERAL,
                cadena
            );
        }


        // Manejo basico de caracteres escapados
        // Ejemplo: "Hola\n"
        if (actual == '\\') {

            cadena += actual;

            posicion++;


            if (posicion < codigo.size()) {

                cadena += codigo[posicion];

                posicion++;
            }

            continue;
        }


        cadena += actual;

        posicion++;
    }


    // Si llegamos al final sin cerrar las comillas
    return Token(
        TokenType::ERROR,
        cadena
    );
}


// ==================================================
// AUTOMATA DE CARACTERES
// Ejemplo: 'A'
// ==================================================

Token Lexer::leerCaracter() {

    string caracter;


    // Comilla inicial
    caracter += codigo[posicion];

    posicion++;


    // No puede terminar inmediatamente
    if (posicion >= codigo.size()) {

        return Token(
            TokenType::ERROR,
            caracter
        );
    }


    // Caracter escapado
    // Ejemplo: '\n'
    if (codigo[posicion] == '\\') {

        caracter += codigo[posicion];

        posicion++;


        if (posicion >= codigo.size()) {

            return Token(
                TokenType::ERROR,
                caracter
            );
        }


        caracter += codigo[posicion];

        posicion++;
    }

    else {

        // Caracter normal
        caracter += codigo[posicion];

        posicion++;
    }


    // Ahora esperamos la comilla final
    if (
        posicion < codigo.size() &&
        codigo[posicion] == '\''
    ) {

        caracter += codigo[posicion];

        posicion++;


        return Token(
            TokenType::CHAR_LITERAL,
            caracter
        );
    }


    return Token(
        TokenType::ERROR,
        caracter
    );
}


// ==================================================
// AUTOMATA DE OPERADORES
// ==================================================

string Lexer::leerOperador() {

    string operador;


    char actual = codigo[posicion];

    operador += actual;

    posicion++;


    if (posicion < codigo.size()) {

        char siguiente = codigo[posicion];


        // Operadores formados por dos caracteres
        if (
            (actual == '&' && siguiente == '&') ||
            (actual == '|' && siguiente == '|') ||
            (actual == '-' && siguiente == '>') ||
            (actual == '=' && siguiente == '=') ||
            (actual == '!' && siguiente == '=') ||
            (actual == '<' && siguiente == '=') ||
            (actual == '>' && siguiente == '=')
        ) {

            operador += siguiente;

            posicion++;
        }
    }


    return operador;
}


// ==================================================
// COMENTARIO DE UNA LINEA
//
// // comentario
// ==================================================

void Lexer::saltarComentarioLinea() {

    // Saltamos //
    posicion += 2;


    while (
        posicion < codigo.size() &&
        codigo[posicion] != '\n'
    ) {

        posicion++;
    }
}


// ==================================================
// COMENTARIO DE BLOQUE
//
// /* comentario */
// ==================================================

bool Lexer::saltarComentarioBloque() {

    // Saltamos /*
    posicion += 2;


    while (posicion + 1 < codigo.size()) {


        // Buscar */
        if (
            codigo[posicion] == '*' &&
            codigo[posicion + 1] == '/'
        ) {

            posicion += 2;

            return true;
        }


        posicion++;
    }


    // Comentario nunca cerrado
    return false;
}


// ==================================================
// PALABRAS RESERVADAS
// ==================================================

Token Lexer::identificarPalabra(const string& palabra) {


    // Palabras reservadas

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



    // Tipos

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



    // Valores booleanos

    if (palabra == "true")
        return Token(TokenType::TRUE, palabra);


    if (palabra == "false")
        return Token(TokenType::FALSE, palabra);



    // Si no coincide con ninguna palabra reservada
    // entonces es un identificador

    return Token(
        TokenType::IDENTIFIER,
        palabra
    );
}


// ==================================================
// CLASIFICACION DE OPERADORES
// ==================================================

Token Lexer::identificarOperador(const string& op) {


    // Aritmeticos

    if (op == "+")
        return Token(TokenType::PLUS, op);


    if (op == "-")
        return Token(TokenType::MINUS, op);


    if (op == "*")
        return Token(TokenType::MULTIPLY, op);


    if (op == "/")
        return Token(TokenType::DIVIDE, op);



    // Logicos

    if (op == "&&")
        return Token(TokenType::AND, op);


    if (op == "||")
        return Token(TokenType::OR, op);


    if (op == "!")
        return Token(TokenType::NOT, op);



    // Asignacion

    if (op == "=")
        return Token(TokenType::ASSIGN, op);



    // Comparaciones

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



    // Flecha utilizada por funciones

    if (op == "->")
        return Token(TokenType::ARROW, op);



    return Token(
        TokenType::UNKNOWN,
        op
    );
}


// ==================================================
// ANALIZADOR LEXICO PRINCIPAL
// ==================================================

vector<Token> Lexer::analizar() {

    vector<Token> tokens;


    while (posicion < codigo.size()) {

        char actual = codigo[posicion];


        // ==================================================
        // ESPACIOS
        // ==================================================

        if (
            isspace(
                static_cast<unsigned char>(actual)
            )
        ) {

            posicion++;

            continue;
        }


        // ==================================================
        // COMENTARIOS
        // ==================================================

        if (
            actual == '/' &&
            posicion + 1 < codigo.size()
        ) {

            char siguiente = codigo[posicion + 1];


            // Comentario //
            if (siguiente == '/') {

                saltarComentarioLinea();

                continue;
            }


            // Comentario /* */
            if (siguiente == '*') {

                bool cerrado =
                    saltarComentarioBloque();


                if (!cerrado) {

                    tokens.push_back(
                        Token(
                            TokenType::ERROR,
                            "Comentario de bloque sin cerrar"
                        )
                    );
                }

                continue;
            }
        }


        // ==================================================
        // STRINGS
        // ==================================================

        if (actual == '"') {

            tokens.push_back(
                leerCadena()
            );

            continue;
        }


        // ==================================================
        // CARACTERES
        // ==================================================

        if (actual == '\'') {

            tokens.push_back(
                leerCaracter()
            );

            continue;
        }


        // ==================================================
        // IDENTIFICADORES Y PALABRAS RESERVADAS
        // ==================================================

        if (esInicioIdentificador(actual)) {

            string palabra =
                leerIdentificador();


            tokens.push_back(
                identificarPalabra(palabra)
            );


            continue;
        }


        // ==================================================
        // NUMEROS
        // ==================================================

        if (
            isdigit(
                static_cast<unsigned char>(actual)
            )
        ) {

            string numero =
                leerNumero();


            if (
                numero.find('.') != string::npos
            ) {

                tokens.push_back(
                    Token(
                        TokenType::DECIMAL,
                        numero
                    )
                );
            }

            else {

                tokens.push_back(
                    Token(
                        TokenType::INTEGER,
                        numero
                    )
                );
            }


            continue;
        }


        // ==================================================
        // DELIMITADORES
        // ==================================================

        switch (actual) {


            case '(':

                tokens.push_back(
                    Token(
                        TokenType::LEFT_PAREN,
                        "("
                    )
                );

                posicion++;

                continue;



            case ')':

                tokens.push_back(
                    Token(
                        TokenType::RIGHT_PAREN,
                        ")"
                    )
                );

                posicion++;

                continue;



            case '{':

                tokens.push_back(
                    Token(
                        TokenType::LEFT_BRACE,
                        "{"
                    )
                );

                posicion++;

                continue;



            case '}':

                tokens.push_back(
                    Token(
                        TokenType::RIGHT_BRACE,
                        "}"
                    )
                );

                posicion++;

                continue;



            case '[':

                tokens.push_back(
                    Token(
                        TokenType::LEFT_BRACKET,
                        "["
                    )
                );

                posicion++;

                continue;



            case ']':

                tokens.push_back(
                    Token(
                        TokenType::RIGHT_BRACKET,
                        "]"
                    )
                );

                posicion++;

                continue;



            case ',':

                tokens.push_back(
                    Token(
                        TokenType::COMMA,
                        ","
                    )
                );

                posicion++;

                continue;



            case ';':

                tokens.push_back(
                    Token(
                        TokenType::SEMICOLON,
                        ";"
                    )
                );

                posicion++;

                continue;



            case ':':

                tokens.push_back(
                    Token(
                        TokenType::COLON,
                        ":"
                    )
                );

                posicion++;

                continue;
        }


        // ==================================================
        // OPERADORES
        // ==================================================

        if (
            actual == '+' ||
            actual == '-' ||
            actual == '*' ||
            actual == '/' ||
            actual == '&' ||
            actual == '|' ||
            actual == '!' ||
            actual == '=' ||
            actual == '<' ||
            actual == '>'
        ) {

            string operador =
                leerOperador();


            tokens.push_back(
                identificarOperador(operador)
            );


            continue;
        }


        // ==================================================
        // CARACTER NO RECONOCIDO
        // ==================================================

        tokens.push_back(
            Token(
                TokenType::UNKNOWN,
                string(1, actual)
            )
        );


        posicion++;
    }


    // ==================================================
    // FIN DEL ARCHIVO
    // ==================================================

    tokens.push_back(
        Token(
            TokenType::END_OF_FILE,
            ""
        )
    );


    return tokens;
}