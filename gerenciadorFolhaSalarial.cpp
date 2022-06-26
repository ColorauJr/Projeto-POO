#include "gerenciadorFolhaSalarial.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

/*A seguir, temos todas as constantes usadas no cálculo de INSS e imposto de renda*/
#define VALOR_MAX_FAIXA1_INSS 1212.00
#define VALOR_MAX_FAIXA2_INSS 2427.35
#define VALOR_MAX_FAIXA3_INSS 3641.03
#define VALOR_MAX_FAIXA4_INSS 7087.22
#define PERCENTUAL_FAIXA1_INSS 0.075
#define PERCENTUAL_FAIXA2_INSS 0.09
#define PERCENTUAL_FAIXA3_INSS 0.12
#define PERCENTUAL_FAIXA4_INSS 0.14
#define VALOR_MAX_FAIXA1_IR 2500.00
#define VALOR_MAX_FAIXA2_IR 3200.00
#define VALOR_MAX_FAIXA3_IR 4250.00
#define VALOR_MAX_FAIXA4_IR 5300.00
#define PERCENTUAL_FAIXA2_IR 0.075
#define PERCENTUAL_FAIXA3_IR 0.15
#define PERCENTUAL_FAIXA4_IR 0.225
#define PERCENTUAL_FAIXA5_IR 0.275

GerenciaFolhaSalarial::~GerenciaFolhaSalarial(){
    
}



//Realiza o cálculo de imposto de renda usando uma base calculada no método calculaFolhaMes(), utilizando as constantes definidas anteriormente
float calcularImpostoDeRenda(float base){
    float imposto;

    if(base <= VALOR_MAX_FAIXA1_IR){
        imposto = 0;
    }
    if(base >= VALOR_MAX_FAIXA1_IR + 0.01 && base <= VALOR_MAX_FAIXA2_IR){
        imposto = base*PERCENTUAL_FAIXA2_IR;
    }
    if(base >= VALOR_MAX_FAIXA2_IR + 0.01 && base <= VALOR_MAX_FAIXA3_IR){
        imposto = base*PERCENTUAL_FAIXA3_IR;
    }
    if(base >= VALOR_MAX_FAIXA3_IR + 0.01 && base <= VALOR_MAX_FAIXA4_IR){
        imposto = base*PERCENTUAL_FAIXA4_IR;
    }
    if(base >= VALOR_MAX_FAIXA4_IR + 0.01){
        imposto = base*PERCENTUAL_FAIXA5_IR;
    }

    return imposto;
}

//Realiza o cálculo do INSS usando uma base calculada no método calculaFolhaMes(), utilizando as constantes definidas anteriormente
float calcularINSS(float base){
    float imposto;
    float faixa1 = VALOR_MAX_FAIXA1_INSS * PERCENTUAL_FAIXA1_INSS;
    float faixa2 = (VALOR_MAX_FAIXA2_INSS - VALOR_MAX_FAIXA1_INSS) * PERCENTUAL_FAIXA2_INSS;
    float faixa3 = (VALOR_MAX_FAIXA3_INSS - VALOR_MAX_FAIXA2_INSS) * PERCENTUAL_FAIXA3_INSS;
    float faixa4 = (VALOR_MAX_FAIXA4_INSS - VALOR_MAX_FAIXA3_INSS) * PERCENTUAL_FAIXA4_INSS;

    if(base <= VALOR_MAX_FAIXA1_INSS){
        imposto = base*PERCENTUAL_FAIXA1_INSS;
    }
    if(base >= VALOR_MAX_FAIXA1_INSS + 0.01 && base <= VALOR_MAX_FAIXA2_INSS){
        imposto =  faixa1 + (base - VALOR_MAX_FAIXA1_INSS)*PERCENTUAL_FAIXA2_INSS;
    }
    if(base >= VALOR_MAX_FAIXA2_INSS + 0.01 && base <= VALOR_MAX_FAIXA3_INSS){
        imposto = faixa1 + faixa2 + (base - VALOR_MAX_FAIXA2_INSS)*PERCENTUAL_FAIXA3_INSS;
    }
    if(base >= VALOR_MAX_FAIXA3_INSS + 0.01 && base <= VALOR_MAX_FAIXA4_INSS){
        imposto = faixa1 + faixa2 + faixa3 + (base - VALOR_MAX_FAIXA3_INSS)*PERCENTUAL_FAIXA4_INSS;
    }
    if(base >= VALOR_MAX_FAIXA4_INSS + 0.01){
        imposto = faixa1 + faixa2 + faixa3 + faixa4;
    }

    return imposto;
}

