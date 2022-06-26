#include "operador.h"
#include "gerente.h"
#include "diretor.h"
#include "presidente.h"
#include "CEPendereco.h"
#include "gerenciadorDeDadosFuncionario.h"
#include "gerenciadorFolhaSalarial.h"
#include <iostream>
#include <fstream>
#include <Windows.h>

//Função para salvar os dados em arquivo usando fstream e um vector de um objeto da classe GerenciaFuncinario
void salvarArquivoFuncionarios(vector<Funcionario *> func) {
    fstream fs;
    fs.open("dadosFuncionarios.txt", fstream::out);
    if(!fs.is_open()) {
        cout << "Erro ao abrir arquivo para escrita\n";
        return;
    }
    for(int i = 0; i < func.size(); i++){
        fs << func[i]->getCodigo() << endl;
        fs << func[i]->getNome() << endl;
        fs << func[i]->getCargo() << endl;
        fs << func[i]->getDataIngresso() << endl;
        fs << func[i]->getSalario() << endl;
        fs << func[i]->getTelefone() << endl;
        fs << func[i]->getEndereco() << endl;

        if(func[i]->getCargo() == "gerente"){
            fs << ((Gerente*)func[i])->getAreaSupervisao() << endl;
        }
        if(func[i]->getCargo() == "diretor"){
            fs << ((Diretor*)func[i])->getAreaSupervisao() << endl;
            fs << ((Diretor*)func[i])->getAreaFormacao() << endl;
        }
        if(func[i]->getCargo() == "presidente"){
            fs << ((Presidente*)func[i])->getAreaFormacao() << endl;
            fs << ((Presidente*)func[i])->getFormacaoMaxima() << endl;
        }
        
    }
    fs.close();
}

/*Função para ler dados de um arquivo e usaá-los para criar objetos, colocando estes num vector*/
vector<Funcionario*> lerArquivoFuncionarios() {
    vector<Funcionario *> func;
    Funcionario *f;
    fstream fs;
    string nome, codigo, endereco, telefone, dataIngresso, cargo;
    string areaSupervisao, areaFormacao, formacaoMaxima;
    float salario;

    fs.open("dadosFuncionarios.txt", fstream::in);
    if (!fs.is_open()) {
        cout << "Erro ao abrir arquivo para leitura\n";
        return func;
    }

    while (!fs.eof()) {
        getline(fs, codigo);
        if (fs.eof())//Evita bug de leitura e escrita de código
            break;
        getline(fs, nome);
        getline(fs, cargo);
        getline(fs, dataIngresso);
        fs >> salario;
        fs.ignore();
        getline(fs, telefone);
        getline(fs, endereco);

        /*Criação de objetos com base nos cargos lidos*/
        if(cargo == "gerente") {
            getline(fs, areaSupervisao);
            f = new Gerente(telefone, dataIngresso, salario, codigo, nome, endereco, cargo, areaSupervisao);
            ((Gerente*)f)->setAreaSupervisao(areaSupervisao);
        }else if(cargo == "diretor"){
            getline(fs, areaSupervisao);
            getline(fs, areaFormacao);
            f = new Diretor(telefone, dataIngresso, salario, codigo, nome, endereco, cargo, areaSupervisao, areaFormacao);
            ((Diretor*)f)->setAreaSupervisao(areaSupervisao);
            ((Diretor*)f)->setAreaFormacao(areaFormacao);
        }else if (cargo == "presidente"){
            getline(fs, areaFormacao);
            getline(fs, formacaoMaxima);
            f = new Presidente(telefone, dataIngresso, salario, codigo, nome, endereco, cargo, areaFormacao, formacaoMaxima);
            ((Presidente*)f)->setAreaFormacao(areaFormacao);
            ((Presidente*)f)->setFormacaoMaxima(formacaoMaxima);
        }else{
            f = new Operador(telefone, dataIngresso, salario, codigo, nome, endereco, cargo);
        }
        f->setCodigo(codigo);
        f->setNome(nome);
        f->setCargo(cargo);
        f->setdataIngresso(dataIngresso);
        f->setSalario(salario);
        f->setTelefone(telefone);
        f->setEndereco(endereco);
        func.push_back(f);
    }
    fs.close();
    return func;
}

