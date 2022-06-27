# Bem-vindo à wiki do projeto!

Aqui teremos a descrição das classes e métodos mais importantes, referentes à primeira nota do projeto para a disciplina de Linguagem de Programação I (um salve ao professor Marcelo).

## Diagrama de classes

![Imagem do diagrama de classes](https://github.com/ColorauJr/Projeto-POO/blob/main/Diagrama.drawio.png)

## Classes
### Funcionario
**Funcionario** é a classe núcleo de todo o projeto, usada para fins de polimorfismo a fim de criar objetos para manipular dados de funcionários, tendo como variáveis: "nome", "codigo", "telefone", "endereco", "cargo" e "dataIngresso" do tipo string e "salario" do tipo float.

#### Métodos importantes

##### void informacoesAdicionais()

Método virtual puro do tipo void criado para tornar a classe abstrata, usado pelas subclasses para imprimir os dados específicos de cada cargo de um funcionário.

### Operador
Subclasse de **Funcionario**, representa o cargo de operador. Não apresenta informações adicionais, dado que é o cargo mais baixo entre todos. Sendo assim, o método _informacoesAdicionais()_ nesta classe é implementado, mas sem finalidade.

### Gerente
Subclasse de **Funcionario**, representa o cargo de gerente. Possui a variável "areaSupervisao" do tipo string, exibidas pelo método _informacoesAdicionais()_.

#### Métodos importantes

##### void informacoesAdicionais()

Método para exibir os dados exclusivos da classe **Gerente**.

```
void Gerente::informacoesAdicionais(){
    cout << "Área de supervisão: " + getAreaSupervisao() + ".\n";
}
```


### Diretor
Subclasse de **Funcionario**, representa o cargo de diretor. Possui as variáveis "areaSupervisao" e "areaFormacao" do tipo string, exibidas pelo método _informacoesAdicionais()_.

#### Métodos importantes

##### void informacoesAdicionais()

Método para exibir os dados exclusivos da classe **Diretor**.

```
void Diretor::informacoesAdicionais(){
    cout << "Área de supervisão: " + getAreaSupervisao() + ".\nÁrea de formação: " + getAreaFormacao() + ".\n";
}
```

### Presidente
Subclasse de **Funcionario**, representa o cargo de presidente. Possui as variáveis "areaFormacao" e "formacaoMaxima" do tipo string, exibidas pelo método _informacoesAdicionais()_.

#### Métodos importantes

##### void informacoesAdicionais()

Método para exibir os dados exclusivos da classe **Presidente**.

```
void Presidente::informacoesAdicionais(){
    cout << "Área de formação: " + getAreaFormacao() + ".\nFormação máxima: " + getFormacaoMaxima() + ".\n";
}
```

### GerenciaFuncionarios
Classe responsável pela manipulação de dados dos funcionários cadastrados. Armazena em um vector do tipo **Funcionario*** todos os objetos criados das subclasses de **Funcionario** para alterar, excluir, adicionar ou exibir os dados de cada objeto que representa um funcionário.

#### Métodos importantes

##### void adicionarFuncionario(Funcionario* func)
Método do tipo void com um parâmetro do tipo **Funcionario*** que adiciona um novo objeto de subclasses de **Funcionario** no vector da classe GerenciaFuncionario.

```
void GerenciaFuncionarios::adicionarFuncionario(Funcionario * func){
    funcionario.push_back(func);
    cout << "\nFuncionario adicionado com êxito.\n";
}
```
##### void editarDados(int tipo, string codigoFunc)
Método do tipo void com um parâmetro do tipo int e um do tipo string que edita um dado (com base no tipo de dado escolhido através do parâmetro int) de um dos objetos do vector (definido pelo código passado como parâmetro string).

```
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
```
##### void excluirRegistro(string codigoFunc)
Método do tipo void com um parâmetro do tipo string que exclui um objeto do vector da classe (com base no código passado como parâmetro).

```
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
```
##### void exibicao(int i)
Método do tipo void com um parâmetro do tipo inteiro. Exibe o registro de um funcionário de acordo com a posição do objeto no vector da classe passada como parâmetro. Feito para evitar repetição de código.

```
void GerenciaFuncionarios::exibicao(int i){
    cout << funcionario[i]->getCodigo() << ": " << funcionario[i]->getNome() << ", " << funcionario[i]->getCargo() << ".\nSalário: R$";
    cout << funcionario[i]->getSalario() << ".\nData de ingresso: " << funcionario[i]->getDataIngresso() << endl;

    if(funcionario[i]->getCargo() == "gerente" || funcionario[i]->getCargo() == "diretor" || funcionario[i]->getCargo() == "presidente"){
        funcionario[i]->informacoesAdicionais();
    }

    cout << "Endereço: " << funcionario[i]->getEndereco() << endl << "Telefone: " << funcionario[i]->getTelefone() << endl << endl;

}
``` 
##### void exibirRegistro(string codigoFunc)
Método do tipo void com um parâmetro do tipo string. Exibe o registro de um funcionário com base no código passado como parâmetro. Verifica a variável "codigo" dos objetos do vector da classe e compara com o parâmetro passado, e caso sejam iguais, o método _exibicao(int i)_ é chamado.

```
void GerenciaFuncionarios::exibirRegistro(string codigoFunc){
    for(int i = 0; i < funcionario.size(); i++){
        if(codigoFunc == funcionario[i]->getCodigo()){
           exibicao(i);
           break;
        }
    }
}
```
##### void exibirLista()
Método do tipo void. Exibe uma lista de todos os funcionários presentes no vector da classe através de um for com o método _exibicao(int i)_.

```
void GerenciaFuncionarios::exibirLista(){
    for(int i = 0; i < funcionario.size(); i++){
        exibicao(i);
    }
}
```
##### void exibirListaPorTipo(string tipo)
Método do tipo void que possui uma parâmetro do tipo string. Exibe uma lista de funcionários de um determinado cargo. O cargo digitado é passado como parâmetro e é feito a comparação com a variável "cargo" de cada objeto do vector, exibindo através do método _exibicao(int i)_ aqueles que tiverem o cargo igual ao do parâmetro.

```
void GerenciaFuncionarios::exibirListaPorTipo(string tipo){
    for(int i = 0; i < funcionario.size(); i++){
        if(funcionario[i]->getCargo() == tipo){
            exibicao(i);
        }
    }
}
```
##### void aumento()
Método do tipo void. Realiza o aumento no salário dos funcionários com base no cargo. Dentro de um for, é utilizado outro for para definir o valor da variável "j" através do comparativo de uma lista que possui os nomes dos cargos com a variável "cargo" (passada pelo getVector()) de um objeto. O valor da variável "j" direcionará para a operação de aumento referente ao cargo do funcionário.

```
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
```

### GerenciaFolhaSalarial
Classe responsável por calcular e exibir as folhas salariais da empresa e dos funcionários, além de salvar os valores calculados em arquivos.

#### Funções importantes

##### float calcularImpostoDeRenda(float base)
Função do tipo float com um parâmetro do tipo float. Realiza o cálculo do imposto utilizando constantes pré-definidas e um valor base, passado como parâmetro, retornando o valor do imposto.

```
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
```
##### float calcularINSS(float base)
Função do tipo float com um parâmetro do tipo float. Realiza o cálculo do imposto utilizando constantes pré-definidas e um valor base, passado como parâmetro, retornando o valor do imposto.

```
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
```

#### Métodos importantes

##### void calculaFolhaMes(vector<Funcionario*> vec)
Método do tipo void com um parâmetro do tipo vector<Funcionario*>. Calcula todos os dados financeiros da empresa referente aos funcionários, utilizando o vector passado como parâmetro, e salva os dados em arquivo após efetuar os cálculos de cada funcionário. Faz uso das funções _calcularImpostodeRenda(float base)_ e _calcularINSS(float base)_.

```
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
```

##### void imprimirFolhaSalarialFuncionario(Funcionario* func)
Método do tipo void com um parâmetro do tipo **Funcionario***. Imprime um contracheque de um funcionário utilizando o objeto passado como parâmetro para o método acessar seus dados, solicitando o mês a ser imprimido e utilizando o arquivo para recuperar os dados a serem exibidos.

```
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
```
##### void imprimirFolhaSalarialEmpresa()
Método do tipo void. Solicita o tipo de folha a ser calculada: mensal ou anual. Caso seja mensal, será solicitado o mês. Assim, será calculada a folha com base nas condições desejadas, recuperando os dados do arquivo e realizando um somatório para cada dado. Por fim, é exibida a folha.

```
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
```
