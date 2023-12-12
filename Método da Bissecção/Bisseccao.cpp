#include <iostream>
#include "calculadora.h"
using namespace std;

int main()
{
	cout << "Digite a expressao matematica: ";
	string entrada;
	getline(cin, entrada);

	cout << "Digite o valor de x: ";
	double x;
	cin >> x;

	unordered_map<char, double> valoresVariaveis = {{'x', x}};

	string posfixa = infixParaPosfixa(entrada);

	cout << "Expressao posfixa: " << posfixa << endl;

	double resultado = avaliarPosfixa(posfixa, valoresVariaveis);

	cout << "Resultado da expressao: " << resultado << endl;

	return 0;
}