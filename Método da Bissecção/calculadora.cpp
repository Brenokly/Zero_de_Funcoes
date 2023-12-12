#include "calculadora.h"
#include <stack>
#include <cctype>
#include <cmath>

bool ehOperador(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

bool ehOperando(char ch)
{
    return std::isalnum(ch) || ch == '_';
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
    case '-':
        return operando1 - operando2;
    case '*':
        return operando1 * operando2;
    case '/':
        return operando1 / operando2;
    case '^':
        return std::pow(operando1, operando2);
    default:
        return 0.0;
    }
}

std::string infixParaPosfixa(const std::string &infixa)
{
    std::string posfixa = "";
    std::stack<char> pilhaOperadores;

    for (char ch : infixa)
    {
        if (ehOperando(ch))
        {
            posfixa += ch;
        }
        else if (ehOperador(ch))
        {
            while (!pilhaOperadores.empty() && pilhaOperadores.top() != '(' && obterPrecedencia(pilhaOperadores.top()) >= obterPrecedencia(ch))
            {
                posfixa += pilhaOperadores.top();
                pilhaOperadores.pop();
            }
            pilhaOperadores.push(ch);
        }
        else if (ch == '(')
        {
            pilhaOperadores.push(ch);
        }
        else if (ch == ')')
        {
            while (!pilhaOperadores.empty() && pilhaOperadores.top() != '(')
            {
                posfixa += pilhaOperadores.top();
                pilhaOperadores.pop();
            }
            pilhaOperadores.pop();
        }
    }

    while (!pilhaOperadores.empty())
    {
        posfixa += pilhaOperadores.top();
        pilhaOperadores.pop();
    }

    return posfixa;
}

double avaliarPosfixa(const std::string &posfixa, const std::unordered_map<char, double> &valoresVariaveis)
{
    std::stack<double> pilhaOperandos;

    for (char ch : posfixa)
    {
        if (ehOperando(ch))
        {
            if (std::isalpha(ch))
            {
                double valor = valoresVariaveis.at(ch);
                pilhaOperandos.push(valor);
            }
            else
            {
                // Converte dígito para double
                double operando = ch - '0';
                pilhaOperandos.push(operando);
            }
        }
        else if (ehOperador(ch))
        {
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