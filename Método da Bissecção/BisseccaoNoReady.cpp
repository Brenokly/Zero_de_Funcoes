#include <iostream>
#include "CalculadorNoReady.h"
using namespace std;

// M�todo da bissec��o; Zero de Fun��es

int main() {

    cout << fixed;
    cout.precision(4); //precisao de 4 casas decimaiscout << fixed;

    cout << "Entre com os valores do intervalo" << endl;
    cout << "A: ";
    double a;
    cin >> a;

    cout << "B: ";
    double b;
    cin >> b;

    cout << "Entre com a precisao  epsilon (Ex: 0.001): ";
    double epsilon;
    cin >> epsilon;

    int k = ceil((log10(abs(b - a)) - log10(epsilon)) / log10(2)) + 1;

    double x = ((a + b) / 2);
    int cont = 1;


    if ((iteracao(a, b, x, epsilon, cont, k)) == 0) {
        // solver == 1 significa que a raiz foi encontrada
        // solver == 0 significa que a raiz nao foi encontrada
        cout << "Nao foi encontrada raiz no intervalo [" << a << ", " << b << "]. Especifique melhor o intervalo ou essa fun��o nao possui intervalo!" << endl;
    }

    return 0;
}

