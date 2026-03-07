#pragma once
#include "ControleDeGastos.h"
#include "Data.h"

using namespace std;

class Pessoa{
    private:
        string nome;
        string cpf;
        Data dataNascimento;
        ControleDeGastos fatura;
    public:
        Pessoa(string n, string c, Data nasc) : nome{n}, cpf{c}, dataNascimento{nasc} {}
        Pessoa() : Pessoa("", "", Data()) {}

        string getNome(){
            return nome;
        }

        string getCpf(){
            return cpf;
        }

        Data getData(){
            return dataNascimento;
        }
        // passa o endereço da fatura, não cria cópia. Necessário pra poder atualizar a fatura.
        ControleDeGastos& getFatura(){
            return fatura;
        }
        
        void setNome(string n){
            nome = n;
        }
        
        void setCpf(string c){
            cpf = c;
        }

        void setData(int d, int m, int a){
            dataNascimento.setDia(d);
            dataNascimento.setMes(m);
            dataNascimento.setAno(a);
        }

        
};