/*Função que abriga os requisitos propostos de funcionários, o parametro opcao é usado para definir 
qual atividade será realizada através do switch, usando um objeto da classe GerenciaFuncionarios
definido na função main, e passado como parâmetro, para acessar os métodos de cada caso*/
void opcoesFuncionario(int opcao, GerenciaFuncionarios gerencia){
    
    switch(opcao){
        case 1:{//ADICIONAR FUNCIONARIO
            int i;
            string cargo;
            string designacao[4] = {"operador", "gerente", "diretor", "presidente"};
            cout << "\nDigite o cargo do funcionário:\n";
            getline(cin, cargo);

            /*Compara a variavel com os elementos do vetor para usar o valor de "i" no próximo switch, 
            a fim de definir qual será o objeto construído*/
            for(i = 1; i <= 4; i++){
                if(cargo == designacao[i-1]){
                    break;
                }
            }
            //Caso o for termine e a variável "cargo" não tenha o nome de um dos quatro cargos do array, o case encerrará
            if(i == 4 && cargo != "presidente"){
                cout << "\nCargo inválido.\n";
                break;
            }

            string telefone, dataIngresso, codigo, nome, cep, endereco;
            float salario;

            cout << "\nDigite o nome do funcionário:\n";
            getline(cin, nome);
            cout << "\nDigite o código do funcionário:\n";
            getline(cin, codigo);
            cout << "\nDigite o CEP sem hífen):\n";
            getline(cin, cep);
            endereco = getEnderecoPeloCep(cep);
            cout << "\nDigite o telefone do funcionário:\n";
            getline(cin, telefone);
            cout << "\nDigite a data de ingresso do funcionário (modelo numérico. Insira também as barras):\n";
            getline(cin, dataIngresso);
            cout << "\nDigite o salário do funcionário:\n";
            cin >> salario;
            cin.ignore();

            
            Funcionario * funcionario;

            switch(i){//Criação do objeto com base em seu cargo
                case 1:{
                    funcionario = new Operador(telefone, dataIngresso, salario, codigo, nome, endereco, cargo);
                    break;
                }
                case 2:{
                    string areaSupervisao;
                    cout << "\nDigite a área de supervisão do funcionário:\n";
                    getline(cin, areaSupervisao);
                    funcionario = new Gerente(telefone, dataIngresso, salario, codigo, nome, endereco, cargo, areaSupervisao);
                    break;
                }
                case 3:{
                    string areaSupervisao, areaFormacao;
                    cout << "\nDigite a área de supervisão do funcionário:\n";
                    getline(cin, areaSupervisao);
                    cout << "\nDigite a área de formação do funcionário:\n";
                    getline(cin, areaFormacao);
                    funcionario = new Diretor(telefone, dataIngresso, salario, codigo, nome, endereco, cargo, areaSupervisao, areaFormacao);
                    break;
                }
                case 4:{
                    string areaFormacao, formacaoMaxima;
                    cout << "\nDigite a área de formação do funcionário:\n";
                    getline(cin, areaFormacao);
                    cout << "\nDigite a formação máxima do funcionário:\n";
                    getline(cin, formacaoMaxima);
                    funcionario = new Presidente(telefone, dataIngresso, salario, codigo, nome, endereco, cargo, areaFormacao, formacaoMaxima);
                    break;
                }
            }
            /*Método do objeto da classe GerenciaFuncionarios, passado como parâmetro. 
            O objeto da classe Funcionario é passado como parâmetro e é adicionado no vector de "gerencia"*/
            gerencia.adicionarFuncionario(funcionario);
            cout << "\nFuncionario adicionado com êxito.\n";
            system("pause");
            break;
        }
        case 2:{//EDITAR DADOS
            string codigoFunc;
            int tipo;
            cout << "\nDigite o código do funcionário:\n";
            getline(cin, codigoFunc);
            
            /*O for é usado para comparar o código digitado com os códigos dos funcionários presentes no vector,
            e "i" será usado tanto neste for como num if a seguir*/
            int i;
            vector<Funcionario*> comparar = gerencia.getVectorFunc();
            for(i = 0; i < comparar.size(); i++){
                if(codigoFunc == comparar[i]->getCodigo()){
                    break;
                }
            }

            //i será igual ao tamanho do vetor caso não encontre nenhum código de funcionário igual ao digitado
            if(i == comparar.size()){
                cout << "\nCódigo inválido.\n";
                break;
            }
            cout << "Digite o número do tipo de dado que deseja editar:\n";
            cout << " 1 - telefone\n";
            cout << " 2 - data de ingresso\n";
            cout << " 3 - salário\n";
            cout << " 4 - código\n";
            cout << " 5 - nome\n";
            cout << " 6 - endereço\n";
            cout << " 7 - cargo\n";
            cout << " 8 - voltar\n";
            cin >> tipo;
            cin.ignore();
            system("cls");
            //Método de "gerencia" que realiza a edição do dado usando o tipo e o código digitados
            gerencia.editarDados(tipo, codigoFunc);
            system("pause");
            break;
        }
        case 3:{//EXCLUIR REGISTRO
            string codigoFunc;
            cout << "\nDigite o código do funcionário a ser excluído:\n";
            getline(cin, codigoFunc);
            gerencia.excluirRegistro(codigoFunc);
            system("pause");
            break;
        }
        case 4:{//EXIBIR REGISTRO DE UM FUNCIONÁRIO
            string codigoFunc;
            cout << "\nDigite o código do funcionário a ser exibido:\n";
            getline(cin, codigoFunc);
            gerencia.exibirRegistro(codigoFunc);
            system("pause");
            break;
        }
        case 5:{//EXIBIR LISTA
            gerencia.exibirLista();
            system("pause");
            break;
        }
        case 6:{//EXIBIR LISTA POR TIPO
            string tipo;
            cout << "\nDigite o cargo desejado:\n";
            getline(cin, tipo);
            gerencia.exibirListaPorTipo(tipo);
            system("pause");
            break;
        }
        case 7:{//AUMENTO
            gerencia.aumento();
            system("pause");
            break;
        }
        case 8:{//VOLTAR
            break;
        }
        default:{
            cout << "\nOpção inválida\n";
            system("pause");
        }
    }
    /*A função de save é chamada aqui, e atualiza o arquivo com os dados editados na função atual*/
    salvarArquivoFuncionarios(gerencia.getVectorFunc());
    system("cls");
}



