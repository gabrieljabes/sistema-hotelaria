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

int calcularDias() {
        // transforma as duas datas em dias absolutos
        int diasInicio = dataInicio.getDiasAbsolutos();
        int diasFim = dataFim.getDiasAbsolutos();
        
        int diferenca = diasFim - diasInicio;

        if (diferenca < 0) {
            cout << "Erro: A data de fim é anterior à data de início!" << endl;
            return 0; 
        }

        // retorna a diferença + 1 (para incluir a diária do próprio dia de entrada)
        return diferenca + 1;
    }
};