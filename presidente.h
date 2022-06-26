#pragma once
#include "funcionario.h"

class Presidente : public Funcionario{
    private:
        string areaFormacao, formacaoMaxima;
    public:
        Presidente(string tel, string data, float sal, string cod, string nom, string end, string carg, string form, string max);
        ~Presidente();
        void informacoesAdicionais();

        string getAreaFormacao();
        string getFormacaoMaxima();

        void setAreaFormacao(string a);
        void setFormacaoMaxima(string f);
};