/*Função que abriga os requisitos propostos da folha salarial, o parametro opcao é usado para definir 
qual atividade será realizada através do switch, usando um vector passado como parâmetro nos métodos a seguir*/
void opcoesFolhaSalarial(int opcao, vector<Funcionario*> func){

    /*Este objeto é responsável pelos métodos de cálculo e impressão da folha salarial*/
    GerenciaFolhaSalarial gerenciadorFolha;
    
    switch(opcao){
        case 1:{//CALCULAR FOLHA SALARIAL DO MÊS SOLICITADO
            try{
                gerenciadorFolha.calculaFolhaMes(func);;
            }catch(const char * e){
                cout << e << endl;
            }
            system("pause");
            break;
        }
        case 2:{//IMPRIMIR FOLHA SALARIAL DE UM FUNCIONÁRIO
            string info;
            cout << "\nDigite o código ou nome completo do funcionário:\n";
            getline(cin, info);

            /*Neste for, há um if...else que verifica se a informação passada coresponde a um dos dados do vector passado
            como parâmetro. Se houver, o método é executado*/
            for(int i = 0; i < func.size(); i++){
                
                if(func[i]->getCodigo().find(info) != string::npos || func[i]-> getNome().find(info) != string::npos){
                    try{
                        gerenciadorFolha.imprimirFolhaSalarioFuncionario(func[i]);
                    }catch(const char * e){
                        cout << e << endl;
                    }
                    break;
                    
                }else if(i+1 == func.size()){
                    cout << "Nenhum funcionário encontrado." << endl;
                }
            }
            system("pause");
            break;
        }
        case 3:{//IMPRIMIR FOLHA SALARIAL DA EMPRESA
            try{
                gerenciadorFolha.imprimirFolhaSalarialEmpresa();
            }catch(const char * e){
                cout << e << endl;
            }
            system("pause");
            
            break;
        }
        case 4:{
            break;
        }
        default:{
            cout << "\nOpção inválida\n";
            system("pause");
        }
    }
    system("cls");
}



