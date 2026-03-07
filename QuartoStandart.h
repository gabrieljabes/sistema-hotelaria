#pragma once
#include "UH.h"

class QuartoStandart : public UnidadeHabitacional{
    public:
    double calcularCheckout() override {
        double checkout = 0;
        for(int i = 0; i < hospedes.size(); i++){
            checkout =+ hospedes[i]->getFatura().calcularTotal();
        }
        
        return checkout + (valorDiaria * periodo.calcularDias());
    }
};