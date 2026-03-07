#include <string>
#include <vector>
#include <iostream>
#include "Ocupacao.h"
#include "ControleDeGastos.h"
#include "QuartoStandart.h"
#include "SuiteLuxo.h"

int main(){

ControleDeGastos w;
Despesa a("Batata frita", "Comida", 27.50, 2);
Despesa b("Iscas de frango", "Comida", 40.50);

Data inicio(7, 3, 2026);
Data fim(10, 3, 2026);
Data Nasc1(23, 3, 2007);
Data Nasc2(20, 2, 1976);


w.addDespesa(a);
w.addDespesa(b);

w.exibirGastos();

cout << "Total: " << w.calcularTotal() << endl;
    return 0;
}