/*Função que abriga os tipos de busca de funcionário propostos, o parametro tipo é usado para definir 
qual busca será realizada através do switch, usando um objeto da classe GerenciaFuncionarios
definido na função main, e passado como parâmetro, para utilizar seu vector e seu método de exibição*/
void buscaFuncionario(int tipo, GerenciaFuncionarios gerencia){

    vector<Funcionario*> comparador = gerencia.getVectorFunc();

    
    int find = 0;
    switch(tipo){
        case 1:{//BUSCA POR NOME
            string nome;
            cout << "\nDigite o nome a ser buscado:\n";
            getline(cin, nome);
            cout << endl;

            /*Neste for, há um if...else que verifica se a informação passada coresponde a um dos dados do vector
            passado como parâmetro. Se houver, o método é executado*/
            for(int i = 0; i < comparador.size(); i++){
                
                if(comparador[i]->getNome().find(nome) != string::npos){
                    gerencia.exibicao(i);
                    find = find + 1;
                    
                }else if(find == 0 && i+1 == comparador.size()){
                    cout << "Nenhum funcionário encontrado." << endl;
                }
            }
            system("pause");
            break;
        }
        /*Neste caso são solicitadas duas datas: uma inicial e uma final, a fim de estabelecerem um intervalo. É feito um cálculo
        usando pesos para o ano e o mês a fim de gerar valores que serão bem mais fáceis para a máquina comparar do que usando
        instruções com base no ano e mês originais*/
        case 2:{//BUSCA POR DATA
            int d, m, a, dataInicial, dataFinal, pesoAno = 10000, pesoMes = 100;
            cout << "\nInsira o intervalo de datas";
            cout << "\nDigite o dia da data inicial:\n";
            cin >> d;
            cout << "\nDigite o mês da data inicial:\n";
            cin >> m;
            cout << "\nDigite o ano da data inicial:\n";
            cin >> a;
            dataInicial = a*pesoAno + m*pesoMes + d;
            cout << "\nDigite o dia da data final:\n";
            cin >> d;
            cout << "\nDigite o mês da data final:\n";
            cin >> m;
            cout << "\nDigite o ano da data final:\n";
            cin >> a;
            cin.ignore();
            dataFinal = a*pesoAno + m*pesoMes + d;
            cout << endl;

            /*Neste for, a data de um funcionário é transformada num valor usando os pesos citados, e este é comparado com 
            os valores calculados das datas limites do intervalo. Se estiver dentro do intervalo, o método de exibição é executado*/
            for(int i = 0; i < comparador.size(); i++){
                string dataIngresso = comparador[i]->getDataIngresso();
                int diaDataIngresso, mesDataIngresso, anoDataIngresso, dataFunc;
                diaDataIngresso = stoi(dataIngresso.substr(0, 2));
                mesDataIngresso = stoi(dataIngresso.substr(3, 2));
                anoDataIngresso = stoi(dataIngresso.substr(6, 4));
                dataFunc = anoDataIngresso*pesoAno + mesDataIngresso*pesoMes + diaDataIngresso;
                
                if(dataFunc >= dataInicial && dataFunc <= dataFinal){
                    gerencia.exibicao(i);
                    ++find;
                }else if (find == 0){
                    cout << "Nenhum Funcionario encontrado." << endl;
                }
            }
            system("pause");
            break;
        }
        case 3:{//BUSCA POR ENDEREÇO
            string endereco;
            cout << "\nDigite uma informação do endereço a ser buscado (CEP, nome ou sigla do estado):\n";
            getline(cin, endereco);
            cout << endl;

            for(int i = 0; i < comparador.size(); i++){
                
                if(comparador[i]->getEndereco().find(endereco) != string::npos){
                    gerencia.exibicao(i);
                    find = find + 1;
                    
                }else if(find == 0 && i+1 == comparador.size()){
                    cout << "Nenhum funcionário encontrado." << endl;
                }
            }
            system("pause");
            break;
        }
        case 4:{
            break;
        }
        default:{
            cout << "\nOpção inválida.\n";
            system("pause");
        }
    }
    system("cls");
}

