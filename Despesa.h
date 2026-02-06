#include <string>

class Despesa{
    private:
    double valor;
    std::string tipo;
    std::string nome;

    public:
    Despesa(){
        valor = 0;
        tipo = "";
        nome = "";
    }
    Despesa(std::string n, std::string t, double v){
        nome = n;
        tipo = t;
        valor = v;
    }
    double getValor(){
        return valor;
    }
    std::string getTipo(){
        return tipo;
    }
    std::string getNome(){
        return nome;
    }

    void setValor(double valor){
        this->valor = valor;
    }
    void setTipo(std::string tipo){
        this->tipo = tipo;
    }
    void setNome(std::string nome){
        this->nome = nome;
    }
};