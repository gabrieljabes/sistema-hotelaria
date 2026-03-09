#pragma once
#include "UH.h"
#include "SuiteLuxo.h"
#include "QuartoStandard.h"
#include <iomanip>
#include <fstream>

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
        auto quarto = buscarQuartoPorID(id);
        if(quarto != nullptr){
            quarto->alterarPeriodo(inicio, fim);
            cout << "Período do quarto " << id << " alterado com sucesso!" << endl;
            return true;
        }
        
        cout << "Erro: Quarto não encontrado." << endl;
        return false;
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

    void cadastrarCliente(shared_ptr<Pessoa> novoCliente){
        clientes.push_back(novoCliente);
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
                continue; //se n continua executando o resto pow
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
                    //força a repetição mudando o estado dela pra não passar no while
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
        if(UHs.empty()){
            cout << "\nNenhuma Unidade Habitacional cadastrada no sistema ainda." << endl;
            return;
        }

        // guarda a formatação original
        ios_base::fmtflags f(cout.flags());

        cout << "\n==========================================================================" << endl;
        // cabeçalho da tabela com as larguras fixas pras colunas
        cout << left << setw(6)  << "ID" 
             << left << setw(20) << "Tipo da Unidade" 
             << left << setw(15) << "Diária (R$)" 
             << left << setw(12) << "Status" 
             << "Período" << endl;
        cout << "--------------------------------------------------------------------------" << endl;

        cout << fixed << setprecision(2);

        for(auto& quarto : UHs){
            // printa os dados respeitando os mesmos espaços do cabeçalho
            cout << left << setw(6)  << quarto->getId()
                 << left << setw(20) << quarto->getTipoString();
                 
            cout << "R$ " << left << setw(12) << quarto->getValorDiaria();

            if(quarto->getOcupado()){
                cout << left << setw(12) << "[Ocupado]";
            } else {
                cout << left << setw(12) << "[Livre]";
            }

            cout << quarto->getPeriodo().stringPeriodo() << endl;
        }
        
        cout << "==========================================================================\n" << endl;
        // restaura a formatação do cout
        cout.flags(f);
    }

    void listarHospedes(){
        int id;
        cout << "Qual a unidade você deseja ver?" << endl;
        cin >> id;

        if(buscarQuartoPorID(id) != nullptr){
            for(int i = 0; i < buscarQuartoPorID(id).get()->getQuantidadeHospedes(); i++){
                cout << "Dados do cliente " << buscarQuartoPorID(id).get()->getHospede(i)->getNome() << ":" << endl;
                cout << "CPF: " << buscarQuartoPorID(id).get()->getHospede(i)->getCpf() << endl
                << "Data de Nascimento: " << buscarQuartoPorID(id).get()->getHospede(i)->getData().toStringData() << endl
                << "Fatura total: " << buscarQuartoPorID(id).get()->getHospede(i)->getFatura().calcularTotal() << endl;
            }
        } else{
            cout << "Unidade não econtrada." << endl;
            return;
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


    int pesquisarPorCpf(string cpfBusca) {
        for (int i = 0; i < clientes.size(); i++) {
            if (clientes[i]->getCpf() == cpfBusca) {
                return i; 
            }
        }
        return -1; 
    }

    void exibirClienteEFatura() {
        string cpfBusca;
        cout << "\nQual o CPF do cliente que deseja consultar?" << endl;
        cin.ignore(10000, '\n');
        getline(cin, cpfBusca);

        int index = pesquisarPorCpf(cpfBusca);

        if (index != -1) {
            auto cliente = clientes[index]; 
            ios_base::fmtflags f(cout.flags()); 

            cout << "\n=================================================" << endl;
            cout << "                 DADOS DO CLIENTE                " << endl;
            cout << "=================================================" << endl;
            cout << "Nome : " << cliente->getNome() << endl;
            cout << "CPF  : " << cliente->getCpf() << endl;
            cout << "Nasc : " << cliente->getData().toStringData() << endl;
            cout << "-------------------------------------------------" << endl;
            cout << "                 FATURA INDIVIDUAL               " << endl;
            cout << "-------------------------------------------------" << endl;
            
            if (cliente->getFatura().calcularTotal() > 0) {
                cliente->getFatura().exibirGastos();
                cout << fixed << setprecision(2);
                cout << "\nTotal acumulado na fatura: R$ " << cliente->getFatura().calcularTotal() << endl;
            } else {
                cout << "Nenhuma despesa registrada para este cliente." << endl;
            }
            cout << "=================================================\n" << endl;

            cout.flags(f);
        } else {
            cout << "Erro: Nenhum cliente encontrado com o CPF informado." << endl;
        }
    }

    void alterar(){
        int id;
        int res1;
        cout << "\nQual o número da unidade que deseja alterar?" << endl;
        cin >> id;

        auto quarto = buscarQuartoPorID(id);
        
        if(quarto != nullptr){
            bool continuar = true;
            
            while(continuar){
                cout << "1. Alterar período de ocupação" << endl;
                cout << "2. Gerenciar hóspedes (Adicionar ou Editar)" << endl;
                cout << "3. Retornar ao menu principal" << endl;
                cout << "Escolha uma opcao: ";
                cin >> res1;

                switch(res1){
                    case 1: {
                        if(quarto->getOcupado() == true){
                            int d, m, a;
                            cout << "Digite a nova data de Check-in (dd mm aaaa):" << endl;
                            cin >> d >> m >> a;
                            Data inicio(d, m, a);

                            cout << "Digite a nova data de Check-out (dd mm aaaa):" << endl;
                            cin >> d >> m >> a;
                            Data fim(d, m, a);
                            
                            alterarData(id, inicio, fim);
                        } else {
                            cout << "Erro: Quarto vazio. Adicione um hóspede primeiro para definir o período." << endl;
                        }
                        break;
                    }

                    case 2: {
                        int opcaoHospede;
                        cout << "1. Vincular cliente EXISTENTE a um quarto" << endl;
                        cout << "2. Cadastrar NOVO cliente e adicionar ao quarto" << endl;
                        cout << "3. Alterar dados de um hóspede que JÁ ESTÁ no quarto" << endl;
                        cout << "Escolha uma opcao: ";
                        cin >> opcaoHospede;

                        if (opcaoHospede == 1) {
                            string cpfBusca;
                            cout << "Digite o CPF do cliente existente: ";
                            cin.ignore(10000, '\n');
                            getline(cin, cpfBusca);

                            // Usa o nosso método genial que retorna o índice!
                            int index = pesquisarPorCpf(cpfBusca);
                            if (index != -1) {
                                quarto->addHospede(clientes[index].get());
                                cout << "Cliente " << clientes[index]->getNome() << " vinculado ao quarto com sucesso!" << endl;
                            } else {
                                cout << "Erro: CPF não encontrado. Cadastre o cliente primeiro." << endl;
                            }
                        } 
                        else if (opcaoHospede == 2) {
                            // Cadastra e já vincula
                            auto novoHospede = cadastrarCliente(); 
                            quarto->addHospede(novoHospede.get());
                            cout << "Novo cliente cadastrado e vinculado ao quarto com sucesso!" << endl;
                        } 
                        else if (opcaoHospede == 3) {
                            if (quarto->getOcupado()) {
                                cout << "Qual o CPF do hóspede que deseja alterar?" << endl;
                                string cpfPesquisado;
                                cin.ignore(10000, '\n');
                                getline(cin, cpfPesquisado);

                                // Confirma se o CPF digitado realmente pertence a alguém DENTRO deste quarto
                                Pessoa* p = quarto->getHospedePorCPF(cpfPesquisado);
                                
                                if (p != nullptr) {
                                    cout << "\nO que deseja alterar em " << p->getNome() << "?" << endl;
                                    cout << "1. Nome" << endl;
                                    cout << "2. CPF" << endl;
                                    cout << "3. Data de nascimento" << endl;
                                    
                                    int res;
                                    cin >> res;
                                    cin.ignore(10000, '\n');

                                    switch(res){
                                        case 1: {
                                            string novoNome;
                                            cout << "Digite o novo nome: ";
                                            getline(cin, novoNome);
                                            p->setNome(novoNome);
                                            cout << "Nome atualizado com sucesso!" << endl;
                                            break;
                                        }
                                        case 2: {
                                            string novoCPF;
                                            cout << "Digite o novo CPF: ";
                                            getline(cin, novoCPF);
                                            p->setCpf(novoCPF);
                                            cout << "CPF atualizado com sucesso!" << endl;
                                            break;
                                        }
                                        case 3: {
                                            int d, m, ano;
                                            cout << "Digite a nova data de nascimento (dd mm aaaa): ";
                                            cin >> d >> m >> ano;
                                            p->setData(d, m, ano);
                                            cout << "Data atualizada com sucesso!" << endl;
                                            break;
                                        }
                                        default:
                                            cout << "Opção inválida." << endl;
                                            break;
                                    }
                                } else {
                                    cout << "Erro: Este CPF não pertence a nenhum hóspede cadastrado neste quarto." << endl;
                                }
                            } else {
                                cout << "Erro: Não há hóspedes neste quarto para alterar." << endl;
                            }
                        }
                        break;
                    }
                    case 3: {
                        continuar = false;
                        cout << "Retornando ao menu principal..." << endl;
                        break;
                    }

                    default: {
                        cout << "Opção inválida, tente novamente." << endl;
                        break;
                    }
                }
            }
        } else {
            cout << "Erro: Unidade Habitacional não encontrada." << endl;
        }
    }

    void adicionarDespesaPorCPF() {
        string cpfBusca;
        cout << "\nQual o CPF do hóspede para lançar a despesa?" << endl;
        cin.ignore(10000, '\n');
        getline(cin, cpfBusca);

        // Reutilizando o método de pesquisa de novo!
        int index = pesquisarPorCpf(cpfBusca);

        if (index != -1) {
            auto cliente = clientes[index];
            string nomeItem, tipo;
            double preco;
            int quantidade;

            cout << "\nLançando despesa para: " << cliente->getNome() << endl;
            cout << "Nome do item (ex: Água): ";
            getline(cin, nomeItem);
            cout << "Tipo da despesa (ex: Frigobar): ";
            getline(cin, tipo);
            cout << "Valor unitário: R$ ";
            cin >> preco;
            cout << "Quantidade: ";
            cin >> quantidade;

            Despesa novaDespesa(nomeItem, tipo, preco, quantidade);
            cliente->getFatura().addDespesa(novaDespesa);
            
            cout << "\n[ Sucesso! Despesa adicionada à fatura de " << cliente->getNome() << " ]" << endl;
        } else {
            cout << "Erro: Nenhum cliente encontrado com o CPF informado." << endl;
        }
    }

    void menu(){
        int res = 1;
        while(res != 0){
            cout << "\n" << setfill('=') << setw(60) << "=" << endl;
            cout << setfill(' ') << setw(32) << "HOTEL" << endl;
            cout << setfill('=') << setw(60) << "=" << endl;
            
            
            cout << left << setw(5) << "1" << " - Cadastrar Unidade Habitacional" << endl;
            cout << left << setw(5) << "2" << " - Cadastrar Novo Cliente" << endl;
            
            cout << left << setw(5) << "3" << " - Listar Unidades Habitacionais" << endl;
            cout << left << setw(5) << "4" << " - Exibir Unidade Específica" << endl;
            cout << left << setw(5) << "5" << " - Exibir Cliente e Fatura (por CPF)" << endl;
            
            cout << left << setw(5) << "6" << " - Lançar Despesa (por CPF)" << endl;
            cout << left << setw(5) << "7" << " - Alterar Dados (Quarto/Hóspede)" << endl;
            
            cout << left << setw(5) << "8" << " - Checkout de Unidade (Remover)" << endl;
            cout << left << setw(5) << "9" << " - Exibir Relatório Gerencial" << endl;
            
            cout << left << setw(5) << "0" << " - Sair e Salvar" << endl;
            cout << setfill('-') << setw(60) << "-" << endl;
            
            cout << "Escolha uma opcao: ";
            cin >> res;
        
            switch(res){
                case 1: 
                    cadastrarQuarto(); 
                    break;
                case 2: 
                    cadastrarCliente(); 
                    cout << "\n[ Cliente cadastrado com sucesso no sistema! ]" << endl;
                    break;
                case 3: listarTodas(); break;
                case 4: exibirIndividual(); break;
                case 5: exibirClienteEFatura(); break;
                case 6: adicionarDespesaPorCPF(); break;
                case 7: alterar(); break;
                case 8: remover(); break;
                case 9: exibirRelatorio(); break;
                case 0: cout << "Saindo e guardando os dados..." << endl; break;
                default: cout << "Opção inválida." << endl; break;
            }

            if (res != 0) {
                cout << "\n[ Pressione ENTER para retornar ao menu ]";
                cin.ignore(10000, '\n');
                cin.get();
            }
        }
    }
    
    void remover(){
        int id;
        cout << "Qual a número da unidade que deseja remover?" << endl;
        cin >> id;

        auto quarto = buscarQuartoPorID(id);

        if(quarto != nullptr){
            if(quarto->getOcupado()){
                quarto->exibirCheckout(); 
                quarto->liberarUH();
                cout << "Checkout concluído. Quarto liberado." << endl;
            } else {
                cout << "Este quarto já está livre." << endl;
            }
        } else{
            cout << "Unidade não encontrada." << endl;
        }
    }

    void exibirRelatorio(){
        int totalQuartos = UHs.size();
        int ocupados = 0;
        double receitaPrevista = 0.0;
        int totalClientes = clientes.size();

        for(auto& quarto : UHs){
            if(quarto->getOcupado()){
                ocupados++;
                receitaPrevista += quarto->calcularCheckout();
            }
        }
        ios_base::fmtflags f(cout.flags());
    
        cout << "\n===================================================" << endl;
        cout << "               RELATÓRIO GERENCIAL                 " << endl;
        cout << "===================================================" << endl;
        cout << "Total de clientes cadastrados : " << totalClientes << endl;
        cout << "Total de Unidades (UHs)       : " << totalQuartos << endl;
        cout << "UHs Ocupadas                  : " << ocupados << endl;
        cout << "UHs Livres                    : " << (totalQuartos - ocupados) << endl;
        
        cout << fixed << setprecision(2);
        cout << "Receita Bruta Prevista        : R$ " << receitaPrevista << endl;
        cout << "===================================================\n" << endl;
        
        cout.flags(f);
    }

    

void salvarDados() {
        ofstream arquivo("dados_hotel.txt");
        if (!arquivo.is_open()) return;

        arquivo << clientes.size() << endl;
        for (auto& c : clientes) {
            string nomeFormatado = c->getNome();
            replace(nomeFormatado.begin(), nomeFormatado.end(), ' ', '_'); 
            
            arquivo << nomeFormatado << " " << c->getCpf() << " "
                    << c->getData().getDia() << " " << c->getData().getMes() << " " << c->getData().getAno();

            int qtdDespesas = c->getFatura().getQuantDespesas();
            arquivo << " " << qtdDespesas << endl;

            for (int j = 0; j < qtdDespesas; j++) {
                Despesa d = c->getFatura().getDespesa(j);
                
                string nomeDespesa = d.getNome();
                replace(nomeDespesa.begin(), nomeDespesa.end(), ' ', '_');
                
                string tipoDespesa = d.getTipo();
                replace(tipoDespesa.begin(), tipoDespesa.end(), ' ', '_');

                arquivo << nomeDespesa << " " << tipoDespesa << " " 
                        << d.getValor() << " " << d.getQuantidade() << endl;
            }
        }
        arquivo << UHs.size() << endl;
        for (auto& quarto : UHs) {
            arquivo << quarto->getTipo() << " " << quarto->getId() << " "
                    << quarto->getPeriodo().getDataInicio().getDia() << " "
                    << quarto->getPeriodo().getDataInicio().getMes() << " "
                    << quarto->getPeriodo().getDataInicio().getAno() << " "
                    << quarto->getPeriodo().getDataFim().getDia() << " "
                    << quarto->getPeriodo().getDataFim().getMes() << " "
                    << quarto->getPeriodo().getDataFim().getAno() << " "
                    << quarto->getValorDiaria();

            if (quarto->getTipo() == 2) {
                auto suite = dynamic_pointer_cast<SuiteLuxo>(quarto);
                if (suite) arquivo << " " << suite->getHidromassagem();
            }
            
            arquivo << " " << quarto->getQuantidadeHospedes();
            for(int j = 0; j < quarto->getQuantidadeHospedes(); j++){
                arquivo << " " << quarto->getHospede(j)->getCpf();
            }

            arquivo << endl;
        }
        arquivo.close();
        cout << "[ Base de dados guardada com sucesso no disco! ]" << endl;
    }

    void carregarDados() {
        ifstream arquivo("dados_hotel.txt");
        if (!arquivo.is_open()) return;

        clientes.clear();
        UHs.clear();

        int qtdClientes;
        if (arquivo >> qtdClientes) { 
            for (int i = 0; i < qtdClientes; i++) {
                string nome, cpf;   
                int d, m, a, qtdDespesas;

                arquivo >> nome >> cpf >> d >> m >> a >> qtdDespesas;
                replace(nome.begin(), nome.end(), '_', ' '); 
                
                auto novoCliente = make_shared<Pessoa>(nome, cpf, Data(d, m, a));

                for(int j = 0; j < qtdDespesas; j++) {
                    string nomeDespesa, tipoDespesa;
                    double valor;
                    int quantidade;

                    arquivo >> nomeDespesa >> tipoDespesa >> valor >> quantidade;
                    
                    replace(nomeDespesa.begin(), nomeDespesa.end(), '_', ' ');
                    replace(tipoDespesa.begin(), tipoDespesa.end(), '_', ' ');

                    Despesa novaDespesa(nomeDespesa, tipoDespesa, valor, quantidade);
                    novoCliente->getFatura().addDespesa(novaDespesa);
                }

                clientes.push_back(novoCliente);
            }
        }
        int qtdQuartos;
        if (arquivo >> qtdQuartos) {
            for (int i = 0; i < qtdQuartos; i++) {
                int tipo, id, dI, mI, aI, dF, mF, aF;
                double diaria;
                arquivo >> tipo >> id >> dI >> mI >> aI >> dF >> mF >> aF >> diaria;
                Data inicio(dI, mI, aI);
                Data fim(dF, mF, aF);

                shared_ptr<UnidadeHabitacional> novoQuarto;

                if (tipo == 1) {
                    novoQuarto = make_shared<QuartoStandard>(id, inicio, fim, diaria);
                } else if (tipo == 2) {
                    bool hidro;
                    arquivo >> hidro;
                    novoQuarto = make_shared<SuiteLuxo>(id, inicio, fim, diaria, hidro);
                }

                int qtdHospedesNoQuarto;
                arquivo >> qtdHospedesNoQuarto;
                for(int j = 0; j < qtdHospedesNoQuarto; j++){
                    string cpfBusca;
                    arquivo >> cpfBusca;
                    
                    for(auto& c : clientes){
                        if(c->getCpf() == cpfBusca){
                            novoQuarto->addHospede(c.get()); 
                            break;
                        }
                    }
                }

                UHs.push_back(novoQuarto);
            }
        }
        arquivo.close();
        cout << "[ Dados carregados: " << clientes.size() << " clientes e " << UHs.size() << " quartos. ]" << endl;
    }
};