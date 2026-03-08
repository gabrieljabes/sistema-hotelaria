#pragma once
#include "UH.h"
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
    
    void listarTodas(){
        for(auto a : UH){
            
        }
    }

    void inserir(){
        //inserir um dado específico em uma UH?
    }

    int pesquisar(){
        //retorna ID?
    }

    void exibirUm(){
        //usar ID como parâmetro para exibir UH
    }

    void alterar(){
        //usar ID como parâmetro para alterar os dados
    }
    
    void remover(){
        //usar ID como parâmetro para remover UH
    }

    void exibirRelatorio(){
        //UH por UH?
    }

    void menu(){
        //oqueéisso
    }

    void salvarDados(){
        //oqueéisso
    }

    void carregarDados(){
        //oqueéisso
    }
};