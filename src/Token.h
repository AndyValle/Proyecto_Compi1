#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

enum class TokenType {

    // Palabras reservadas
    LET,
    FN,
    IF,
    ELSE,
    WHILE,
    FOR,
    RETURN,

    // Tipos de datos
    I32,
    F64,
    BOOL,
    CHAR,
    STR,

    // Valores booleanos
    TRUE,
    FALSE,

    // Identificadores y literales
    IDENTIFIER,
    INTEGER,
    DECIMAL,
    STRING_LITERAL,
    CHAR_LITERAL,

    // Operadores aritmeticos
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,

    // Operadores logicos
    AND,
    OR,
    NOT,

    // Asignacion y comparacion
    ASSIGN,
    EQUAL,
    NOT_EQUAL,
    LESS,
    GREATER,
    LESS_EQUAL,
    GREATER_EQUAL,

    // Flecha de retorno de funciones
    ARROW,

    // Delimitadores
    LEFT_PAREN,
    RIGHT_PAREN,

    LEFT_BRACE,
    RIGHT_BRACE,

    LEFT_BRACKET,
    RIGHT_BRACKET,

    COMMA,
    SEMICOLON,
    COLON,

    // Control
    END_OF_FILE,

    // Errores
    UNKNOWN,
    ERROR
};


struct Token {

    TokenType tipo;
    string lexema;

    Token(TokenType tipo, const string& lexema) {
        this->tipo = tipo;
        this->lexema = lexema;
    }
};

#endif