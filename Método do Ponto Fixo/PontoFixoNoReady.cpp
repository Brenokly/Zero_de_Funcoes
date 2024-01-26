#include <iostream>
#include <cmath>
#include <limits>
#include <functional>

// Função original
inline double funcao_original(double x) {
    return pow(x,3) - x - 1; 
}

// Função de iteração
inline double phi(double x) {
    return cbrt(x+1); //raiz cúbica de x + 1 || Aqui é a função phi tal que F(phi) = 0 <-> G(phi) = phi
}

// Método do Ponto Fixo
double metodo_ponto_fixo(std::function<double(double)> phi,std::function<double(double)> funcao, double x_inicial, double epsilon) {
    int max_iteracoes = 1000;

    for (int i = 0; i < max_iteracoes; ++i) {
        double x_proximo = phi(x_inicial);

        // Verificar convergência ou outras condições de parada
        if (abs(x_proximo - x_inicial) < epsilon || abs(funcao(x_proximo)) < epsilon) {
            std::cout << "Numero de iteracoes: " << i << std::endl;
            return x_proximo; // Convergiu, retorna o resultado
        }

        x_inicial = x_proximo; // Atualizar para a próxima iteração
    }

    // Se atingir o número máximo de iterações sem convergir, pode retornar um valor especial ou lançar uma exceção
    return std::numeric_limits<double>::quiet_NaN(); // Exemplo: NaN para indicar falha
}

int main() {
    double epsilon = 0.0001;
    double x_inicial = 4214; // Escolha um valor inicial adequado

    // Aplicar o Método do Ponto Fixo
    double resultado = metodo_ponto_fixo(phi, funcao_original, x_inicial, epsilon);

    // Verificar o resultado, lidar com casos de falha, etc.
    if (!std::isnan(resultado)) {
        std::cout << "Raiz encontrada: " << resultado << std::endl;
    }
    else {
        std::cout << "O Método do Ponto Fixo não convergiu." << std::endl;
    }

    return 0;
}
