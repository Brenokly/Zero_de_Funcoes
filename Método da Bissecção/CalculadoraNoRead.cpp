#include <iostream>
#include <cmath>
#include "CalculadoraNoRead.h"
using namespace std;

inline double funcao(double x) {
    return pow(x, 3) - x;           // Aqui você define a função que quiser!
}

int iteracao(double a, double b, double x, double epsilon, int cont, int k) {
    double Xk = funcao(x);
    double Ak = funcao(a);
    double Bk = funcao(b);

    if (abs(Xk) < epsilon || abs(Xk - x) < epsilon) {
        cout << "Raiz encontrada: [F(" << x << ")] = " << Xk << "]" << endl;
        return 1;
    }
    if (cont > k) {
        cout << cont << ": Ultrapassou as " << k << " Interações!" << endl;
        return 0;
    }

    if (abs(Ak) < epsilon) {
        cout << "Raiz encontrada: [F(" << a << ")] = " << Ak << "]" << endl;
        if (abs(Bk) < epsilon) {
            cout << "Raiz encontrada: [F(" << b << ")] = " << Bk << "]" << endl;
        }
        return 1;
    }

    if ((Ak * Xk) < 0) {
        b = x;
        x = ((a + x) / 2);
        return iteracao(a, b, x, epsilon, cont + 1, k);
    }


    if ((Bk * Xk) < 0) {
        a = x;
        x = ((b + x) / 2);
        return iteracao(a, b, x, epsilon, cont + 1, k);
    }

    return 0;
}