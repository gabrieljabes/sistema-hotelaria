#pragma once
#include "ControleDeGastos.h"
#include "Ocupacao.h"
#include "Pessoa.h"
#include <memory>

class UnidadeHabitacional{
    protected:
        int id;
        int tipo; // tipo de UH 1 - standart | 2 - suiteluxo
        int limiteHospedes; //depende do tipo de UH
        double valorDiaria; //depende do tipo de UH
        Ocupacao periodo; 
        vector <Pessoa*> hospedesAtuais;
        bool ocupado;

    public:
    UnidadeHabitacional(int i, Data datainicio, Data datafim, double diaria) : 
    id(i), periodo(datainicio, datafim), valorDiaria(diaria), ocupado(false){}
    UnidadeHabitacional(int i, Data datainicio, Data datafim) :
    id(i), periodo(datainicio, datafim), ocupado(false) {} //construtor para as classes filhas

    virtual ~UnidadeHabitacional() = default;

    void addHospede(Pessoa* p){
        // se antes do método ser chamado o vetor era vazio, então ele mudará o estado de ocupado;
        if(hospedesAtuais.empty())
            ocupado = true;

        if(hospedesAtuais.size() == limiteHospedes){
            cout << "Não foi possível adicionar, limite de hóspedes atingido" << endl;
        } else {
             hospedesAtuais.push_back(p);
        }
    }

    Pessoa* getHospede(int index){
        if (index >= 0 && index < hospedesAtuais.size()) {
            return hospedesAtuais[index];
        }
        return nullptr;
    }

    void liberarUH(){
        hospedesAtuais.clear();
        ocupado = false;
    }

    void setOcupado(){
        ocupado = true;
    }

    bool getOcupado(){
        return ocupado;
    }

    virtual double calcularCheckout() = 0;

    double calcularFaturaTotal(){
        double fatura = 0;
        for(int i = 0; i < hospedesAtuais.size(); i++){
            fatura += hospedesAtuais[i]->getFatura().calcularTotal();
        }

        return fatura;
    }

    virtual void exibirUH(){
        string quarto;
        if(tipo == 1)
            quarto = "Quarto Standard";
        else if(tipo == 2)
            quarto = "Suíte Luxo";
        
        
        cout << "\n=== " << quarto << " ===" << endl;
        cout << "ID: " << id << endl;
        cout << "Valor da diária: R$" << valorDiaria << endl;
        cout << "Limite de hóspedes: " << limiteHospedes << endl;
    }

    virtual void exibirDetalhes(){
        if(hospedesAtuais.empty())
            cout << "Não há hóspedes nessa unidade habitacional" << endl;
        else if(calcularFaturaTotal() == 0)
            cout << "Não há faturas dos hóspedes nessa unidade habitacional" << endl;
        else {
            for(int i = 0; i < hospedesAtuais.size(); i++){
                cout << "Fatura de " <<hospedesAtuais[i]->getNome() << endl;
                hospedesAtuais[i]->getFatura().exibirGastos();
            }
        }
    }

    virtual void exibirCheckout() = 0;
};