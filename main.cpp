#include <string>
#include <vector>
#include <iostream>
#include "Ocupacao.h"
#include "ControleDeGastos.h"

int main(){

ControleDeGastos w;
Despesa a("Batata frita", "Comida", 27.50, 2);
Despesa b("Iscas de frango", "Comida", 40.50);
Despesa c("Secador de cabelo", "Empréstimo", 80.00);

w.addDespesa(a);
w.addDespesa(b);
w.addDespesa(c);

w.exibirGastos("comida");

std::cout << "Total: " << w.calcularTotal() << std::endl;
    return 0;
}