#pragma once
#include "Despesa.h"
#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

class ControleDeGastos{
    private:
    vector <Despesa> gastos;
    
    public:

    Despesa getDespesa(int index){
        return gastos[index];
    }

    void addDespesa(Despesa& d){
        for(auto& item : gastos){
            if(item.getNome() == d.getNome()){
                item.setQuantidade(item.getQuantidade() + d.getQuantidade());
                return;
            }
        }
        gastos.push_back(d);
        }
    

    void deleteDespesa(int index){
        if(index >= 0 && index < gastos.size())
            gastos.erase(gastos.begin() + index);
    }
    

    double calcularTotal(){
        double total{};
        for(auto& k : gastos)
            total+= k.calcularTotalDespesa();
        
        return total;
    }

    double calcularTotal(string& tipo){
        double total{};

        for(auto& k : gastos)
            if(k.getTipo() == tipo)
                total+= k.calcularTotalDespesa();
        
        return total;
    }

    bool existeDespesaDoTipo(const string& tipoBusca){
        string buscaLower = toLower(tipoBusca);
        for(auto& k : gastos){
            if(toLower(k.getTipo()) == buscaLower)
                return true;
        }
        return false;
    }
    void exibirGastos(){
        if(gastos.empty()) {
            cout << "Nenhum gasto registrado." << endl;
            return;
        }
        for(auto& k : gastos)
            k.exibir();
    }

    void exibirGastos(const string& tipoGasto){
        if(existeDespesaDoTipo(tipoGasto)){
            for(auto& k : gastos){
                if(toLower(k.getTipo()) == toLower(tipoGasto))
                    k.exibir();
            }
        } else return;
    }

    int getQuantDespesas(){
        return gastos.size();
    }

    void zerarGastos(){
        gastos.clear();
    }

    string toLower(string s){
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }
};