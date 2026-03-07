#pragma once
#include "UH.h"

class SuiteLuxo : public UnidadeHabitacional{
    private:
    double TaxadeServico = 100;

    public:
    SuiteLuxo(int i, Data dataInicio, Data dataFim) : UnidadeHabitacional(i, 2, dataInicio, dataFim){}

    double calcularCheckout() override{
        double checkout = 0;
        for(int i = 0; i < hospedes.size(); i++){
            checkout =+ hospedes[i]->getFatura().calcularTotal();
        }
        
        return checkout + (valorDiaria * periodo.calcularDias()) + TaxadeServico;
    }
};