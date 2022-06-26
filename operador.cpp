#include "operador.h"

Operador::Operador(string tel, string data, float sal, string cod, string nom, string end, string carg){
    telefone = tel;
    dataIngresso = data;
    salario = sal;
    codigo = cod;
    nome = nom;
    endereco = end;
    cargo = carg;    
}

Operador::~Operador(){

}

void Operador::informacoesAdicionais(){
    
}