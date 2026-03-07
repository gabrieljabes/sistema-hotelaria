#include <string>
#include <vector>
#include <iostream>
#include "Ocupacao.h"
#include "Pessoa.h"


int main(){

    Pessoa p("Gabriel", "140.630.054-37", Data(21, 12, 2006));
    Despesa a("Batata frita", "Comida", 27.50, 2);
    Despesa b("Iscas de frango", "Comida", 40.50);
    Despesa c("Secador de cabelo", "Empréstimo", 80.00);

    p.getFatura().addDespesa(a);
    p.getFatura().addDespesa(b);
    p.getFatura().addDespesa(c);
    p.getFatura().exibirGastos("comida");
    std::cout << "Total: " << p.getFatura().calcularTotal() << std::endl;
    p.getFatura().zerarGastos();
    p.getFatura().exibirGastos();

    std::cout << "Total: " << p.getFatura().calcularTotal() << std::endl;
    std::cout << p.getNome() << p.getCpf() << p.getData().toStringData() << endl;
        return 0;
}

