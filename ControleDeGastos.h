#pragma once
#include "Despesa.h"
#include <iostream>
#include <vector>


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
        bool existe;

        for(auto& k : gastos)
            if(tipoBusca == k.getTipo()){
                existe = true;  
                break;
            } else
                existe = false;

    return existe;
    }

    void exibirGastos(){
        if(gastos.empty()) {
            cout << "Nenhum gasto registrado." << endl;
            return;
        }
        for(auto& k : gastos)
            cout << " - " << k.getNome() << " [" << k.getTipo() << "] "<< "Quantidade : " << k.getQuantidade() << " R$" << k.calcularTotalDespesa() << endl;
    }

};