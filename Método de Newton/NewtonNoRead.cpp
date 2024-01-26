#include <iostream>
#include <functional>
#include <cmath>

// Função que deseja achar o ZERO
inline double funcao(double x) {
    return pow(x, 5) + 7.0;
}

// Derivada numérica central da função em um ponto x
inline double derivada_funcao(std::function<double(double)> f, double x, double h = 1e-5) {
    double h2 = h * 2.0;
    return (f(x + h) - f(x - h)) / h2;
}

// Função para encontrar G(x) para o método do ponto fixo
std::function<double(double)> encontrar_ponto_fixo(std::function<double(double)> f, double epsilon) {
    return [f, epsilon](double x) {
        int max_iteracoes = 1000;

        for (int i = 0; i < max_iteracoes; ++i) {
            double derivada_x = derivada_funcao(f, x);
            double x_proximo = x - f(x) / derivada_x;

            // Verificar convergência ou outras condições de parada
            if (abs(f(x_proximo)) < epsilon || abs(x_proximo - x) < epsilon) {
                return x_proximo; // Convergiu, retorna o resultado
            }

            x = x_proximo; // Atualizar para a próxima iteração
        }

        // Se atingir o número máximo de iterações sem convergir, pode retornar um valor especial ou lançar uma exceção
        return std::numeric_limits<double>::quiet_NaN(); // Exemplo: NaN para indicar falha
        };
}

int main() {
    std::function<double(double)> funcao_original = funcao;
    double epsilon = 0.0001;

    // Encontrar a função G(x) = x para o método do ponto fixo
    std::function<double(double)> funcao_ponto_fixo = encontrar_ponto_fixo(funcao_original, epsilon);

    double x_inicial = -90.2;

    // Iterações do método do ponto fixo
    double resultado = funcao_ponto_fixo(x_inicial);

    // Verificar o resultado, lidar com casos de falha, etc.
    if (!std::isnan(resultado)) {
        std::cout << "Raiz encontrada: " << resultado << std::endl;
    }
    else {
        std::cout << "O método do ponto fixo não convergiu." << std::endl;
    }

    return 0;
}
