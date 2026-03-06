#pragma once
#include <string>

using namespace std;

class Despesa{
    private:
    double valor;
    string tipo;
    string nome;
    int quantidade;

    public:
    Despesa(string n, string t, double v, int q) : nome{n}, tipo{t}, valor{v}, quantidade{q} {}
    Despesa(string n, string t, double v) : Despesa(n, t, v, 1) {}
    Despesa() : Despesa("", "", 0, 1) {}
    double getValor(){
        return valor;
    }
    string getTipo(){
        return tipo;
    }
    string getNome(){
        return nome;
    }
    int getQuantidade(){
        return quantidade;
    }

    void setValor(double valor){
        this->valor = valor;
    }
    void setTipo(string tipo){
        this->tipo = tipo;
    }
    void setNome(string nome){
        this->nome = nome;
    }
    void setQuantidade(int quantidade){
        this->quantidade = quantidade;
    }

    double calcularTotalDespesa(){
        return quantidade * valor;
    }

    void exibir(){
        cout << " - " << nome << " [" << tipo << "] "<< "Quantidade : " << quantidade << " R$" << calcularTotalDespesa() << endl;
    }
};