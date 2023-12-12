#include <iostream>
#include <stack>
#include <cctype>
#include <cmath>
#include <unordered_map>
#include <string>

using namespace std;
using std::string;

inline int peek();
inline bool ehOperador(char ch);
inline bool ehOperando(char ch);
int obterPrecedencia(char op);
double aplicarOperador(char op, double operando1, double operando2);
double avaliarPosfixa(const string& posfixa, const unordered_map<char, double>& valoresVariaveis);
string infixParaPosfixa(const string& infixa);

int main(){
	cout << "Digite a expressao matematica: ";
	string expressao;
	getline(cin, expressao); // leitura da expressão

	cout << "Digite o valo de X: ";
	double x;
	cin >> x;

	cout << infixParaPosfixa(expressao) << endl;

	// Mapeia o valor de x para a variável 'x' no código
	unordered_map<char, double> valoresVariaveis = { {'x', x} };
        
    // Converte a expressão para a forma posfixa
    string posfixa = infixParaPosfixa(expressao);
    cout << "Expressao posfixa: " << posfixa << endl;

    // Avalia a expressão posfixa com o valor de 'x'
    double resultado = avaliarPosfixa(posfixa, valoresVariaveis);
    cout << "Resultado da expressao: " << resultado << endl;

	cout << endl;
		
	return 0;
}

inline int peek()
{
	int next = getchar();
	ungetc(next, stdin);
	return next;
}


inline bool ehOperador(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

inline bool ehOperando(char ch)
{
	return isalnum(ch) || ch == '_';
}

int obterPrecedencia(char op)
{
	if (op == '^')
		return 3;
	if (op == '*' || op == '/')
		return 2;
	if (op == '+' || op == '-')
		return 1;
	return 0;
}

double aplicarOperador(char op, double operando1, double operando2)
{
	switch (op)
	{
	case '+':
		return operando1 + operando2;
		break;
	case '-':
		return operando1 - operando2;
		break;
	case '*':
		return operando1 * operando2;
		break;
	case '/':
		return operando1 / operando2;
		break;
	case '^':
		return pow(operando1, operando2);
		break;
	default:
		return 0.0;
		break;
	}
}

double avaliarPosfixa(const string& posfixa, const unordered_map<char, double>& valoresVariaveis)
{
    // Cria uma pilha para armazenar operandos durante a avaliação
    stack<double> pilhaOperandos;

    // Itera através dos caracteres na expressão posfixa
    for (size_t i = 0; i < posfixa.size(); i++)
    {
        char ch = posfixa[i];

        if (ehOperando(ch))
        {
            // Se o caractere atual for um operando
            if (isalpha(ch))
            {
                // Se for uma letra, verifica se é 'e' (constante de Euler) ou uma variável
                if (ch == 'e')
                {
                    pilhaOperandos.push(exp(1.0));
                }
                else
                {
                    // Obtém o valor da variável da tabela de valores
                    double valor = valoresVariaveis.at(ch);
                    pilhaOperandos.push(valor);
                }
            }
            else
            {
                // Se for um número, converte dígito para double
                string numero;
                while (isdigit(ch) || ch == '.' && isdigit(peek()))
                {
                    numero += ch;
                    ch = posfixa[++i];
                }
                
                cout << numero << endl;

                --i; // Volta para o último caractere não numérico ou ponto
                // Converte o número para double e adiciona à pilha de operandos
                pilhaOperandos.push(stod(numero));
            }
        }
        else if (ehOperador(ch))
        {
            // Se o caractere atual for um operador
            // Pop dos operandos da pilha, aplica o operador e empurra o resultado de volta à pilha
            double operando2 = pilhaOperandos.top();
            pilhaOperandos.pop();
            double operando1 = pilhaOperandos.top();
            pilhaOperandos.pop();

            double resultado = aplicarOperador(ch, operando1, operando2);
            pilhaOperandos.push(resultado);
        }
    }

    // O resultado final estará no topo da pilha após avaliar toda a expressão
    return pilhaOperandos.top();
}


string infixParaPosfixa(const string &infixa) {
  string posfixa = "";
  stack<char> pilhaOperadores;

  for (char ch : infixa)
  {
    if (ehOperando(ch) || ch == 'e' || ch == '.')
    {
      // Se for um operando ou 'e', adiciona ao posfixa
      posfixa += ch;
    }
    else if (ehOperador(ch))
    {
      // Trata operadores
      while (!pilhaOperadores.empty() && pilhaOperadores.top() != '(' && obterPrecedencia(pilhaOperadores.top()) >= obterPrecedencia(ch))
      {
        posfixa += pilhaOperadores.top();
        pilhaOperadores.pop();
      }
      pilhaOperadores.push(ch);
    }
    else if (ch == '(')
    {
      // Abre parêntese
      pilhaOperadores.push(ch);
    }
    else if (ch == ')')
    {
      // Fecha parêntese
      while (!pilhaOperadores.empty() && pilhaOperadores.top() != '(')
      {
        posfixa += pilhaOperadores.top();
        pilhaOperadores.pop();
      }
      pilhaOperadores.pop();
    }
    else if (isdigit(ch))
    {
      // Trata números com mais de um dígito, incluindo decimais
      string numero;
	  while (isdigit(ch) || ch == '.' && isdigit(peek()))
	  {
		  numero += ch;
		  ch = getchar();
	  }
      ungetc(ch, stdin);       // Devolve o último caractere não numérico ou ponto
      posfixa += numero + ' '; // Adiciona espaço para separar os números
    }
  }

  // Adiciona operadores restantes à posfixa
  while (!pilhaOperadores.empty())
  {
    posfixa += pilhaOperadores.top();
    pilhaOperadores.pop();
  }

  return posfixa;
}