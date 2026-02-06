#include <string>
#include <vector>
#include <iostream>

class Data{
    private:
    int dia, mes, ano;
    std::vector <int> diaLimite{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    public:
    Data(){
        dia = 0;
        mes = 0;
        ano = 0;
    }
    Data(int d, int m, int a){
        if((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0))
            diaLimite[1] = 29;
        int itMes = m - 1;
        if(itMes < diaLimite.size()){
            if(d > diaLimite[itMes] || d <= 0){
                dia = 1;
                std::cout << "Atributo dia Inválido" << std::endl;
            }
            else
                dia = d;
        }

        else{
            dia = d;
            std::cout << "Atributo mês Inválido" << std::endl;
        }
        
        if(m > 12 || m <= 0){
            mes = 1;
        }
        else
            mes = m;

        if(a < 0)
            ano = 1;
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
    

    std::string toStringData(){
        bool d_dia = (dia >= 10);
        bool d_mes = (mes >= 10);
        std::string stringDataDia;
        std::string stringDataMes;
        std::string stringDataAno;

        if(d_dia == false)
            stringDataDia = "0" + (std::to_string(getDia()));
        else
            stringDataDia = (std::to_string(getDia()));

         if(d_mes == false)
            stringDataMes = "0" + (std::to_string(getMes()));
        else
            stringDataMes = (std::to_string(getMes()));

            stringDataAno = (std::to_string(getAno()));
        
        std::string stringData = stringDataDia + "/" + stringDataMes + "/" + stringDataAno;

        return stringData;
    }
    
    void exibirData(){
        std::cout << toStringData() << std::endl;
    }
};