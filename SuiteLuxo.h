#pragma once
#include "UH.h"

class SuiteLuxo : public UnidadeHabitacional{
    private:
    double taxaLimpezaExtra = 150; //da mais trabalho limpar
    double descontoVIP = 0.9; //desconto na fatura
    bool temHidromassagemPrivativa;

    public:
    SuiteLuxo(int i, Data dataInicio, Data dataFim, double valorD, bool hidro) : temHidromassagemPrivativa(hidro), UnidadeHabitacional(i, dataInicio, dataFim, valorD){
        tipo = 2;
        limiteHospedes = 5;
    }

    void setHidromassagem(bool q){
        temHidromassagemPrivativa = q;
    }


    
    double calcularCheckout() override {
        if(temHidromassagemPrivativa == true)
            return (calcularFaturaTotal() * descontoVIP) + (valorDiaria * periodo.calcularDias()) + taxaLimpezaExtra + 100;
        else
            return (calcularFaturaTotal() * descontoVIP) + (valorDiaria * periodo.calcularDias()) + taxaLimpezaExtra;
    }

    void exibirCheckout(){
        cout << "\n=== CHECKOUT ===" << endl;
        cout << "Total das faturas: R$ " << calcularFaturaTotal() << endl;
        cout << "Custo de " << periodo.calcularDias() << " diárias: R$ " << valorDiaria * periodo.calcularDias() << endl;
        cout << "Desconto VIP sobre a fatura: " << (1 - descontoVIP) * 100 << "%" << endl;
        if(temHidromassagemPrivativa)
            cout << "Taxa extra da hidromassagem: R$ " << 100 << endl;
        cout << "Taxa de limpeza extra: R$ " << taxaLimpezaExtra << endl;
        cout << "Total: R$ " << calcularCheckout() << endl;
        
    }
    
};