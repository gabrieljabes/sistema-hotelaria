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

    shared_ptr<Pessoa> cadastrarCliente(){
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

        auto novoCliente = make_shared<Pessoa>(Nome, cpf, dataNasc);
        clientes.push_back(novoCliente);

        return novoCliente;
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
                continue; // se n continua executando o resto pow
            }

            cout << "Qual o tipo da Unidade Habitacional? (1 - Quarto Standart ou 2 - Suíte de luxo)" << endl;
            cin >> tipo;

            cout << "Qual o dia do Check-in? (dd mm aaaa)" << endl;
            Data inicio;
            do{
                cin >> d >> m >> a;
                inicio = Data(d, m, a);
            } while (!inicio.isValida());
            cout << "Qual o dia do Check-out? (dd mm aaaa)" << endl;
            Data fim;
            do{
                cin >> d >> m >> a;
                fim = Data(d, m, a);

                if(fim <= inicio && fim.isValida()){
                    cout << "Erro: A data de Check-out não pode ser anterior ou igual ao Check-in." << endl;
                    // força a repetição mudando o estado dela pra não passar no while
                    fim = Data(); 
                }

            } while (!fim.isValida());

            cout << "Qual o valor da diária?" << endl;
            cin >> diaria;

            switch(tipo){
                case 1:
                UHs.push_back(make_shared<QuartoStandard>(id, inicio, fim, diaria));
                break;

                case 2: {
                    bool hidro;
                    char resp;
                    cout << "O hóspede quer hidromassagem? (s ou n)" << endl;
                    cin >> resp;
                    if(resp == 's') 
                        hidro = true;
                    else
                        hidro = false;
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

    //metodo que ja aceita um objeto ja criado
    void cadastrarQuarto(shared_ptr<UnidadeHabitacional> novoQuarto){
        if(buscarQuartoPorID(novoQuarto->getId()) != nullptr){
            cout << "Erro: Quarto de ID " << novoQuarto->getId() << " já existe no sistema." << endl;
            return;
        }
        UHs.push_back(novoQuarto);
        cout << "Quarto " << novoQuarto->getId() << " cadastrado com sucesso!" << endl;
    }
    
    void listarTodas(){
        cout << endl;
        for(auto a : UHs){
            cout << "Unidade " << a->getId() << ":" << endl;
            a->exibirInfo();
        }
    }

    void exibirIndividual(){
        int id;
        cout << "Qual a número da unidade que deseja exibir?" << endl;
        cin >> id;
        if(buscarQuartoPorID(id) != nullptr){
            buscarQuartoPorID(id)->exibirInfo();
            return;
        } else{
            cout << "Unidade não econtrada." << endl;
            return;
        }
    }

    void exibirIndividual(int id){
        auto quarto = buscarQuartoPorID(id);
        
        if(quarto != nullptr){
            quarto->exibirInfo();
        } else {
            cout << "Quarto ID " << id << " não encontrado no sistema." << endl;
        }
    }

    void exibirFaturaUH(){
        int id;
        cout << "Qual a número da unidade que deseja exibir as faturas?" << endl;
        cin >> id;
        auto quarto = buscarQuartoPorID(id);
        if(quarto != nullptr){
            quarto->exibirFaturas();
            return;
        } else{
            cout << "Unidade não econtrada." << endl;
            return;
        }
    }


    void exibirFaturaUH(int id){
        auto quarto = buscarQuartoPorID(id);
        
        if(quarto != nullptr){
            quarto->exibirFaturas();
        } else {
            cout << "Quarto ID " << id << " não encontrado no sistema." << endl;
        }
    }
    void alterar(){
        int id;
        int res1;
        cout << "Qual o número da unidade que deseja alterar?" << endl;
        cin >> id;

        auto quarto = buscarQuartoPorID(id);
        
        if(quarto != nullptr){
            bool continuar = true;
            
            while(continuar){
                cout << "O que deseja alterar?" << endl
                << "1. Período de ocupação do hóspede atual" << endl
                << "2. Alterar ou adicionar hóspede" << endl
                << "3. retornar ao menu inicial" << endl;
                cin >> res1;

                switch(res1){
                    case 1: {
                        if(quarto->getOcupado() == true){
                            int d, m, a;
                            cout << "Digite a data de início: (dd mm aaaa)" << endl;
                            cin >> d >> m >> a;
                            Data inicio(d, m, a);

                            cout << "Digite a data de término: (dd mm aaaa)" << endl;
                            cin >> d >> m >> a;
                            Data fim(d, m, a);
                            
                            alterarData(id, inicio, fim);
                        } else
                            cout << "Quarto ainda não está ocupado, cadastre um novo hóspede." << endl;
                        break;
                    }

                    case 2: {
                        if(quarto->getOcupado() == true){
                            cout << "Qual o CPF do hóspede que deseja alterar?" << endl;
                            string cpfPesquisado;
                            cin.ignore();
                            getline(cin, cpfPesquisado);

                            bool clienteEncontrado = false;

                            for(auto& a : clientes){
                                if(cpfPesquisado == a.get()->getCpf()){
                                    clienteEncontrado = true;
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
                                            cout << "Despesa adicionada com sucesso!" << endl;
                                            break;
                                        }

                                        default:
                                            cout << "Caractere inválido." << endl;
                                            break;
                                    }
                                break; // encerra o for
                                }
                            }


                        if(!clienteEncontrado){
                            cout << "CPF não encontrado." << endl;
                        }
                        
                        } else{
                            auto novoHospede = cadastrarCliente();
                            // n tava vinculando o cliente ao quarto, ai fiz a funçao cadastrarcliente retornar o cliente novo e puxei aq
                            quarto->addHospede(novoHospede.get());
                            cout << "Novo hóspede cadastrado e vinculado ao quarto com sucesso!" << endl;
                        }
                        break;
                    }
                    case 3: {
                        continuar = false;
                        cout << "Retornando..." << endl;
                        break;
                    }

                    default: {
                        cout << "Opção inválida, tente novamente." << endl;
                        break;
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