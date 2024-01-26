#include <iostream>
#include <functional>
#include <cmath>

// Fun��o que deseja achar o ZERO
inline double funcao(double x) {
    return pow(x, 5) + 7.0;
}

// Derivada num�rica central da fun��o em um ponto x
inline double derivada_funcao(std::function<double(double)> f, double x, double h = 1e-5) {
    double h2 = h * 2.0;
    return (f(x + h) - f(x - h)) / h2;
}

// Fun��o para encontrar G(x) para o m�todo do ponto fixo
std::function<double(double)> encontrar_ponto_fixo(std::function<double(double)> f, double epsilon) {
    return [f, epsilon](double x) {
        int max_iteracoes = 1000;

        for (int i = 0; i < max_iteracoes; ++i) {
            double derivada_x = derivada_funcao(f, x);
            double x_proximo = x - f(x) / derivada_x;

            // Verificar converg�ncia ou outras condi��es de parada
            if (abs(f(x_proximo)) < epsilon || abs(x_proximo - x) < epsilon) {
                return x_proximo; // Convergiu, retorna o resultado
            }

            x = x_proximo; // Atualizar para a pr�xima itera��o
        }

        // Se atingir o n�mero m�ximo de itera��es sem convergir, pode retornar um valor especial ou lan�ar uma exce��o
        return std::numeric_limits<double>::quiet_NaN(); // Exemplo: NaN para indicar falha
        };
}

int main() {
    std::function<double(double)> funcao_original = funcao;
    double epsilon = 0.0001;

    // Encontrar a fun��o G(x) = x para o m�todo do ponto fixo
    std::function<double(double)> funcao_ponto_fixo = encontrar_ponto_fixo(funcao_original, epsilon);

    double x_inicial = -90.2;

    // Itera��es do m�todo do ponto fixo
    double resultado = funcao_ponto_fixo(x_inicial);

    // Verificar o resultado, lidar com casos de falha, etc.
    if (!std::isnan(resultado)) {
        std::cout << "Raiz encontrada: " << resultado << std::endl;
    }
    else {
        std::cout << "O m�todo do ponto fixo n�o convergiu." << std::endl;
    }

    return 0;
}