/*Calcula a folha salarial usando os dados dos objetos do vector que armazena os funcionários*/
void GerenciaFolhaSalarial::calculaFolhaMes(vector<Funcionario*> vec){
    fstream fs;
    //nomeMes receberá o nome do mês ao qual é relacionado o número digitado pelo usuário
    string nomeMes;
    //folha receberá todo o conteúdo do arquivo para procurar o nome do mês solicitado a fim de descobrir se a folha deste mês já foi calculada
    string folha;
    int numMes;
    string meses[12]{"janeiro", "fevereiro", "março", "abril", "maio", "junho", "julho", "agosto", "setembro", "outubro", "novembro", "dezembro"};

    cout << "\nDigite o número do mês a ser calculado:\n";
    cin >> numMes;
    cin.ignore();
    
    if(numMes > 12 || numMes < 1){
        throw "\nMês inválido.\n";
    }
    /*O nome do mês a ser calculado será armazenado aqui, se utilizando do array definido no início para defini-lo*/
    nomeMes = meses[numMes-1];
    
    fs.open("folhasCalculadas.txt", fstream::in);
    if(!fs.is_open()){
        throw "\nErro ao abrir arquivo.\n";
    }
    /*Todo o conteúdo do arquivo será armazenado numa string, a fim de procurar o nome do mês solicitado para descobrir 
    se a folha do mês já foi calculada*/
    while(!fs.eof()){
        string novaLinha = "";
        getline(fs, novaLinha);
        folha = folha + novaLinha;
    }

    fs.close();
    fs.open("folhasCalculadas.txt", fstream::out|fstream::app);

    if(folha.find(nomeMes) != string::npos){
        cout << "\nFolha Salarial deste mês já foi calculada.\n";
        return;                        
    }
    /*Este é o for que realiza os cálculos de todas as informações para cada funcionário cadastrado*/
    for(int i = 0; i < vec.size(); i++){
        string data = vec[i]->getDataIngresso();//usada para dar valor a duas variáveis a seguir
        int diaData, mesData, anoData;
        diaData = stoi(data.substr(0, 2));
        mesData = stoi(data.substr(3, 2));
        anoData = stoi(data.substr(6, 4));
        int diasUteisMes[12]{21, 20, 23, 19, 22, 22, 21, 23, 21, 20, 20, 22};//array de dias úteis em cada mês (2022)
        int diasNaoUteisMes[12]{10, 8, 8, 11, 9, 8, 10, 8, 9, 11, 10, 9};//array de dias não-úteis em cada mês (2022)
        int diasTrabalhados = diasUteisMes[numMes-1];
        int horasTrabalhadas = 220;
        
        /*Confere a data de ingresso do funcionário. Se entrou após o mês a ser calculado, o loop pula para a próxima iteração*/
        if(mesData > numMes && anoData >= 2022){
            continue;
        }
        if(mesData == numMes && anoData >= 2022){
            diasTrabalhados = diasUteisMes[numMes-1]+diasNaoUteisMes[numMes-1] - diaData;
            horasTrabalhadas = diasTrabalhados*8;
        }

        int qtddHorasExtras = rand()%21;
        float percentualHoraExtra = 2;//(100% do valor da hora + 100% da hora extra)/100, pra facilitar um cálculo a seguir

        float salarioBruto = vec[i]->getSalario();
        float valorTotalHoraExtra = (salarioBruto/220)*percentualHoraExtra*qtddHorasExtras;//220 é o valor referência de horas trabalhadas no mês
        
        
        float dsr = valorTotalHoraExtra*diasNaoUteisMes[numMes-1]/diasUteisMes[numMes-1];
        float salarioTotal = salarioBruto + valorTotalHoraExtra + dsr;

        float inss = calcularINSS(salarioTotal);//salarioTotal serve como base para o cálculo do INSS
        float baseImpostoDeRenda = salarioTotal - inss;
        float impostoDeRenda = calcularImpostoDeRenda(baseImpostoDeRenda);

        float salarioLiquido = salarioTotal - impostoDeRenda - inss;
        float fgts = salarioTotal*0.08;

        //O nome do mês será escrito apenas no início, para definir início e término das folhas calculadas no arquivo
        if(i == 0){
            fs << nomeMes << endl;
        }
        fs << vec[i]->getNome() << endl;
        fs << vec[i]->getCargo() << endl;
        fs << salarioBruto << endl;
        fs << horasTrabalhadas << endl;
        fs << qtddHorasExtras << endl;
        fs << valorTotalHoraExtra << endl;
        fs << dsr << endl;
        fs << inss << endl;
        fs << impostoDeRenda << endl;
        fs << salarioTotal << endl;//Serve também como valor base do INSS
        fs << baseImpostoDeRenda << endl;
        fs << inss + impostoDeRenda << endl;//Total de descontos
        fs << salarioLiquido << endl;
        fs << fgts << endl; 
    }

    cout << "\nFolha Salarial calculada com êxito.\n";
    fs.close();
}

