#pragma once
#include "UH.h"

class QuartoStandard : public UnidadeHabitacional{
    private:
        
    public:
        QuartoStandard(int i, double valorD) : UnidadeHabitacional(i, valorD) {
            tipo = 1;
            limiteHospedes = 2;
        }  
        QuartoStandard(int i, Data dataInicio, Data DataFim, double valorD) : UnidadeHabitacional(i, dataInicio, DataFim, valorD) {
            tipo = 1;
            limiteHospedes = 2;
        }  

    
    void exibirCheckout(){
        cout << "\n[ RECIBO DE CHECKOUT - " << getTipoString() << " " << id << " ]" << endl;
        cout << fixed << setprecision(2);
        
        cout << "Diárias (" << periodo.calcularDias() << "x R$ " << valorDiaria << "): R$ " << (valorDiaria * periodo.calcularDias()) << endl;
        cout << "Consumo (Fatura)      : R$ " << calcularFaturaTotal() << endl;
        cout << "---------------------------------------" << endl;
        cout << "TOTAL A PAGAR         : R$ " << calcularCheckout() << endl;
        cout << "---------------------------------------\n" << endl;
        
    }
    double calcularCheckout() override {
        return calcularFaturaTotal() + (valorDiaria * periodo.calcularDias());
    }
};