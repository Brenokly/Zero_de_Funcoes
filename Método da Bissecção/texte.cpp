#include <iostream>
#include <stack>
#include <cctype>
#include <cmath>
#include <unordered_map>
#include <string>

using namespace std;
using std::string;

bool ehOperador(char ch);
bool ehOperando(char ch);
int obterPrecedencia(char op);
double aplicarOperador(char op, double operando1, double operando2);
double avaliarPosfixa(const string &posfixa, const unordered_map<char, double> &valoresVariaveis);
string infixParaPosfixa(const string &infixa);

bool ehOperador(char ch)
{
  return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

bool ehOperando(char ch)
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
  cout << "Aplicando operador " << op << " em " << operando1 << " e " << operando2 << endl;
  switch (op)
  {
  case '+':
    return operando1 + operando2;
  case '-':
    return operando1 - operando2;
  case '*':
    return operando1 * operando2;
  case '/':
    return operando1 / operando2;
  case '^':
    return pow(operando1, operando2);
  default:
    return 0.0;
  }
}

string infixParaPosfixa(const string &infixa)
{
  string posfixa = "";
  stack<char> pilhaOperadores;

  for (char ch : infixa)
  {
    if (ehOperando(ch) || ch == 'e')
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
      while (isdigit(ch) || ch == '.')
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

double avaliarPosfixa(const string &posfixa, const unordered_map<char, double> &valoresVariaveis)
{
  stack<double> pilhaOperandos;

  for (size_t i = 0; i < posfixa.size(); ++i)
  {
    char ch = posfixa[i];
    if (ehOperando(ch))
    {
      // Trata operandos
      if (isalpha(ch))
      {
        if (ch == 'e')
        {
          // Se 'e' for encontrado, use a constante de Euler
          pilhaOperandos.push(exp(1.0));
        }
        else
        {
          // Se for uma variável, obtenha o valor dela da tabela de valores
          double valor = valoresVariaveis.at(ch);
          pilhaOperandos.push(valor);
        }
      }else{
        // Converte dígito para double
        string numero;
        while (isdigit(ch) || ch == '.')
        {
          numero += ch;
          ch = posfixa[++i];
        }
        --i; // Volta para o último caractere não numérico ou ponto
        pilhaOperandos.push(stod(numero));
      }
    }
    else if (ehOperador(ch))
    {
      // Trata operadores
      double operando2 = pilhaOperandos.top();
      pilhaOperandos.pop();
      double operando1 = pilhaOperandos.top();
      pilhaOperandos.pop();

      double resultado = aplicarOperador(ch, operando1, operando2);
      pilhaOperandos.push(resultado);
    }
  }

  return pilhaOperandos.top();
}

int main()
{
  // Solicita a expressão matemática do usuário
  cout << "Digite a expressao matematica: ";
  string entrada;
  getline(cin, entrada);

  // Solicita o valor de x
  cout << "Digite o valor de x: ";
  double x;
  cin >> x;

  // Mapeia o valor de x para a variável 'x' no código
  unordered_map<char, double> valoresVariaveis = {{'x', x}};

  // Converte a expressão para a forma posfixa
  string posfixa = infixParaPosfixa(entrada);
  cout << "Expressao posfixa: " << posfixa << endl;

  // Avalia a expressão posfixa com o valor de 'x'
  double resultado = avaliarPosfixa(posfixa, valoresVariaveis);
  cout << "Resultado da expressao: " << resultado << endl;

  return 0;
}
