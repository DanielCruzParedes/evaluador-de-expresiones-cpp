#ifndef EVALUADOR_DE_EXPRESIONES_H
#define EVALUADOR_DE_EXPRESIONES_H

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <stack>
#include <vector>
#include <expected>
#include <stdfloat>
#include <utility> 

using namespace std;

extern unordered_map<string, double> constantes;
extern bool imprimirResultado;


void obtenerConstantes();
std::expected<void, std::string> esExpresionValida(string expresion);
int precedence(char op);
vector<string> infixToPostfix(const string &infix);
float64_t evaluatePostfix(vector<string> &arr);

#endif // EVALUADOR_DE_EXPRESIONES_H