/*Imprime a folha salarial de um funcionário que tem o objeto com seus dados passado como parâmetro*/
void GerenciaFolhaSalarial::imprimirFolhaSalarioFuncionario(Funcionario* func){
    int numMes;
    string meses[12]{"janeiro", "fevereiro", "março", "abril", "maio", "junho", "julho", "agosto", "setembro", "outubro", "novembro", "dezembro"};
    int horasTrabalhadas, qtddHorasExtras;
    string mes, procuraMes, procuraFunc, lerDadoString, nome, cargo;
    float lerDadoFloat, salarioBruto, valorTotalHoraExtra, dsr, inss, impostoDeRenda, salarioTotal, baseInss;
    float baseImpostoDeRenda, totalDeDescontos, salarioLiquido, fgts;
    //Variável a ser usada no for pra comparar com o contador, relativa à quantidade de dados a serem lidos neste método
    int qtddDados = 15;

    cout << "\nDigite o número do mês:\n";
    cin >> numMes;
    cin.ignore();

    if(numMes > 12 || numMes < 1){
        throw "Mês inválido.\n";
    }
    mes = meses[numMes-1];

    fstream fs;
    fs.open("folhasCalculadas.txt", fstream::in);

    while(!fs.eof()){
        /*As linhas do arquivo serão lidas a fim de encontrar o mês solicitado*/
        getline(fs, procuraMes);
        if(procuraMes == mes){
            /*Após o mês ser encontrado, será iniciado outro while. Este será encerrado quando o nome de outro mês
            for lido, ou quando o próximo break for chamado*/
            while(procuraFunc != meses[0] && procuraFunc != meses[1] && procuraFunc != meses[2] && procuraFunc != meses[3] && procuraFunc != meses[4]
            && procuraFunc != meses[5] && procuraFunc != meses[6] && procuraFunc != meses[7] && procuraFunc != meses[8] && procuraFunc != meses[9]
            && procuraFunc != meses[10] && procuraFunc != meses[11]){
                
                /*O nome do funcionário será procurado a partir daqui. Caso encontrado, os dados seguintes do arquivo
                serão armazenados em variáveis, de acordo com os if's dentro do for*/
                getline(fs, procuraFunc);
                
                if(procuraFunc == func->getNome()){
                    nome = procuraFunc;

                    /*i = 1 pois nome já foi armazenado, qtddDados-1 pois dois dados serão escritos num mesmo if*/
                    for(int i = 1; i < qtddDados-1; i++){
                        if(i==1){
                            getline(fs, lerDadoString);
                            cargo = lerDadoString;
                        }else{
                            fs >> lerDadoFloat;
                            fs.ignore();
                        }
                        if(i==2)
                            salarioBruto = lerDadoFloat;
                        if(i==3)
                            horasTrabalhadas = lerDadoFloat;
                        if(i==4)
                            qtddHorasExtras = lerDadoFloat;
                        if(i==5)
                            valorTotalHoraExtra = lerDadoFloat;
                        if(i==6)
                            dsr = lerDadoFloat;
                        if(i==7)
                            inss = lerDadoFloat;
                        if(i==8)
                            impostoDeRenda = lerDadoFloat;
                        if(i==9){
                            salarioTotal = lerDadoFloat;
                            baseInss = salarioTotal;
                        }
                        if(i==10)
                            baseImpostoDeRenda = lerDadoFloat;
                        if(i==11)
                            totalDeDescontos = lerDadoFloat;
                        if(i==12)
                            salarioLiquido = lerDadoFloat;
                        if(i==13)
                            fgts = lerDadoFloat;
                    }
                    break;
                }
            }
        }
    }

    fs.close();
    /*Se o funcionário não for encontrado, "procuraFunc" sairá dos loops com o nome de um mês. Sendo assim, este if...else verifica se 
    "procuraFunc" tem o nome de um mês e imprime um aviso se o funcionário não foi encontrado. Se não, imprime o contracheque*/
    if(procuraFunc == meses[0] || procuraFunc == meses[1] || procuraFunc == meses[2] || procuraFunc == meses[3] || procuraFunc == meses[4]
    || procuraFunc == meses[5] || procuraFunc == meses[6] || procuraFunc == meses[7] || procuraFunc == meses[8] || procuraFunc == meses[9]
    || procuraFunc == meses[10] || procuraFunc == meses[11]){
        cout << "\nFuncionário não estava em serviço neste mês.\n";
    }else{
        //código da exibição
        cout << fixed << setprecision(2);
        cout << "\nContracheque do mês de junho" << endl << endl;
        cout << "Funcionário: " << nome << endl;
        cout << "Cargo: " << cargo << endl << endl;
        cout << " ---------------------------------------------------------------------------" << endl;
        cout << "             Descrição         //    Ref    //  Vencimentos  //   Descontos" << endl;
        cout << "   Salário                     // " << horasTrabalhadas << " horas // R$ " << salarioBruto << "    //" << endl;
        cout << "   Horas Extraordinárias       //   " << qtddHorasExtras << "      // R$ " << valorTotalHoraExtra <<"     //" << endl;
        cout << "   DSR - Horas Extraordinárias //     --    // R$ " << dsr << "    //" << endl;
        cout << "   INSS                        //     --    //      --     //  R$ " << inss << endl;
        cout << "   IRRF                        //     --    //     --     //  R$ " << impostoDeRenda << endl;
        cout << " ---------------------------------------------------------------------------" << endl;
        cout << "                      Total de Vencimentos    //    Total de Descontos"<< endl;
        cout << "                           R$ " << salarioTotal << "        //         R$ " << totalDeDescontos << endl << endl << endl;
        cout << "                      Valor líquido: R$" << salarioLiquido << endl;
        cout << " ---------------------------------------------------------------------------" << endl;
        cout << "Salário base: R$ "<< salarioBruto << "     Base INSS: R$ " << baseInss << "    Base IRRF: R$ " << baseImpostoDeRenda << endl;
        cout << "FGTS: R$ " << fgts << "     Dependentes: 00" << endl << endl;
    }
}

