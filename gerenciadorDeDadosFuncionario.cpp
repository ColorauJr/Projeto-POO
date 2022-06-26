#include "CEPendereco.h"
#include "gerenciadorDeDadosFuncionario.h"
#include "operador.h"
#include "gerente.h"
#include "diretor.h"
#include "presidente.h"
#include <iostream>

/*Destrutor que apaga todo o vector do objeto desta classe*/
GerenciaFuncionarios::~GerenciaFuncionarios(){
    for(int i = 0; i < funcionario.size(); i++){
        delete funcionario[i];
    }
}

//Adiciona funcionário no vector da classe
void GerenciaFuncionarios::adicionarFuncionario(Funcionario * func){
    funcionario.push_back(func);
    cout << "\nFuncionario adicionado com êxito.\n";
}

//Edita o dado de registro escolhido de um funcionário solicitado através de seu código
void GerenciaFuncionarios::editarDados(int tipo, string codigoFunc){
    
    //"i" será utilizada num for para definir seu valor, a fim de definir o funcionário que terá os dados alterados através do switch
    int i;

    //O for é usado para comparar o código digitado com os códigos dos funcionários presentes no vector,
    for(i = 0; i < funcionario.size(); i++){
        if(codigoFunc == funcionario[i]->getCodigo()){
            break;
        }
    }


    switch(tipo){
        case 1:{
            string telefone;
            cout << "Digite o telefone:\n";
            getline(cin, telefone);
            funcionario[i]->setTelefone(telefone);
            break;
        }
        case 2:{
            string data;
            cout << "Digite a data em modelo numérico. Use barras:\n";
            getline(cin, data);
            funcionario[i]->setdataIngresso(data);
            break;
        }
        case 3:{
            float salario;
            cout << "Digite o salario:\n";
            cin >> salario;
            funcionario[i]->setSalario(salario);
            break;
        }
        case 4:{
            string codigo;
            cout << "Digite o código:\n";
            getline(cin, codigo);
            funcionario[i]->setCodigo(codigo);
            break;
        }
        case 5:{
            string nome;
            cout << "Digite o nome:\n";
            getline(cin, nome);
            funcionario[i]->setNome(nome);
            break;
        }
        case 6:{
            string cep;
            cout << "Digite o CEP sem hífen:\n";
            getline(cin, cep);
            funcionario[i]->setEndereco(getEnderecoPeloCep(cep));
            break;
        }
        /*No case 7, não só o nome do cargo será alterado, como também o tipo de objeto do elemento "i" do vector do gerenciador*/
        case 7:{
            string cargo;
            cout << "Digite o cargo:\n";
            getline(cin, cargo);
            
            string designacao[4] = {"operador", "gerente", "diretor", "presidente"};
            
            int j;
            //Compara a variavel com os elementos do vetor para usar o valor de "j" no próximo switch
            for(j = 1; i <= 4; i++){
                if(cargo == designacao[j-1]){
                    break;
                }
            }

            /*Todas essas variáveis serão usadas para construir um novo objeto, usando os elementos do atual*/
            Funcionario * func;
            float salario = funcionario[i]->getSalario();
            string telefone = funcionario[i]->getTelefone(), dataIngresso = funcionario[i]->getDataIngresso();
            string codigo = funcionario[i]->getCodigo(), nome = funcionario[i]->getNome(), endereco = funcionario[i]->getEndereco();

            /*Dependendo do objeto construído, outras variáveis precisarão ser adicionadas. O switch realiza a construção dependendo
            do caso digitado*/
            switch(j){
                case 1:{
                    func = new Operador(telefone, dataIngresso, salario, codigo, nome, endereco, cargo);
                    break;
                }
                case 2:{
                    string areaSupervisao;
                    
                    /*Como os objetos do tipo "diretor" já possuem a variável areaSupervisao, ela é reaproveitada aqui. Caso
                    seja de outro tipo, é necessário digitá-la para adicionar e alterar o objeto*/
                    if(funcionario[i]->getCargo() == "diretor")
                        areaSupervisao = ((Diretor*)funcionario[i])->getAreaSupervisao();
                    else{
                        cout << "\nDigite a área de supervisão do funcionário:\n";
                        getline(cin, areaSupervisao);
                    }

                    func = new Gerente(telefone, dataIngresso, salario, codigo, nome, endereco, cargo, areaSupervisao);
                    break;
                }
                case 3:{
                    string areaSupervisao, areaFormacao;

                    /*Como os objetos do tipo "gerente" já possuem a variável areaSupervisao, ela é reaproveitada aqui. Caso
                    seja de outro tipo, é necessário digitá-la para adicionar e alterar o objeto*/
                    if(funcionario[i]->getCargo() == "gerente")
                        areaSupervisao = ((Gerente*)funcionario[i])->getAreaSupervisao();
                    else{
                        cout << "\nDigite a área de supervisão do funcionário:\n";
                        getline(cin, areaSupervisao);
                    }
                    /*Como os objetos do tipo "presidente" já possuem a variável areaFormacao, ela é reaproveitada aqui. Caso
                    seja de outro tipo, é necessário digitá-la para adicionar e alterar o objeto*/
                    if(funcionario[i]->getCargo() == "presidente")
                        areaFormacao = ((Presidente*)funcionario[i])->getAreaFormacao();
                    else{
                        cout << "\nDigite a área de formação do funcionário:\n";
                        getline(cin, areaFormacao);
                    }
    
                    func = new Diretor(telefone, dataIngresso, salario, codigo, nome, endereco, cargo, areaSupervisao, areaFormacao);
                    break;
                }
                case 4:{
                    string areaFormacao, formacaoMaxima;

                    /*Como os objetos do tipo "diretor" já possuem a variável areaFormacao, ela é reaproveitada aqui. Caso
                    seja de outro tipo, é necessário digitá-la para adicionar e alterar o objeto*/
                    if(funcionario[i]->getCargo() == "diretor")
                        areaFormacao = ((Diretor*)funcionario[i])->getAreaFormacao();
                    else{
                        cout << "\nDigite a área de formação do funcionário:\n";
                        getline(cin, areaFormacao);
                    }

                    cout << "\nDigite a formação máxima do funcionário:\n";
                    getline(cin, formacaoMaxima);

                    func = new Presidente(telefone, dataIngresso, salario, codigo, nome, endereco, cargo, areaFormacao, formacaoMaxima);
                    break;
                }
            }
            funcionario[i] = func;
            break;
        }
        case 8:{
            return;
        }
        default:{
            cout << "\nOpção inválida\n";
            return;
        }
            
    }
    cout << "Dado alterado.\n";
}

