#pragma once
#include "UH.h"
#include <iomanip>

class SuiteLuxo : public UnidadeHabitacional{
    private:
    double taxaLimpezaExtra = 150; //da mais trabalho limpar
    double descontoVIP = 0.9; //desconto na fatura
    bool temHidromassagemPrivativa;

    public:
    SuiteLuxo(int i, double valorD, bool hidro) : temHidromassagemPrivativa(hidro), UnidadeHabitacional(i, valorD){
        tipo = 2;
        limiteHospedes = 5;
    }
    SuiteLuxo(int i, Data dataInicio, Data dataFim, double valorD, bool hidro) : temHidromassagemPrivativa(hidro), UnidadeHabitacional(i, dataInicio, dataFim, valorD){
        tipo = 2;
        limiteHospedes = 5;
    }

    void setHidromassagem(bool q){
        temHidromassagemPrivativa = q;
    }

    bool getHidromassagem(){
        return temHidromassagemPrivativa;
    }

    void exibirInfo() override {
            UnidadeHabitacional::exibirInfo();
            cout << "Hidromassagem: " << (temHidromassagemPrivativa ? "Sim" : "Não") << endl;
    }
    
    double calcularCheckout() override {
        if(temHidromassagemPrivativa == true)
            return (calcularFaturaTotal() * descontoVIP) + (valorDiaria * periodo.calcularDias()) + taxaLimpezaExtra + 100;
        else
            return (calcularFaturaTotal() * descontoVIP) + (valorDiaria * periodo.calcularDias()) + taxaLimpezaExtra;
    }

    void exibirCheckout(){
        cout << "\n[ RECIBO DE CHECKOUT - " << getTipoString() << " " << id << " ]" << endl;
        cout << fixed << setprecision(2);
        cout << "Diárias (" << periodo.calcularDias() << "x R$ " << valorDiaria << "): R$ " << (valorDiaria * periodo.calcularDias()) << endl;
        double faturaTotal = calcularFaturaTotal();
        cout << "Consumo (Fatura)      : R$ " << faturaTotal << endl;
        // Mostra o valor real descontado em vez de apenas a percentagem
        if (faturaTotal > 0) {
            cout << "Desconto VIP (10%)    :-R$ " << faturaTotal * (1.0 - descontoVIP) << endl;
        }
        cout << "Taxa de Limpeza Extra : R$ " << taxaLimpezaExtra << endl;
        if(temHidromassagemPrivativa) {
            cout << "Taxa Hidromassagem    : R$ 100.00" << endl;
        }
        cout << "---------------------------------------" << endl;
        cout << "TOTAL A PAGAR         : R$ " << calcularCheckout() << endl;
        cout << "---------------------------------------\n" << endl;
        
    }
    
};