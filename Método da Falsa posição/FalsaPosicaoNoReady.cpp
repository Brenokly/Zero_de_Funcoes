#include <iostream>
#include "CalculadoraNoReady.h"
using namespace std;

// Método da bissecção; Zero de Funções

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

    cout << "Quantos vezes desejar repetir o processo de divisao? (k): ";
    int k = 0;
    cin >> k;

    double Bk = funcao(b);
    double Ak = funcao(a);

    double x = (((a * abs(Bk)) + (b * abs(Ak))) / (abs(Ak) + abs(Bk)));
    int cont = 1;


    if ((iteracao(a, b, x, epsilon, cont, k)) == 0) {
        // solver == 1 significa que a raiz foi encontrada
        // solver == 0 significa que a raiz nao foi encontrada
        cout << "Nao foi encontrada raiz no intervalo [" << a << ", " << b << "]. Especifique melhor o intervalo ou essa função nao possui intervalo!" << endl;
    }

    return 0;
}

