#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Data{
    private:
    int dia, mes, ano;
    vector <int> diaLimite{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool valida = true;
    public:
    Data(){
        dia = 0; mes = 0; ano = 0;
        valida = false;
    }
    Data(int d, int m, int a){
            valida = true; // Assume que é válida até provar o contrário

            if((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0))
                diaLimite[1] = 29;
                
            int itMes = m - 1;
            if(itMes >= 0 && itMes < diaLimite.size()){
                if(d > diaLimite[itMes] || d <= 0){
                    dia = 1;
                    cout << "Atributo dia Inválido" << endl;
                    valida = false; 
                }
                else
                    dia = d;
            }
            else{
                dia = d;
                cout << "Atributo mês Inválido" << endl;
                valida = false; 
            }
            
            if(m > 12 || m <= 0){
                mes = 1;
                valida = false; 
            }
            else
                mes = m;

            if(a < 0){
                ano = 1;
                valida = false; 
            }
            else
                ano = a;
    }

    int getDia(){
        return dia;
    }
    int getMes(){
        return mes;
    }
    int getAno(){
        return ano;
    }
    void setDia(int d){
        dia = d;
    }
    void setMes(int m){
        mes = m;
    }
    void setAno(int a){
        ano = a;
    }

    void avancarDia(){
        if(dia < diaLimite[mes - 1])
            setDia(getDia() + 1);
        else{
            setDia(1);

            if(mes != 12)
                setMes(getMes() + 1);
            else{
                setMes(1);
                setAno(getAno() + 1);
            }
        }
    }
    

    string toStringData(){
        bool d_dia = (dia >= 10);
        bool d_mes = (mes >= 10);
        string stringDataDia;
        string stringDataMes;
        string stringDataAno;

        if(d_dia == false)
            stringDataDia = "0" + (to_string(getDia()));
        else
            stringDataDia = (to_string(getDia()));

         if(d_mes == false)
            stringDataMes = "0" + (to_string(getMes()));
        else
            stringDataMes = (to_string(getMes()));

            stringDataAno = (to_string(getAno()));
        
        string stringData = stringDataDia + "/" + stringDataMes + "/" + stringDataAno;

        return stringData;
    }
    
    void exibirData(){
        cout << toStringData() << endl;
    }

    bool isValida(){
        return valida;
    }

    bool operator<=(const Data& d){
        if(ano != d.ano) return ano < d.ano;
        if(mes != d.mes) return mes < d.mes;
        return dia <= d.dia;
    }

};