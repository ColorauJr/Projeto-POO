#pragma once
#include "funcionario.h"

class Operador : public Funcionario{
    public:
    Operador(string tel, string data, float sal, string cod, string nom, string end, string carg);
    ~Operador();
    void informacoesAdicionais();
};