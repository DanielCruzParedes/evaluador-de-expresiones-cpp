#include "../includes/EvaluadorDeExpresiones.h"
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <stack>
#include <cmath>
#include <vector>

// C++ 23
#include <print>
#include <expected>
#include <utility> // para std::unreachable()
#include <stdfloat>

int main()
{
    obtenerConstantes();
    string expresion;

    while (true)
    {
        expresion.clear();
        print("Ingresar 'exit' para salir del programa. \n");
        print("Ingrese una expresion para ser evaluada: ");
        getline(cin, expresion);

        if (expresion == "exit")
        {
            break;
        }

        auto validacion = esExpresionValida(expresion);
        if (!validacion.has_value())
        {
            std::print(" - SYNTAX ERROR - {}\n", validacion.error());
        }
        else
        {
            // Verificar si se ingresaron variables y pedir su valor
            string nuevaExpresion;
            string variable;
            bool enVariable = false;

            for (size_t i = 0; i < expresion.size(); i++)
            {
                char c = expresion[i];

                if (isalpha(c))
                {
                    if (!enVariable)
                    {
                        variable.clear();
                        enVariable = true;
                    }
                    variable += c;
                }
                else
                {
                    if (enVariable)
                    {
                        if (constantes.find(variable) == constantes.end()) // Si no encuentra esa variable en las constantes
                        {
                            double valor;
                            cout << "Ingrese el valor de la variable " << variable << ": ";
                            cin >> valor;
                            constantes[variable] = valor;
                        }
                        nuevaExpresion += to_string(constantes[variable]);
                        enVariable = false;
                    }
                    nuevaExpresion += c;
                }
            }

            // Si quedó una variable al final
            if (enVariable)
            {
                if (constantes.find(variable) == constantes.end())
                {
                    double valor;
                    cout << "Ingrese el valor de la variable " << variable << ": ";
                    cin >> valor;
                    constantes[variable] = valor;
                }
                nuevaExpresion += to_string(constantes[variable]);
            }

            expresion = nuevaExpresion;

            vector<string> expresionPostfija = infixToPostfix(expresion);

            std::print("La expresion ingresada es: {}\n", expresion);
            std::print("La expresion en postfijo es: ");
            for (const auto &token : expresionPostfija)
            {
                std::print("{} ", token);
            }

            std::print("\n");
            double resultado = evaluatePostfix(expresionPostfija);
            if (imprimirResultado)
            {
                std::print("El resultado de la expresion es: {}\n", resultado);
                obtenerConstantes(); // Recargar las constantes
            }

            cin.clear();
            cin.ignore();
        }
    }

    return 0;
    unreachable();
}
