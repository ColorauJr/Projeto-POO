#pragma once
#include <vector>
#include "funcionario.h"

class GerenciaFolhaSalarial{
    public:
    ~GerenciaFolhaSalarial();
    void calculaFolhaMes(vector<Funcionario*> vec);
    void imprimirFolhaSalarioFuncionario(Funcionario* func);
    void imprimirFolhaSalarialEmpresa();
};