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

    void addDespesa(Despesa d){
        for(auto& item : gastos){
            if(item.getNome() == d.getNome()){
                item.setQuantidade(item.getQuantidade() + d.getQuantidade());
                return;
            }
        }
        gastos.push_back(d);
        }
    

    void deleteDespesa(int index){
        gastos.erase(gastos.begin() + index);
    }
    

    double calcularTotal(){
        double total{};
        for(auto& k : gastos)
            total+= k.calcularTotalDespesa();
        
        return total;
    }

    double calcularTotal(string tipo){
        double total{};

        for(auto& k : gastos)
            if(k.getTipo() == tipo)
                total+= k.calcularTotalDespesa();
        
        return total;
    }

    bool existeDespesaDoTipo(string tipoBusca){

        transform(tipoBusca.begin(), tipoBusca.end(), tipoBusca.begin(), ::tolower);

        for(auto& k : gastos){
            //copia do valor pra comparar
            string t = k.getTipo();
            transform(t.begin(), t.end(), t.begin(), ::tolower);
            if(tipoBusca == t)
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

    void exibirGastos(string tipoGasto){
        if(existeDespesaDoTipo(tipoGasto)){
        transform(tipoGasto.begin(), tipoGasto.end(), tipoGasto.begin(), ::tolower);

        for(auto& k : gastos){
            //copia do valor pra comparar
            string t = k.getTipo();
            //transforma as letras em minusculas
            transform(t.begin(), t.end(), t.begin(), ::tolower);

            if(tipoGasto == t){
                k.exibir();
            }
        }
    } else
        cout << "Não há gastos do tipo pesquisado" << endl;
        return;
    }

    void zerarGastos(){
        int tam_vetor = gastos.size();
        for(int i = 0; i < tam_vetor; i++)
            gastos.pop_back();
    }

};