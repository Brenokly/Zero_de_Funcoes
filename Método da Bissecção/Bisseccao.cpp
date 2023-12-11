#include <iostream>
#include "calculadora.h"
using namespace std;

int main()
{
	system("chcp 1252 > nul");

	cout << "Digite a expressao matem�tica: ";
	string entrada;
	getline(cin, entrada);

	cout << "Digite o valor de x: ";
	double x;
	cin >> x;

	unordered_map<char, double> valoresVariaveis = {{'x', x}};

	string posfixa = infixParaPosfixa(entrada);

	cout << "Express�o posfixa: " << posfixa << endl;

	double resultado = avaliarPosfixa(posfixa, valoresVariaveis);

	cout << "Resultado da express�o: " << resultado << endl;

	return 0;
}