#include <iostream>
#include "calculadora.h"
using namespace std;

int main()
{
	system("chcp 1252 > nul");

	cout << "Digite a expressao matemática: ";
	string entrada;
	getline(cin, entrada);

	cout << "Digite o valor de x: ";
	double x;
	cin >> x;

	unordered_map<char, double> valoresVariaveis = {{'x', x}};

	string posfixa = infixParaPosfixa(entrada);

	cout << "Expressão posfixa: " << posfixa << endl;

	double resultado = avaliarPosfixa(posfixa, valoresVariaveis);

	cout << "Resultado da expressão: " << resultado << endl;

	return 0;
}