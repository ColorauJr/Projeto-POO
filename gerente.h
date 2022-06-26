#pragma once
#include "funcionario.h"

class Gerente : public Funcionario{
    private:
        string areaSupervisao;
    public:
        Gerente(string tel, string data, float sal, string cod, string nom, string end, string carg, string sup);
        ~Gerente();
        void informacoesAdicionais();
        string getAreaSupervisao();
        void setAreaSupervisao(string a);
};