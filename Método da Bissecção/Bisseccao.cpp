#include "calculadora.h"

int main() {
    cout << "Digite a expressao matematica: ";
    string expressao;
    getline(cin, expressao); // leitura da expressão

    cout << fixed;
    cout.precision(4);//precisao de 4 casas decimaiscout << fixed;

    // Converte a expressão para a forma posfixa
    string posfixa = infixParaPosfixa(expressao);
    cout << "Expressao posfixa: " << posfixa << endl;

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

    cout << "K = " << k << endl;

    double x = ((a + b) / 2);
    int cont = 1;


    if ((Teste(a, b, x, epsilon, cont, k, posfixa)) == 0) {
        // solver == 1 significa que a raiz foi encontrada
        // solver == 0 significa que a raiz nao foi encontrada
        cout << "Nao foi encontrada raiz no intervalo [" << a << ", " << b << "]. Especifique melhor o intervalo ou essa função nao possui intervalo!" << endl;
    }

    return 0;
}