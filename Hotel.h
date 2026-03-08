#pragma once
#include "UH.h"
#include "SuiteLuxo.h"
#include "QuartoStandard.h"
#include <iomanip>

class Hotel{
    private:
    vector<shared_ptr<UnidadeHabitacional>> UHs;
    vector<shared_ptr<Pessoa>> clientes;

    public:

    shared_ptr<UnidadeHabitacional> buscarQuartoPorID(int id){
        for(int i = 0; i < UHs.size(); i++){
            if(id == UHs[i]->getId()){
                return UHs[i];
            }
        }
        return nullptr;
    }

    bool alterarData(int id, Data inicio, Data fim){

    for(auto& a : UHs){

        if(a.get()->getId() == id) continue; // ignora o próprio quarto

        Data inicioExistente = a.get()->getPeriodo().getDataInicio();
        Data fimExistente = a.get()->getPeriodo().getDataFim();

        if(inicio <= fimExistente || inicioExistente <= fim){
            return false;
        }
    }

    buscarQuartoPorID(id).get()->getPeriodo().setDataInicio(inicio);
    buscarQuartoPorID(id).get()->getPeriodo().setDataFim(fim);

    return true;
}

    void cadastrarCliente(){
        string Nome;
        string cpf;
        int d, m, a;

        cin.ignore();
        cout << "Qual o nome do hóspede?" << endl;
        getline(cin, Nome);

        cout << "Qual o CPF dele(a)?" << endl;
        getline(cin, cpf);

        cout << "Digite a data de nascimento (dd mm aaaa):" << endl;
        cin >> d >> m >> a;
        Data dataNasc(d, m, a);

        clientes.push_back(make_shared<Pessoa>(Nome, cpf, dataNasc));
    }

    void cadastrarQuarto(){
    int id;
    int d, m, a;
    double diaria;
    int tipo;
    char res = 's';

    while(res == 's' || res == 'S'){
        cout << "Qual a número da unidade?" << endl;
        cin >> id;

        if(buscarQuartoPorID(id) != nullptr){
            cout << "Quarto de ID: " << id << ", já existe." << endl;
        }

        cout << "Qual o tipo da Unidade Habitacional? (1 - Quarto Standart ou 2 - Suíte de luxo)" << endl;
        cin >> tipo;

        cout << "Qual o dia do Check-in? (dd mm aaaa)" << endl;
        cin >> d >> m >> a;
        Data inicio(d, m, a);

        cout << "Qual o dia do Check-out? (dd mm aaaa)" << endl;
        cin >> d >> m >> a;
        Data fim(d, m, a);

        cout << "Qual o valor da diária?" << endl;
        cin >> diaria;

        switch(tipo){
            case 1:
            UHs.push_back(make_shared<QuartoStandard>(id, inicio, fim, diaria));
            break;

            case 2: {
                bool hidro;
                char res;
                cout << "O hóspede quer hidromassagem? (s ou n)" << endl;
                if(res == 's') hidro = true;
                else hidro == false;
                UHs.push_back(make_shared<SuiteLuxo>(id, inicio, fim, diaria, hidro));
                break;

            }

            default:
            break;
        }
        cout << "Deseja cadastrar um novo quarto? (s ou n)" << endl;
        cin >> res;
    }
    }
    
    void listarTodas(){
        cout << endl;
        for(auto a : UHs){
            cout << "Unidade " << a->getId() << ":" << endl;
            a->exibirInfo();
        }
    }

    void exibirUm(){
        int id;
        cout << "Qual a número da unidade que deseja exibir?" << endl;
        cin >> id;
        if(buscarQuartoPorID(id) != nullptr){
            buscarQuartoPorID(id).get()->exibirInfo();
            return;
        } else{
            cout << "Unidade não econtrada." << endl;
            return;
        }
    }

