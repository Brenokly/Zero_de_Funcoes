#ifndef CALCULADORA_H
#define CALCULADORA_H

#include <string>
#include <unordered_map>

//Arquivo de cabeçalho

bool ehOperador(char ch);
bool ehOperando(char ch);
int obterPrecedencia(char op);
double aplicarOperador(char op, double operando1, double operando2);
double avaliarPosfixa(const std::string &posfixa, const std::unordered_map<char, double> &valoresVariaveis);
std::string infixParaPosfixa(const std::string &infixa);

#endif // CALCULADORA_H