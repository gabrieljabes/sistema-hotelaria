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
UnidadeHabitacional* uh;
int tipo;
switch(tipo){
    case 1:
    uh = new QuartoStandart(301, inicio, fim);
    cout << uh->calcularCheckout() << endl;
    break;
    
    case 2:
    uh = new SuiteLuxo(601, inicio, fim);
    cout << uh->calcularCheckout() << endl;
    break;

    default: break;
}

delete uh;

w.addDespesa(a);
w.addDespesa(b);

w.exibirGastos();

cout << "Total: " << w.calcularTotal() << endl;
    return 0;
}