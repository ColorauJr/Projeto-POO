#include "funcionario.h"

Funcionario::~Funcionario(){
    
}

string Funcionario::getTelefone(){
    return telefone;
}

string Funcionario::getDataIngresso(){
    return dataIngresso;
}

float Funcionario::getSalario(){
    return salario;
}

string Funcionario::getCodigo(){
    return codigo;
}

string Funcionario::getNome(){
    return nome;
}

string Funcionario::getEndereco(){
    return endereco;
}

string Funcionario::getCargo(){
    return cargo;
}

void Funcionario::setTelefone(string t){
    telefone = t;
}

void Funcionario::setdataIngresso(string d){
    dataIngresso = d;
}

void Funcionario::setSalario(float s){
    salario = s;
}

void Funcionario::setCodigo(string c){
    codigo = c;
}

void Funcionario::setNome(string n){
    nome = n;
}

void Funcionario::setEndereco(string e){
    endereco = e;
}

void Funcionario::setCargo(string c){
    cargo = c;
}