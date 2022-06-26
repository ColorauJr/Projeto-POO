#include <iostream>
#include <fstream>
#include <string>
#include "CEPendereco.h"

using namespace std;

/*Função que solicita um CEP a fim de obter suas informações pela internet, armazená-las num arquivo e passar o conteúdo
para uma string que definirá um endereço*/
string getEnderecoPeloCep(string cep){
    
    string url;

    /*Variável que será passada na linha de comando para baixar o arquivo da url de acordo com o CEP digitado*/
    url = "https://viacep.com.br/ws/" + cep + "/json/";

    /*Instrução passada para o sistema: o Wget será chamado para salvar um arquivo com as informações do json da url*/
    system(("wget -q -O cep.txt " + url).c_str());

    string json, rua, complemento, bairro, cidade, estado;
    fstream fs;
    
    /*"i" representará as linhas do arquivo dentro do while*/
    int i = 0;

    fs.open("cep.txt", fstream::in);
    if(fs.is_open()){
        
        /*Aqui será feita a leitura de cada linha do arquivo. Dependendo do número da linha, o conteúdo será 
        armazenado numa variável, armazenando apenas os caracteres necessários, pegando uma substring e delimitando
        o início e o final dela*/
        while(!fs.eof()){
            getline(fs, json);

            if(i == 2){
                rua = json.substr(17, json.size() - 2 - 17);
            }else if(i == 3){
                complemento = json.substr(18, json.size() - 2 - 18);
            }else if(i == 4){
                bairro = json.substr(13, json.size() - 2 - 13);
            }else if(i == 5){
                cidade = json.substr(17, json.size() - 2 - 17);
            }else if(i == 6){
                estado = json.substr(9, json.size()- 2 - 9);
            }
            i++;
        }
        fs.close();
    }

    /*if...else para definir o conteúdo da string a ser retornada pela função. Caso o tamanho da variável "complemento"
    seja zero, ela não será utilizada*/
    string endereco;
    if(complemento.length() == 0){
        endereco = rua + ". " + bairro + ", " + cidade + ", " + estado + ". CEP: " + cep;
    }else{
        endereco = rua + ", " + complemento + ". " + bairro + ", " + cidade + ", " + estado + ". CEP: " + cep;
    }

    /*Como o arquivo de CEP não é mais necessário, ele é deletado*/
    system("del \"cep.txt\""); 
    return endereco;
}