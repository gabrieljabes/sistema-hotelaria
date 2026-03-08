#pragma once
#include "UH.h"

class QuartoStandard : public UnidadeHabitacional{
    private:
        
    public:
        QuartoStandard(int i, Data dataInicio, Data DataFim, double valorD) : UnidadeHabitacional(i, dataInicio, DataFim, valorD) {
            tipo = 1;
            limiteHospedes = 2;
        }  

    
    void exibirCheckout(){
        cout << "\n=== CHECKOUT ===" << endl;
        cout << "Total das faturas: R$ " << calcularFaturaTotal() << endl;
        cout << "Custo de " << periodo.calcularDias() << " diárias: R$ " << valorDiaria * periodo.calcularDias() << endl;
        cout << "Total: R$ " << calcularCheckout() << endl;
        
    }
    double calcularCheckout() override {
        return calcularFaturaTotal() + (valorDiaria * periodo.calcularDias());
    }
};