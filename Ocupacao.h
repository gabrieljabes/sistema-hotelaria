#pragma once
#include "Data.h"

class Ocupacao{
    private:
    Data dataInicio;
    Data dataFim;

    public:
    Ocupacao(Data inicio, Data fim){
        dataInicio = inicio;
        dataFim = fim;
    }

    Data getDataInicio(){
        return dataInicio;
    }
    Data getDataFim(){
        return dataFim;
    }

    void setDataInicio(Data inicio){
        dataInicio = inicio;
    }

    void setDataFim(Data fim){
        dataFim = fim;
    }

    int calcularDias(){
        //avança os dias de uma cópia da data de início até se igualar a do fim para calcular os dias
        Data d = getDataInicio();
        int i = 1; // inclui a data de Inicio
        while(d.toStringData() != getDataFim().toStringData()){
            d.avancarDia();
            i++;
        }
      return i;
    }
};  