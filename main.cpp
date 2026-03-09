#include <iostream>
#include "Hotel.h"

using namespace std;

int main(){
    Hotel parahotel;    

    
    parahotel.carregarDados();

    parahotel.menu();

    parahotel.salvarDados();

    return 0;
}