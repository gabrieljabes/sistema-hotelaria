#include <string>
#include <vector>
#include <iostream>
#include "Ocupacao.h"
#include "Pessoa.h"

#include "ControleDeGastos.h"
#include "QuartoStandard.h"
#include "SuiteLuxo.h"

int main(){
    Pessoa p("Gabriel", "140.630.054-37", Data(21, 12, 2006));

    Pessoa p("Gabriel", "140.630.054-37", Data(21, 12, 2006));
    Pessoa d("Jabis", "000.000.000-00", Data(21, 11, 2006));

    Despesa a("Batata frita", "Comida", 27.50, 2);
    Despesa b("Iscas de frango", "Comida", 40.50);
    Despesa c("Secador de cabelo", "Empréstimo", 80.00);
 
    UnidadeHabitacional* teste = new SuiteLuxo(101, Data(27, 12, 2026), Data(31, 12, 2026), 800, false);
    UnidadeHabitacional* seila = new QuartoStandard(102, Data(23, 12, 2026), Data(27, 12, 2026), 200);

    teste->addHospede(&p);
    teste->addHospede(&d);
    teste->getHospede(0)->getFatura().addDespesa(a);
    teste->getHospede(1)->getFatura().addDespesa(b);
    teste->getHospede(0)->getFatura().addDespesa(c);

    teste->exibirUH();
    cout << endl << endl << endl;
    teste->exibirDetalhes();
    cout << endl << endl << endl;
    teste->exibirCheckout();
    cout << endl << endl << endl;
    seila->exibirUH();
    cout << endl << endl << endl;
    seila->exibirDetalhes();
    cout << endl << endl << endl;
    seila->exibirCheckout();

   
}