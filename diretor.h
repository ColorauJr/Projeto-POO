#pragma once
#include "funcionario.h"

class Diretor : public Funcionario{
    private:
        string areaSupervisao, areaFormacao;
    public:
        Diretor(string tel, string data, float sal, string cod, string nom, string end, string carg, string sup, string form);
        ~Diretor();
        void informacoesAdicionais();

        string getAreaSupervisao();
        string getAreaFormacao();

        void setAreaSupervisao(string s);
        void setAreaFormacao(string f);
};