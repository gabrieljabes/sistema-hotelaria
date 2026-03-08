#pragma once
#include "UH.h"

class Hotel{
    private:
    vector<UnidadeHabitacional*> UH;

    public:
    
    void listarTodas(){
        for(auto a : UH){
            //getID pra listar as unidades com titulo
            a->exibirDetalhes();
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