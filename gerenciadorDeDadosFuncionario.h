#pragma once
#include <vector>
#include "funcionario.h"

class GerenciaFuncionarios{
    private:
        vector<Funcionario*> funcionario = vector<Funcionario*>(30);
    public:
        ~GerenciaFuncionarios();
        void adicionarFuncionario(Funcionario * f);
        void editarDados(int tipo, string codigoFunc);
        void excluirRegistro(string codigoFunc);
        void exibirRegistro(string codigoFunc);
        void exibicao(int i);
        void exibirLista();
        void exibirListaPorTipo(string tipo);
        void aumento();
        vector<Funcionario*> getVectorFunc();
        void setVectorFunc(vector<Funcionario*> vec);
};