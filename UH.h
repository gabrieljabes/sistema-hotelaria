#pragma once
#include "ControleDeGastos.h"
#include "Ocupacao.h"
#include "Pessoa.h"
#include <memory>

class UnidadeHabitacional{ //testar a UH na main
    protected:
        int id;
        int tipo; // tipo de UH (standart ou suiteluxo)
        int limiteHospedes; //depende do tipo de UH
        double valorDiaria; //depende do tipo de UH
        Ocupacao periodo;
        vector<unique_ptr<Pessoa>> hospedes;
        bool ocupado;

    public:
    UnidadeHabitacional(int i, int t, Data datainicio, Data datafim, double diaria) : id(i), tipo(t), periodo(datainicio, datafim), valorDiaria(diaria){}
    UnidadeHabitacional(int i, int t, Data datainicio, Data datafim) : id(i), tipo(t), periodo(datainicio, datafim){} //construtor para as classes filhas

    void setPessoas(){ //transferir para a main depois
        Data Nasc1(23, 3, 2007);
        Data Nasc2(20, 2, 1976);
        hospedes.push_back(make_unique<Pessoa>("Kael", "000.000.000-01", Nasc1));
        hospedes.push_back(make_unique<Pessoa>("Carlos", "000.000.000-02", Nasc2));
    }

    bool getOcupado(){
        if(!ocupado) return false;
        else if(ocupado) return true;
    }

    virtual double calcularCheckout() = 0;

    double calcularFaturaTotal(){
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