#pragma once
#include "ControleDeGastos.h"
#include "Ocupacao.h"
#include "Pessoa.h"

class UnidadeHabitacional{ //testar a Uh na main antes e depois de deixar abstrata
    private:
        int id;
        int limiteHospedes;
        double valorDiaria;
        Ocupacao periodo;
        vector <Pessoa*> hospedes;
        bool ocupado;

    public:
    UnidadeHabitacional(int i, int inicio, int fim) : id(i), Ocupacao(inicio, fim){} //QUE ERRO É ESSE
    virtual~ UnidadeHabitacional();

    bool getOcupado(){
        if(!ocupado) return false;
        else if(ocupado) return true;
    }

    double calcularCheckout(){ //mudar para método abstrato para as outras classes herdarem
        double checkout = 0;
        for(int i = 0; i < hospedes.size(); i++){
            checkout =+ hospedes[i]->getFatura().calcularTotal();
        }
        
        return checkout + (valorDiaria * periodo.calcularDias());
    }

    double calcularFaturaTotal(){ //esse tbm
        double fatura = 0;
        for(int i = 0; i < hospedes.size(); i++){
            fatura =+ hospedes[i]->getFatura().calcularTotal();
        }

        return fatura;
    }

    void exibirDetalhes(){
        for(int i = 0; i < hospedes.size(); i++){
            hospedes[i]->getFatura().exibirGastos();
        }
    }
};