#pragma once
#include "UH.h"

class SuiteLuxo : public UnidadeHabitacional{
    private:
    double TaxadeServico = 100;

    public:
    double calcularCheckout() override{
        double checkout = 0;
        for(int i = 0; i < hospedes.size(); i++){
            checkout =+ hospedes[i]->getFatura().calcularTotal();
        }
        
        return checkout + (valorDiaria * periodo.calcularDias()) + TaxadeServico;
    }
};