void GerenciaFuncionarios::excluirRegistro(string codigoFunc){
    
    //"i" terá seu valor definido neste for e será usado para conferir a validade do código do funcionário
    int i;
    //O for é usado para comparar o código digitado com os códigos dos funcionários presentes no vector
    for(i = 0; i < funcionario.size(); i++){
        if(codigoFunc == funcionario[i]->getCodigo()){
            break;
        }
    }
    if(i == funcionario.size()){
        cout << "\nCódigo inválido\n";
        return;
    }
    if(funcionario[i]->getCargo() == "diretor" || funcionario[i]->getCargo() == "presidente"){
        cout << "\nExclusão não permitida.\n";
        return;
    }
    int perguntar;
    cout << "Confirme a exclusão deste fucnionário.\nDigite 1 para excluir. Use qualquer outra tecla para cancelar.\n";
    cin >> perguntar;

    if(perguntar == 1){
        funcionario.erase(funcionario.begin() + i);
        cout << "\nExclusão efetuada com sucesso.\n";
    }else{
        cout << "\nExclusão cancelada.\n";
    }
}

/*Método feito pra evitar repetição de código, utilizado em três métodos a seguir e na parte de buscas*/
void GerenciaFuncionarios::exibicao(int i){
    cout << funcionario[i]->getCodigo() << ": " << funcionario[i]->getNome() << ", " << funcionario[i]->getCargo() << ".\nSalário: R$";
    cout << funcionario[i]->getSalario() << ".\nData de ingresso: " << funcionario[i]->getDataIngresso() << endl;

    if(funcionario[i]->getCargo() == "gerente" || funcionario[i]->getCargo() == "diretor" || funcionario[i]->getCargo() == "presidente"){
        funcionario[i]->informacoesAdicionais();
    }

    cout << "Endereço: " << funcionario[i]->getEndereco() << endl << "Telefone: " << funcionario[i]->getTelefone() << endl << endl;

}

/*Usa uma string que armazena um código de funcionário e imprime os dados do funcionário ao qual pertence o
código através do método exibicao(i)*/
void GerenciaFuncionarios::exibirRegistro(string codigoFunc){
    for(int i = 0; i < funcionario.size(); i++){
        if(codigoFunc == funcionario[i]->getCodigo()){
           exibicao(i);
           break;
        }
    }
}

//Exibe toda a lista de funcionários presentes no vector através do método exibicao(i)
void GerenciaFuncionarios::exibirLista(){
    for(int i = 0; i < funcionario.size(); i++){
        exibicao(i);
    }
}

//Exibe todos os funcionários de um determinado cargo presentes no vector através do método exibicao(i)
void GerenciaFuncionarios::exibirListaPorTipo(string tipo){
    for(int i = 0; i < funcionario.size(); i++){
        if(funcionario[i]->getCargo() == tipo){
            exibicao(i);
        }
    }
}

//Realiza o aumento na variável de salário de cada objeto do vector, tendo uma porcentagem de aumento definida com base no cargo
void GerenciaFuncionarios::aumento(){
    for(int i = 0; i < funcionario.size(); i++){
        int j;
        string cargo = funcionario[i]->getCargo();
        string designacao[4] = {"operador", "gerente", "diretor", "presidente"};
        for(j = 1; j <= 4; j++){
            if(cargo == designacao[j-1]){
                break;
            }
        }
        switch(j){
            case 1:{//OPERADOR
                funcionario[i]->setSalario(funcionario[i]->getSalario()*1.05);
                break;
            }
            case 2:{//GERENTE
                funcionario[i]->setSalario(funcionario[i]->getSalario()*1.1);
                break;
            }
            case 3:{//DIRETOR
                funcionario[i]->setSalario(funcionario[i]->getSalario()*1.2);
                break;
            }
            case 4:{//PRESIDENTE
                funcionario[i]->setSalario(funcionario[i]->getSalario()*1.3);
                break;
            }
        }    
    }
    cout << "\nAumento efetuado com sucesso.\n";
}

vector<Funcionario*> GerenciaFuncionarios::getVectorFunc(){
    return funcionario;
}

void GerenciaFuncionarios::setVectorFunc(vector<Funcionario*> vec){
    funcionario = vec;
}