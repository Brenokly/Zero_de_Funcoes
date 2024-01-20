#define CALCULADORA_H

#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

//Arquivo de cabeçalho

inline int peek();
inline bool ehOperador(char ch);
inline bool ehOperando(char ch);
int obterPrecedencia(char op);
double aplicarOperador(char op, double operando1, double operando2);
double avaliarPosfixa(const string& posfixa, const unordered_map<char, double>& valoresVariaveis);
string infixParaPosfixa(const string& infixa);
int Teste(double a, double b, double x, double epsilon, int cont, const int k, string& posfixa);
