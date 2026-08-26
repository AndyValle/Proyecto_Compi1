#include <iostream>
#include <string>
#include <vector>

#include "Lexer.h"

using namespace std;


// Funcion para convertir el tipo de token a texto
string tokenTypeToString(TokenType tipo) {

    switch (tipo) {

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


        case TokenType::IDENTIFIER:
            return "IDENTIFIER";

        case TokenType::INTEGER:
            return "INTEGER";

        case TokenType::DECIMAL:
            return "DECIMAL";


        case TokenType::PLUS:
            return "PLUS";

        case TokenType::MINUS:
            return "MINUS";

        case TokenType::MULTIPLY:
            return "MULTIPLY";

        case TokenType::DIVIDE:
            return "DIVIDE";


        case TokenType::AND:
            return "AND";

        case TokenType::OR:
            return "OR";

        case TokenType::NOT:
            return "NOT";


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


        case TokenType::ARROW:
            return "ARROW";


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


        case TokenType::END_OF_FILE:
            return "EOF";


        case TokenType::UNKNOWN:
            return "UNKNOWN";
    }


    return "UNKNOWN";
}


int main() {

    // Codigo Rust que vamos a analizar

    string codigo = R"(

fn suma(a: i32, b: i32) -> i32 {

    return a + b;
}

fn main() {

    let x = 10;
    let y = 20;

    if x < y {

        let resultado = suma(x, y);

    } else {

        return;
    }
}

)";


    // Crear el lexer

    Lexer lexer(codigo);


    // Analizar el codigo

    vector<Token> tokens = lexer.analizar();


    // Mostrar los tokens encontrados

    cout << "==============================" << endl;
    cout << "      ANALIZADOR LEXICO        " << endl;
    cout << "==============================" << endl;
    cout << endl;


    for (const Token& token : tokens) {

        cout << tokenTypeToString(token.tipo);

        if (!token.lexema.empty()) {

            cout << " -> " << token.lexema;
        }

        cout << endl;
    }


    return 0;
}