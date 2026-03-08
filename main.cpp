#include <string>
#include <vector>
#include <iostream>
#include "Ocupacao.h"
#include "Pessoa.h"

#include "ControleDeGastos.h"
#include "QuartoStandard.h"
#include "SuiteLuxo.h"
#include "Hotel.h"

int main(){
    Pessoa p("Gabriel", "140.630.054-37", Data(21, 12, 2006));
    Pessoa d("Jabis", "000.000.000-00", Data(21, 11, 2006));

    Despesa a("Batata frita", "Comida", 27.50, 2);
    Despesa b("Iscas de frango", "Comida", 40.50);
    Despesa c("Secador de cabelo", "Empréstimo", 80.00);
 
    std::shared_ptr<UnidadeHabitacional> teste = std::make_shared<SuiteLuxo>(101, Data(27, 12, 2026), Data(31, 12, 2026), 800, false);
    std::shared_ptr<UnidadeHabitacional> seila = std::make_shared<QuartoStandard>(102, Data(23, 12, 2026), Data(27, 12, 2026), 200);


    Hotel parahotel;    

    parahotel.cadastrarQuarto(teste);
    parahotel.buscarQuartoPorID(101).get()->addHospede(&p);
    parahotel.buscarQuartoPorID(101).get()->addHospede(&d);
    p.getFatura().addDespesa(a);
    d.getFatura().addDespesa(b);

    parahotel.exibirFaturaUH(101);




   
}