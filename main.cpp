#include <iostream>
#include "Hotel.h"

using namespace std;

int main(){
    Hotel parahotel;    
    
    // 1. Carrega os dados automaticamente ao abrir
    parahotel.carregarDados();

    // 2. Inicia o loop interativo do sistema
    parahotel.menu();

    // 3. Salva os dados no arquivo assim que o usuário digita 0 para sair do menu
    parahotel.salvarDados();

    return 0;
}