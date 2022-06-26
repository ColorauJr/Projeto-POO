#include "gerente.h"
#include <iostream>

Gerente::Gerente(string tel, string data, float sal, string cod, string nom, string end, string carg, string sup){
    telefone = tel;
    dataIngresso = data;
    salario = sal;
    codigo = cod;
    nome = nom;
    endereco = end;
    cargo = carg;
    areaSupervisao = sup; 
}

Gerente::~Gerente(){
    
}

void Gerente::informacoesAdicionais(){
    cout << "Área de supervisão: " + getAreaSupervisao() + ".\n";
}


string Gerente::getAreaSupervisao(){
    return areaSupervisao;
}

void Gerente::setAreaSupervisao(string a){
    areaSupervisao = a;
}