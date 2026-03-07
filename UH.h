#pragma once
#include "ControleDeGastos.h"
#include "Ocupacao.h"
#include "Pessoa.h"

class UnidadeHabitacional{ //testar a UH na main
    protected:
        int id;
        int tipo; // tipo de UH (standart ou suiteluxo)
        int limiteHospedes; //depende do tipo de UH
        double valorDiaria; //depende do tipo de UH
        Ocupacao periodo;
        vector<Pessoa*> hospedes;
        bool ocupado;

    public:
    UnidadeHabitacional(int i, int t, Data datainicio, Data datafim, double diaria) : id(i), tipo(t), periodo(datainicio, datafim), valorDiaria(diaria){}
    UnidadeHabitacional(int i, int t, Data datainicio, Data datafim) : id(i), tipo(t), periodo(datainicio, datafim){} //construtor para as classes filhas
    virtual~ UnidadeHabitacional();

    void setPessoas(){ //transferir para a main depois
        Data Nasc1(23, 3, 2007);
        Data Nasc2(20, 2, 1976);
        Pessoa* a = new Pessoa("Kael", "000.000.000-01", Nasc1);
        Pessoa* b = new Pessoa("Carlos", "000.000.000-02", Nasc2);
        hospedes.push_back(a);
        hospedes.push_back(b);
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