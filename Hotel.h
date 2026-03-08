#pragma once
#include "UH.h"
#include "SuiteLuxo.h"
#include "QuartoStandard.h"
#include <iomanip>

class Hotel{
    private:
    vector<UnidadeHabitacional*> UH;
    vector<shared_ptr<Pessoa>> clientes;
    vector<shared_ptr<UnidadeHabitacional>> quartos;

    public:

    void cadastrarCliente(){
        string Nome;
        string cpf;
        int d, m, a;

        cin.ignore();
        getline(cin, Nome);
        getline(cin, cpf);
        cin >> d >> m >> a;
        Data dataNasc(d, m, a);

        clientes.push_back(make_shared<Pessoa>(Nome, cpf, dataNasc));
    }

    void cadastrarQuarto(){
    int id;
    Data inicio;
    Data fim;
    double diaria;
    int tipo;
    char res = 's';

    while(res == 's'){
        cout << "Qual a número da unidade?" << endl;
        cin >> id;

        cout << "Qual o tipo da Unidade Habitacional? (1 - Quarto Standart ou 2 - Suíte de luxo)" << endl;
        cin >> tipo;

        cout << "Qual o dia do Check-in?" << endl;
        inicio.lerData();

        cout << "Qual o dia do Check-out?" << endl;
        fim.lerData();

        cout << "Qual o valor da diária?" << endl;
        cin >> diaria;

        switch(tipo){
            case 1:
            quartos.push_back(make_shared<QuartoStandard>(id, inicio, fim, diaria));
            break;

            case 2:
            bool hidro;
            char res;
            cout << "O hóspede quer hidromassagem? (s ou n)" << endl;
            if(res == 's') hidro = true;
            else hidro == false;
            quartos.push_back(make_shared<SuiteLuxo>(id, inicio, fim, diaria, hidro));
            break;

            default:
            break;
        }
        cout << "Deseja cadastrar um novo quarto? (s ou n)" << endl;
        cin >> res;
    }
    }
    
    void listarTodas(){
        cout << endl;
        for(auto a : UH){
            cout << "Unidade " << a->getId() << ":" << endl;
            a->exibirInfo();
        }
    }

    void exibirUm(){
        int id;
        cout << "Qual a número da unidade?" << endl;
        cin >> id;
        for(int i = 0; i < UH.size(); i++){
            if(id == UH[i]->getId())
                UH[i]->exibirInfo();
                return;
        }
        cout << "ID não encontrada." << endl;
    }

    void alterar(){
        //usar ID como parâmetro para alterar os dados
    }
    
    void remover(){
        int id;
        cout << "Qual a número da unidade?" << endl;
        cin >> id;
        for(int i = 0; i < UH.size(); i++){
            if(id == UH[i]->getId())
                UH[i]->liberarUH();
                return;
        }
        cout << "ID não encontrada." << endl;
    }

    void exibirRelatorio(){
        //UH por UH?
    }

    void salvarDados(){
        //oqueéisso
    }

    void carregarDados(){
        //oqueéisso
    }
};