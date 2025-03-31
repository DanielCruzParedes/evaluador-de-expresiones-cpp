#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <stack>
#include <cmath>
#include <vector>

// TDD (WIP)

// C++ 23
#include <print>
#include <expected>
#include <utility> // para std::unreachable()
#include <stdfloat>
#include "../includes/EvaluadorDeExpresiones.h"

using namespace std;

unordered_map<string, double> constantes;
bool imprimirResultado = true;

// Funcion para obtener las constantes puestas en el archivo de texto
void obtenerConstantes()
{
    constantes.clear();
    ifstream archivo("../constantes.txt");
    string linea;
    while (getline(archivo, linea))
    {
        size_t pos = linea.find('=');
        if (pos != string::npos)
        {
            string nombre = linea.substr(0, pos);
            double valor = stod(linea.substr(pos + 1));
            constantes[nombre] = valor;
        }
    }

    archivo.close();
}

// Chequiar validaciones de la expresion dada
std::expected<void, std::string> esExpresionValida(string expresion)
{
    string mensaje = "";

    /* --== Verificaciones revisando el primer  y ultimo indice de la expresion ==-- */

    // Verificar que la expresion no este vacia
    if (expresion.empty())
    {
        return std::unexpected("La expresion no puede estar vacia");
        unreachable();
    }

    // Verificar que la expresion no inicie con un operador
    if (expresion[0] == '+' || expresion[0] == '-' || expresion[0] == '*' || expresion[0] == '/' || expresion[0] == '%' || expresion[0] == '^')
    {
        return std::unexpected("La expresion no puede iniciar con un operador");
        unreachable();
    }

    // Verificar que la expresion no termine con un operador
    if (expresion[expresion.size() - 1] == '+' || expresion[expresion.size() - 1] == '-' || expresion[expresion.size() - 1] == '*' || expresion[expresion.size() - 1] == '/' || expresion[expresion.size() - 1] == '%' || expresion[expresion.size() - 1] == '^')
    {
        return std::unexpected("La expresion no puede terminar con un operador");
        unreachable();
    }

    // Verificar que la expresion no empiece con un parentesis de cierre
    if (expresion[0] == ')')
    {
        return std::unexpected("La expresion no puede iniciar con un parentesis de cierre");
        unreachable();
    }

    // Verificar que la expresion no termine con un parentesis de apertura
    if (expresion[expresion.size() - 1] == '(')
    {
        return std::unexpected("La expresion no puede terminar con un parentesis de apertura");
        unreachable();
    }

    // Verificar que la expresion no tenga dos operadores seguidos
    for (int i = 0; i < expresion.size(); i++)
    {
        if ((expresion[i] == '+' || expresion[i] == '-' || expresion[i] == '*' || expresion[i] == '/' || expresion[i] == '%' || expresion[i] == '^') && (expresion[i + 1] == '+' || expresion[i + 1] == '-' || expresion[i + 1] == '*' || expresion[i + 1] == '/' || expresion[i + 1] == '%' || expresion[i + 1] == '^'))
        {
            return std::unexpected("La expresion no puede tener dos operadores seguidos");
            unreachable();
        }
    }

    // Verificar que la expresion no tenga un parentesis de apertura seguido de un operador
    for (int i = 0; i < expresion.size(); i++)
    {
        if ((expresion[i] == '(' && (expresion[i + 1] == '+' || expresion[i + 1] == '-' || expresion[i + 1] == '*' || expresion[i + 1] == '/' || expresion[i + 1] == '%' || expresion[i + 1] == '^')))
        {
            return std::unexpected("La expresion no puede tener un parentesis de apertura seguido de un operador");
            unreachable();
        }
    }

    // Verificar que los parentesis se cierren correctamente
    int parentesis = 0;
    for (int i = 0; i < expresion.size(); i++)
    {
        if (expresion[i] == '(')
        {
            parentesis++;
        }
        else if (expresion[i] == ')')
        {
            parentesis--;
        }
    }
    if (parentesis != 0)
    {
        return std::unexpected("Los parentesis no estan balanceados");
        unreachable();
    }

    // Verificar que no haya caracteres no permitidos
    for (int i = 0; i < expresion.size(); i++)
    {
        if (!isalnum(expresion[i]) && expresion[i] != '+' && expresion[i] != '-' && expresion[i] != '*' && expresion[i] != '/' && expresion[i] != '%' && expresion[i] != '^' && expresion[i] != '(' && expresion[i] != ')' && expresion[i] != '.' && expresion[i])
        {
            return std::unexpected("La expresion contiene caracteres no permitidos");
            unreachable();
        }
    }

    return std::expected<void, std::string>();
    unreachable();
}

// Función para obtener la precedencia de los operadores
int precedence(char op)
{
    unordered_map<char, int> prec{
        {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'%', 2}, {'^', 3}};

    return prec.contains(op) ? prec[op] : -1;
    unreachable();
}

// Función para convertir una expresión infija a postfija y devolver un vector de strings
vector<string> infixToPostfix(const string &infix)
{
    stack<char> operatorsStack;
    vector<string> postfix;
    string number;

    for (char c : infix)
    {
        if (isalnum(c) || c == '.')
        {
            number += c;
        }
        else
        {
            if (!number.empty())
            {
                postfix.push_back(number);
                number.clear();
            }
            if (c == '(')
            {
                operatorsStack.push(c);
            }
            else if (c == ')')
            {
                while (!operatorsStack.empty() && operatorsStack.top() != '(')
                {
                    postfix.push_back(string(1, operatorsStack.top()));
                    operatorsStack.pop();
                }
                if (!operatorsStack.empty())
                    operatorsStack.pop(); // Eliminar '('
            }
            else
            {
                while (!operatorsStack.empty() && precedence(operatorsStack.top()) >= precedence(c))
                {
                    postfix.push_back(string(1, operatorsStack.top()));
                    operatorsStack.pop();
                }
                operatorsStack.push(c);
            }
        }
    }

    if (!number.empty())
    {
        postfix.push_back(number);
    }

    while (!operatorsStack.empty())
    {
        postfix.push_back(string(1, operatorsStack.top()));
        operatorsStack.pop();
    }

    return postfix;
    unreachable();
}

// Funcion para evaluar la expresion ya convertida en postfija
float64_t evaluatePostfix(vector<string> &arr)
{
    stack<float64_t> pila;
    imprimirResultado = true;

    for (string token : arr)
    {

        // Si es un numero lo pushea al stack
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-'))
        {
            pila.push(stod(token));
        }
        else
        {
            float64_t valor1 = pila.top();
            pila.pop();
            double valor2 = pila.top();
            pila.pop();

            if (token == "+")
            {
                pila.push(valor2 + valor1);
            }
            else if (token == "-")
            {
                pila.push(valor2 - valor1);
            }
            else if (token == "*")
            {
                pila.push(valor2 * valor1);
            }
            else if (token == "/")
            {
                if (valor1 == 0)
                {
                    std::print(" - ERROR - No se puede dividir por cero\n");
                    imprimirResultado = false;
                    return 0;
                    unreachable();
                }
                pila.push(valor2 / valor1);
            }
            else if (token == "%")
            {
                if (valor1 == 0)
                {
                    std::print(" - ERROR - No se puede dividir por cero\n");
                    imprimirResultado = false;
                    return 0;
                    unreachable();
                }
                pila.push(fmod(valor2, valor1));
            }
            else if (token == "^")
            {
                pila.push(pow(valor2, valor1));
            }
            else
            {
                std::unreachable();
            }
        }
    }
    return pila.top();
    unreachable();
}
