#pragma once
#include "ControleDeGastos.h"
#include "Ocupacao.h"
#include "Pessoa.h"

class UnidadeHabitacional{
    private:
        int id;
        int limiteHospedes;
        double valorDiaria;
        Ocupacao periodo;
        vector <Pessoa*> hospedes;
        bool ocupado;   
    public:
    virtual~ UnidadeHabitacional();
    
        
};