#pragma once
#include <string>

using namespace std;

class Funcionario{
    protected:
        string telefone, dataIngresso, codigo, nome, endereco, cargo;
        float salario;
    public:
        virtual ~Funcionario();
        //Método usado para imprimir dados específicos de cada tipo de funcionário
        virtual void informacoesAdicionais() = 0;
        float getSalario();
        string getTelefone();
        string getDataIngresso();
        string getCodigo();
        string getNome();
        string getEndereco();
        string getCargo();

        void setSalario(float s);
        void setTelefone(string t);
        void setdataIngresso(string d);
        void setCodigo(string c);
        void setNome(string n);
        void setEndereco(string e);
        void setCargo(string c);
};