void GerenciaFolhaSalarial::imprimirFolhaSalarialEmpresa(){
    string meses[12]{"janeiro", "fevereiro", "março", "abril", "maio", "junho", "julho", "agosto", "setembro", "outubro", "novembro", "dezembro"};
    string lerDado;
    float salarioTotal = 0, totalDeDescontos = 0, fgts = 0;
    //Armazena os dados convertidos de string para float, sendo usada no somatório de cada informação da folha
    float converteToFloat;
    //Variável a ser usada no for pra comparar com o contador, relativa à quantidade de tipos de dados presente no arquivo
    int qtddDados = 15;
    float lerDadoFloat;

    fstream fs;
    fs.open("folhasCalculadas.txt", fstream::in);
    
    
    int tipo;
    cout << "\nSelecione o tipo de Folha Salarial a ser imprimida:\n";
    cout << " 1 - mensal\n";
    cout << " 2 - anual\n";
    cout << " 3 - voltar\n";
    cin >> tipo;
    cin.ignore();

    switch (tipo){
        case 1:{//MENSAL
            string mes, procuraMes;
            int numMes;
            cout << "\nDigite o número do mês:\n";
            cin >> numMes;
            cin.ignore();

            if(numMes > 12 || numMes < 1){
                throw "Mês inválido.\n";
            }
            
            mes = meses[numMes-1];
            //cont é usada a fim de impedir que o getline usado para encontrar o mês no arquivo continue a operar após encontrá-lo
            int cont = 0;
            
            while(!fs.eof() && (lerDado != meses[0] && lerDado != meses[1] && lerDado != meses[2] && lerDado != meses[3] && lerDado != meses[4]
            && lerDado != meses[5] && lerDado != meses[6] && lerDado != meses[7] && lerDado != meses[8] && lerDado != meses[9]
                && lerDado != meses[10] && lerDado != meses[11])){
                
                if(cont == 0){
                    getline(fs, procuraMes);
                }
                
                if(procuraMes == mes){    
                    ++cont;
                    while(lerDado != meses[0] && lerDado != meses[1] && lerDado != meses[2] && lerDado != meses[3] && lerDado != meses[4]
                    && lerDado != meses[5] && lerDado != meses[6] && lerDado != meses[7] && lerDado != meses[8] && lerDado != meses[9]
                    && lerDado != meses[10] && lerDado != meses[11]){
                        
                        for(int i = 0; i < qtddDados-1; i++){
                            
                            getline(fs, lerDado);
                            if(fs.eof()){
                            break;
                            }
                            //Se lerDado ler o nome de um mês, irá encerrar os loops
                            if(lerDado == meses[0] || lerDado == meses[1] || lerDado == meses[2] || lerDado == meses[3] || lerDado == meses[4]
                            || lerDado == meses[5] || lerDado == meses[6] || lerDado == meses[7] || lerDado == meses[8] || lerDado == meses[9]
                            || lerDado == meses[10] || lerDado == meses[11]){
                                break;
                            }
                            if(i==9){
                                converteToFloat = stof(lerDado);
                                salarioTotal = salarioTotal + converteToFloat;
                            }
                                
                            if(i==11){
                                converteToFloat = stof(lerDado);
                                totalDeDescontos = totalDeDescontos + converteToFloat;
                            }
                            if(i==13){
                                converteToFloat = stof(lerDado);
                                fgts = fgts + converteToFloat;
                            }
                        }
                    }
                }
            }
            fs.close();
            cout << "\nFolha Salarial mensal:";
            break;
        }
        case 2:{//ANUAL
             while(!fs.eof()){
                    
                for(int i = 0; i < qtddDados-1; i++){
                    getline(fs, lerDado);
                    if(fs.eof()){
                        break;
                    }
                    //Encerra os loops se lerDado for o nome de um mês
                    if(lerDado == meses[0] || lerDado == meses[1] || lerDado == meses[2] || lerDado == meses[3] || lerDado == meses[4]
                    || lerDado == meses[5] || lerDado == meses[6] || lerDado == meses[7] || lerDado == meses[8] || lerDado == meses[9]
                    || lerDado == meses[10] || lerDado == meses[11]){
                        break;
                    }
                    if(i==9){
                        converteToFloat = stof(lerDado);
                        salarioTotal = salarioTotal + converteToFloat;
                    }
                        
                    if(i==11){
                        converteToFloat = stof(lerDado);
                        totalDeDescontos = totalDeDescontos + converteToFloat;
                    }
                    if(i==13){
                        converteToFloat = stof(lerDado);
                        fgts = fgts + converteToFloat;
                    }
                }
            }
            fs.close();
            cout << "\nFolha Salarial anual:";
            break;
        }
        case 3:{
            return;
        }
        default:
            cout << "\nOpção inválida.\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nCustos de funcionários:\n\n";
    cout << "Salários e vencimentos: R$ " << salarioTotal << endl;
    cout << "Impostos de funcionários: R$ " << totalDeDescontos << endl;
    cout << "FGTS: R$ " << fgts << endl << endl;
}