int main(){
    SetConsoleOutputCP(CP_UTF8);//Torna possível o uso de caracteres especiais

    /*Objeto passado como parâmetro nas funções e responsável por armazenar os dados dos funcionários 
    durante o funcionamento do programa*/
    GerenciaFuncionarios gerenciadorFunc;
    int opcao = 0;
    /*O vector do objeto é definido através da leitura de arquivo*/
    gerenciadorFunc.setVectorFunc(lerArquivoFuncionarios());

    while(opcao !=4){
        cout << "\nEscolha uma opção:\n";
        cout << " 1 - Funcionários\n";
        cout << " 2 - Folha Salarial\n";
        cout << " 3 - Busca\n";
        cout << " 4 - Encerrar\n";
        cin >> opcao;
        cin.ignore();
        system("cls");

        switch(opcao){
            case 1:{ //OPÇÕES DE FUNCIONARIO
                int opcao1 = 0;
                while(opcao1 != 8){
                    cout << "\nEscolha uma opção:\n";
                    cout << " 1 - Adicionar funcionário\n";
                    cout << " 2 - Editar dados de um funcionário\n";
                    cout << " 3 - Excluir registro de um funcionário\n";
                    cout << " 4 - Exibir registro de um funcionário\n";
                    cout << " 5 - Exibir lista de funcionários\n";
                    cout << " 6 - Exibir lista de funcionários por cargo\n";
                    cout << " 7 - Conceder aumento para os funcionários\n";
                    cout << " 8 - Voltar\n";
                    cin >> opcao1;
                    cin.ignore();
                    system("cls");
                    opcoesFuncionario(opcao1, gerenciadorFunc);
                    /*O vector precisa ser atualizado após a função anterior ser executada*/
                    gerenciadorFunc.setVectorFunc(lerArquivoFuncionarios());
                }
                break;
            }
            case 2:{//OPÇÕES DE FOLHA SALARIAL
                int opcao2 = 0;
                while(opcao2 != 4){
                    cout << "\nEscolha uma opção:\n";
                    cout << " 1 - Calcular Folha Salarial\n";
                    cout << " 2 - Imprimir contracheque de um funcionário\n";
                    cout << " 3 - Imprimir Folha Salarial da empresa\n";
                    cout << " 4 - Voltar\n";
                    cin >> opcao2;
                    cin.ignore();
                    system("cls");
                    opcoesFolhaSalarial(opcao2, gerenciadorFunc.getVectorFunc());
                }
                break;
            }
            case 3:{//FERRAMENTA DE BUSCA
                int tipo = 0;
                while(tipo != 4){
                    cout << "\nEscolha uma opção:\n";
                    cout << " 1 - Busca por nome\n";
                    cout << " 2 - Busca por data de ingresso\n";
                    cout << " 3 - Busca por endereço\n";
                    cout << " 4 - Voltar\n";
                    cin >> tipo;
                    cin.ignore();
                    system("cls");
                    buscaFuncionario(tipo, gerenciadorFunc);
                }
                break;
            }
            case 4:{//SAIR
                break;
            }
            default:{
                cout << "\nOpção inválida\n";
                system("pause");
            }
        }
    }

    system("cls");
    cout << "\nPrograma encerrado." << endl << endl;

    return 0;
}