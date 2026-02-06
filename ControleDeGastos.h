#include "Despesa.h"
#include <iostream>
#include <vector>

class ControleDeGastos{
    private:
    std::vector <Despesa> gastos;
    
    public:

    void addDespesa(Despesa d){
        gastos.push_back(d);
    }
    

    double calcularTotalDespesas(){
        double total{};
        for(auto& k : gastos)
            total+= k.getValor();
        
        return total;
    }

    float calcularTotalDespesas(std::string tipo){
        float total{};

        for(Despesa k : gastos)
            if(k.getTipo() == tipo)
                total+= k.getValor();
        
        return total;
    }

    bool existeDespesaDoTipo(std::string tipoBusca){
        bool existe;

        for(Despesa k : gastos)
            if(tipoBusca == k.getTipo()){
                existe = true;  
                break;
            } else
                existe = false;

    return existe;
    }

    void exibirGastos(){
        if(gastos.empty()) {
            std::cout << "Nenhum gasto registrado." << std::endl;
            return;
        }
        for(auto& k : gastos)
            std::cout << " - " << k.getNome() << " [" << k.getTipo() << "] R$" << k.getValor() << std::endl;
    }

};