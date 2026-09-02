
#include <iostream>
#include <string>
#include <vector>

#include "Lexer.h"

using namespace std;


// ==================================================
// CONVERTIR TOKEN A TEXTO
// ==================================================

string tokenTypeToString(TokenType tipo) {

    switch (tipo) {


        // Palabras reservadas

        case TokenType::LET:
            return "LET";

        case TokenType::FN:
            return "FN";

        case TokenType::IF:
            return "IF";

        case TokenType::ELSE:
            return "ELSE";

        case TokenType::WHILE:
            return "WHILE";

        case TokenType::FOR:
            return "FOR";

        case TokenType::RETURN:
            return "RETURN";


        // Tipos

        case TokenType::I32:
            return "I32";

        case TokenType::F64:
            return "F64";

        case TokenType::BOOL:
            return "BOOL";

        case TokenType::CHAR:
            return "CHAR";

        case TokenType::STR:
            return "STR";


        // Booleanos

        case TokenType::TRUE:
            return "TRUE";

        case TokenType::FALSE:
            return "FALSE";


        // Identificadores y literales

        case TokenType::IDENTIFIER:
            return "IDENTIFIER";

        case TokenType::INTEGER:
            return "INTEGER";

        case TokenType::DECIMAL:
            return "DECIMAL";

        case TokenType::STRING_LITERAL:
            return "STRING_LITERAL";

        case TokenType::CHAR_LITERAL:
            return "CHAR_LITERAL";


        // Operadores aritmeticos

        case TokenType::PLUS:
            return "PLUS";

        case TokenType::MINUS:
            return "MINUS";

        case TokenType::MULTIPLY:
            return "MULTIPLY";

        case TokenType::DIVIDE:
            return "DIVIDE";


        // Operadores logicos

        case TokenType::AND:
            return "AND";

        case TokenType::OR:
            return "OR";

        case TokenType::NOT:
            return "NOT";


        // Asignacion y comparacion

        case TokenType::ASSIGN:
            return "ASSIGN";

        case TokenType::EQUAL:
            return "EQUAL";

        case TokenType::NOT_EQUAL:
            return "NOT_EQUAL";

        case TokenType::LESS:
            return "LESS";

        case TokenType::GREATER:
            return "GREATER";

        case TokenType::LESS_EQUAL:
            return "LESS_EQUAL";

        case TokenType::GREATER_EQUAL:
            return "GREATER_EQUAL";


        // Flecha

        case TokenType::ARROW:
            return "ARROW";


        // Delimitadores

        case TokenType::LEFT_PAREN:
            return "LEFT_PAREN";

        case TokenType::RIGHT_PAREN:
            return "RIGHT_PAREN";

        case TokenType::LEFT_BRACE:
            return "LEFT_BRACE";

        case TokenType::RIGHT_BRACE:
            return "RIGHT_BRACE";

        case TokenType::LEFT_BRACKET:
            return "LEFT_BRACKET";

        case TokenType::RIGHT_BRACKET:
            return "RIGHT_BRACKET";

        case TokenType::COMMA:
            return "COMMA";

        case TokenType::SEMICOLON:
            return "SEMICOLON";

        case TokenType::COLON:
            return "COLON";


        // Final

        case TokenType::END_OF_FILE:
            return "EOF";


        // Errores

        case TokenType::UNKNOWN:
            return "UNKNOWN";

        case TokenType::ERROR:
            return "ERROR";
    }


    return "UNKNOWN";
}


// ==================================================
// MAIN
// ==================================================

int main() {

    /*
        Codigo Rust utilizado para probar
        los automatas del lexer.
    */

    string codigo = R"(

fn suma(a: i32, b: i32) -> i32 {

    return a + b;
}

fn main() {

    // Variables numericas

    let x = 10;
    let y = 20;

    let precio = 35.50;


    // Booleano

    let activo: bool = true;


    // Caracter

    let letra: char = 'A';


    // Cadena

    let mensaje: str = "Hola mundo";


    /*
        Prueba de if
        con comparacion
    */

    if x < y && activo == true {

        let resultado = suma(x, y);

    } else {

        return;
    }
}

)";


    // Crear lexer

    Lexer lexer(codigo);


    // Analizar codigo

    vector<Token> tokens =
        lexer.analizar();


    // Mostrar resultado

    cout << "==========================================" << endl;
    cout << "           ANALIZADOR LEXICO              " << endl;
    cout << "==========================================" << endl;

    cout << endl;


    for (const Token& token : tokens) {

        cout
            << tokenTypeToString(token.tipo);


        if (!token.lexema.empty()) {

            cout
                << " -> "
                << token.lexema;
        }


        cout << endl;
    }


    return 0;
}