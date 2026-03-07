#pragma once
#include "UH.h"

class QuartoStandart : public UnidadeHabitacional{
    private:
    
    public:
    QuartoStandart(int i, Data dataInicio, Data DataFim) : UnidadeHabitacional(i, 1, dataInicio, DataFim){}

    double calcularCheckout() override {
        double checkout = 0;
        for(int i = 0; i < hospedes.size(); i++){
            checkout =+ hospedes[i]->getFatura().calcularTotal();
        }
        
        return checkout + (valorDiaria * periodo.calcularDias());
    }
};