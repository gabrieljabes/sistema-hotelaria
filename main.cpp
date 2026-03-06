#include <string>
#include <vector>
#include <iostream>
#include "Ocupacao.h"
#include "ControleDeGastos.h"

int main(){

ControleDeGastos w;
Despesa a("Batata frita", "Comida", 27.50, 2);
Despesa b("Iscas de frango", "Comida", 40.50);

w.addDespesa(a);
w.addDespesa(b);

w.exibirGastos();

std::cout << "Total: " << w.calcularTotal() << std::endl;
    return 0;
}