#include "presidente.h"
#include <iostream>

Presidente::Presidente(string tel, string data, float sal, string cod, string nom, string end, string carg, string form, string max){
    telefone = tel;
    dataIngresso = data;
    salario = sal;
    codigo = cod;
    nome = nom;
    endereco = end;
    cargo = carg; 
    areaFormacao = form;
    formacaoMaxima = max;
}

Presidente::~Presidente(){
    
}

void Presidente::informacoesAdicionais(){
    cout << "Área de formação: " + getAreaFormacao() + ".\nFormação máxima: " + getFormacaoMaxima() + ".\n";
}

string Presidente::getAreaFormacao(){
    return areaFormacao;
}

string Presidente::getFormacaoMaxima(){
    return formacaoMaxima;
}

void Presidente::setAreaFormacao(string a){
    areaFormacao = a;
}

void Presidente::setFormacaoMaxima(string f){
    formacaoMaxima = f;
}