    void alterar(){
        int id;
        int res2;
        char res1 = 's';
        cout << "Qual o número da unidade que deseja alterar?" << endl;
        cin >> id;
        if(buscarQuartoPorID(id) != nullptr){
            while(res2 == 's' || res2 == 'S'){
                cout << "O que deseja alterar?" << endl
                << "1. Período de ocupação do hóspede atual" << endl
                << "2. Alterar ou adicionar hóspede" << endl
                << "3. retornar ao menu inicial" << endl;

                switch(res1){
                    case 1: {
                        if(buscarQuartoPorID(id).get()->getOcupado() == true){
                            int d, m, a;
                            cout << "Digite a data de início: (dd mm aaaa)" << endl;
                            cin >> d >> m >> a;
                            Data inicio(d, m, a);

                            cout << "Digite a data de término: (dd mm aaaa)" << endl;
                            cin >> d >> m >> a;
                            Data fim(d, m, a);
                            
                            alterarData(id, inicio, fim);
                        } else cout << "Quarto ainda não está ocupado, cadastre um novo hóspede." << endl;
                        break;
                    }

                    case 2: {
                        if(buscarQuartoPorID(id).get()->getOcupado() == true){
                            cout << "Qual o CPF do hóspede que deseja alterar?" << endl;
                            string cpfPesquisado;
                            getline(cin, cpfPesquisado);

                            for(auto& a : clientes){
                                if(cpfPesquisado == a.get()->getCpf()){
                                    cout << "O que deseja alterar do(a) cliente " << a.get()->getNome() << "?" << endl;
                                    cout << "1. Nome" << endl
                                    << "2. CPF" << endl
                                    << "3. Data de nascimento" << endl
                                    << "4. Fatura" << endl;
                                    
                                    int res;
                                    cin >> res;
                                    cin.ignore();
                                    switch(res){
                                        case 1: {
                                            string novoNome;
                                            cout << "Digite o novo nome:" << endl;
                                            getline(cin, novoNome);
                                            a.get()->setNome(novoNome);
                                            cout << "Novo nome cadastrado!" << endl;
                                            break;
                                        }
                                        
                                        case 2: {
                                            string novoCPF;
                                            cout << "Digite o novo CPF:" << endl;
                                            getline(cin, novoCPF);
                                            a.get()->setCpf(novoCPF);
                                            cout << "Novo CPF cadastrado!" << endl;
                                            break;
                                        }

                                        case 3: {
                                            int d, m, ano;
                                            cout << "Digite a nova data de nascimento: (dd mm aaaa)" << endl;
                                            cin >> d >> m >> ano;
                                            Data novaData(d, m, ano);
                                            a.get()->setData(d, m, ano);
                                            cout << "Nova data de nascimento cadastrada!" << endl;
                                            break;
                                        }

                                        case 4: {
                                            string nome, tipo;
                                            double preco;
                                            int quantidade;

                                            cout << "Insira o nome:" << endl;
                                            getline(cin, nome);
                                            cout << "Insira o tipo:" << endl;
                                            getline(cin, tipo);
                                            cout << "Insira o preço do produto e logo após, a quantidade" << endl;
                                            cin >> preco >> quantidade;

                                            Despesa novaDespesa(nome, tipo, preco, quantidade);

                                            a.get()->getFatura().addDespesa(novaDespesa);
                                            break;
                                        }

                                        default:
                                        cout << "Caractere inválido." << endl;
                                        break;
                                    }
                                } else{
                                    cout << "CPF não encontrado." << endl;
                                }
                            }
                        } else cadastrarCliente();
                    }
                }
            }
        } else{
            cout << "Unidade não encontrada." << endl;
            return;
        }
    }

    void menu(){
        //cout do menu usando iomanip
    }
    
    void remover(){
        int id;
        cout << "Qual a número da unidade que deseja remover?" << endl;
        cin >> id;
        if(buscarQuartoPorID(id) != nullptr){
            buscarQuartoPorID(id).get()->liberarUH();
            cout << "Quarto removido." << endl;
            return;
        } else{
            cout << "Unidade não encontrada." << endl;
            return;
        }
    }

    void exibirRelatorio(){
        //UH por UH?
    }

    void salvarDados(){
        //oqueéisso
    }

    void carregarDados(){
        //oqueéisso
    }
};