#include <iostream>
#include <functional>
#include <cmath>
using namespace std;

// Função que deseja achar o ZERO
inline double funcao(double x) {
    return pow(x, 2) - 4;
}

// Função para encontrar G(x) para o método do ponto fixo
std::function<double(double, double)> encontrar_ponto_fixo(std::function<double(double)> f, double epsilon) {
    return [f, epsilon](double x0, double x1) {
        int max_iteracoes = 1000;

        for (int i = 0; i < max_iteracoes; ++i) {
            double x_proximo = x1 - (f(x1) / ((f(x1) - f(x0)) / (x1 - x0)));

            // Verificar convergência ou outras condições de parada
            if (abs(f(x_proximo)) < epsilon || abs(x_proximo - x1) < epsilon) {
                std::cout << "Numero de iteracoes: " << i << std::endl;
                return x_proximo; // Convergiu, retorna o resultado
            }

            x0 = x1;
            x1 = x_proximo; // Atualizar para a próxima iteração
        }

        // Se atingir o número máximo de iterações sem convergir, pode retornar um valor especial ou lançar uma exceção
        return std::numeric_limits<double>::quiet_NaN(); // Exemplo: NaN para indicar falha
        };
}

int main() {
    std::function<double(double)> funcao_original = funcao;
    double epsilon = 0.0001;

    // Encontrar a função G(x) = x para o método do ponto fixo
    std::function<double(double, double)> funcao_ponto_fixo = encontrar_ponto_fixo(funcao_original, epsilon);

    double x1 = 12.0;
    double x2 = 14.0;

    // Iterações do método do ponto fixo
    double resultado = funcao_ponto_fixo(x1,x2);

    // Verificar o resultado, lidar com casos de falha, etc.
    if (!std::isnan(resultado)) {
        std::cout << "Raiz encontrada: " << resultado << std::endl;
    }
    else {
        std::cout << "O método do ponto fixo não convergiu." << std::endl;
    }

    return 0;
}
