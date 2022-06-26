#include "diretor.h"
#include <iostream>

Diretor::Diretor(string tel, string data, float sal, string cod, string nom, string end, string carg, string sup, string form){
    telefone = tel;
    dataIngresso = data;
    salario = sal;
    codigo = cod;
    nome = nom;
    endereco = end;
    cargo = carg;
    areaSupervisao = sup; 
    areaFormacao = form;
}

Diretor::~Diretor(){
    
}

void Diretor::informacoesAdicionais(){
    cout << "Área de supervisão: " + getAreaSupervisao() + ".\nÁrea de formação: " + getAreaFormacao() + ".\n";
}

string Diretor::getAreaSupervisao(){
    return areaSupervisao;
}

string Diretor::getAreaFormacao(){
    return areaFormacao;
}

void Diretor::setAreaSupervisao(string s){
    areaSupervisao = s;
}

void Diretor::setAreaFormacao(string f){
    areaFormacao = f;
}