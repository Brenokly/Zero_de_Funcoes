#include <iostream>
#include <cmath>
#include <limits>
#include <functional>

// Fun��o original
inline double funcao_original(double x) {
    return pow(x,3) - x - 1; 
}

// Fun��o de itera��o
inline double phi(double x) {
    return cbrt(x+1); //raiz c�bica de x + 1 || Aqui � a fun��o phi tal que F(phi) = 0 <-> G(phi) = phi
}

// M�todo do Ponto Fixo
double metodo_ponto_fixo(std::function<double(double)> phi,std::function<double(double)> funcao, double x_inicial, double epsilon) {
    int max_iteracoes = 1000;

    for (int i = 0; i < max_iteracoes; ++i) {
        double x_proximo = phi(x_inicial);

        // Verificar converg�ncia ou outras condi��es de parada
        if (abs(x_proximo - x_inicial) < epsilon || abs(funcao(x_proximo)) < epsilon) {
            std::cout << "Numero de iteracoes: " << i << std::endl;
            return x_proximo; // Convergiu, retorna o resultado
        }

        x_inicial = x_proximo; // Atualizar para a pr�xima itera��o
    }

    // Se atingir o n�mero m�ximo de itera��es sem convergir, pode retornar um valor especial ou lan�ar uma exce��o
    return std::numeric_limits<double>::quiet_NaN(); // Exemplo: NaN para indicar falha
}

int main() {
    double epsilon = 0.0001;
    double x_inicial = 4214; // Escolha um valor inicial adequado

    // Aplicar o M�todo do Ponto Fixo
    double resultado = metodo_ponto_fixo(phi, funcao_original, x_inicial, epsilon);

    // Verificar o resultado, lidar com casos de falha, etc.
    if (!std::isnan(resultado)) {
        std::cout << "Raiz encontrada: " << resultado << std::endl;
    }
    else {
        std::cout << "O M�todo do Ponto Fixo n�o convergiu." << std::endl;
    }

    return 0;
}
