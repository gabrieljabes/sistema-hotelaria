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
        if(hospedesAtuais.size() == limiteHospedes){
            cout << "Não foi possível adicionar, limite de hóspedes atingido" << endl;
            return;
        } 
        hospedesAtuais.push_back(p);
        ocupado = true;
        
    }

    int getId(){
        return id;
    }

    int getTipo(){
        return tipo;
    }

    double getValorDiaria(){
        return valorDiaria;
    }

    Ocupacao getPeriodo(){
        return periodo;
    }

    Pessoa* getHospede(int index){
        if (index >= 0 && index < hospedesAtuais.size()) {
            return hospedesAtuais[index];
        }
        return nullptr;
    }

    Pessoa* getHospedePorCPF(string& cpfBusca) {
        for(int i = 0; i < hospedesAtuais.size(); i++) {
            if(hospedesAtuais[i]->getCpf() == cpfBusca) {
                return hospedesAtuais[i]; 
            }
        }
        return nullptr; 
    }

    int getQuantidadeHospedes() {
        return hospedesAtuais.size();
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

    virtual void exibirInfo(){
        cout << "\n[" << getTipoString() << " - Unidade " << id << "]" << endl;
        cout << "Valor da diária: R$ " << valorDiaria << endl;
        cout << "Limite de hóspedes: " << limiteHospedes << endl;
        cout << "Status: " << (ocupado ? "Ocupado" : "Livre") << endl;
        cout << "Período: " << periodo.getDataInicio().toStringData() << " a " 
             << periodo.getDataFim().toStringData() << endl;
    }


    virtual void exibirFaturas(){
        if(hospedesAtuais.empty())
            cout << "Não há hóspedes nessa unidade habitacional" << endl;
        else if(calcularFaturaTotal() == 0)
            cout << "Não há faturas dos hóspedes nessa unidade habitacional" << endl;
        else {
            for(int i = 0; i < hospedesAtuais.size(); i++){
                cout << "Fatura de " <<hospedesAtuais[i]->getNome() << endl;
                hospedesAtuais[i]->getFatura().exibirGastos();
                cout << "Total de " << hospedesAtuais[i]->getNome() << ": R$ " << hospedesAtuais[i]->getFatura().calcularTotal() << endl << endl;
            }
            cout << "Total de todos: R$ "  << calcularFaturaTotal() << endl;
        }
    }

    string getTipoString(){
        if(tipo == 1){
            return "Quarto Standard";
        } else if(tipo == 2){
            return "Suíte Luxo";
        }
        return "Desconhecido";
    }

    virtual void exibirCheckout() = 0;

    void alterarPeriodo(Data novaInicio, Data novaFim) {
        periodo.setDataInicio(novaInicio);
        periodo.setDataFim(novaFim);
    }
};