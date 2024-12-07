#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <set>

#define TAM 5
#define FREE "FREE"
#define RED "\033[1;31m"
#define RESET "\033[0m"

using namespace std;

// Estrutura para representar uma cartela
struct Cartela {
    int numeros[TAM][TAM];
    int marcados[TAM][TAM];

    void gerar() {
        int usados[75] = {0};
        for (int col = 0; col < TAM; col++) {
            int min = col * 15 + 1;
            int max = min + 14;
            for (int row = 0; row < TAM; row++) {
                if (col == 2 && row == 2) {
                    numeros[row][col] = 0;
                    marcados[row][col] = 1;
                    continue;
                }
                int numero;
                do {
                    numero = rand() % (max - min + 1) + min;
                } while (usados[numero]);
                usados[numero] = 1;
                numeros[row][col] = numero;
                marcados[row][col] = 0;
            }
        }
    }

    void exibir() {
        cout << " B   I   N   G   O\n";
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                if (i == 2 && j == 2) {
                    cout << setw(4) << FREE;
                } else if (marcados[i][j]) {
                    cout << RED << setw(4) << numeros[i][j] << RESET;
                } else {
                    cout << setw(4) << numeros[i][j];
                }
            }
            cout << endl;
        }
    }

    bool marcarNumero(int numero) {
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                if (numeros[i][j] == numero) {
                    marcados[i][j] = 1;
                    return true;
                }
            }
        }
        return false;
    }

    // Verifica padrões
    bool verificarPadroes() {
        for (int i = 0; i < TAM; i++) {
            if (all_of(marcados[i], marcados[i] + TAM, [](int v) { return v == 1; })) {
                cout << "LINHA!\n";
                return true;
            }
            bool colunaMarcada = true;
            for (int j = 0; j < TAM; j++) {
                if (marcados[j][i] == 0) colunaMarcada = false;
            }
            if (colunaMarcada) {
                cout << "COLUNA!\n";
                return true;
            }
        }
        bool cartelaCompleta = true;
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                if (marcados[i][j] == 0 && !(i == 2 && j == 2)) {
                    cartelaCompleta = false;
                }
            }
        }
        if (cartelaCompleta) {
            cout << "BINGO!\n";
            return true;
        }
        return false;
    }

    // Verifica se falta um número
    bool faltaUm() {
        int desmarcados = 0;
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                if (marcados[i][j] == 0 && !(i == 2 && j == 2)) {
                    desmarcados++;
                }
            }
        }
        if (desmarcados == 1) {
            cout << "Olha a boa!\n";
            return true;
        }
        return false;
    }
};

// Classe para representar um jogador
class Usuario {
public:
    string nome;
    int id;
    vector<Cartela> cartelas;

    Usuario(string n, int i) : nome(n), id(i) {}

    void adicionarCartelas(int quantidade) {
        for (int i = 0; i < quantidade; ++i) {
            Cartela novaCartela;
            novaCartela.gerar();
            cartelas.push_back(novaCartela);
        }
        cout << quantidade << " cartelas geradas para o usuário " << nome << ".\n";
    }

    void exibirCartelas() {
        for (size_t i = 0; i < cartelas.size(); ++i) {
            cout << "\nCartela " << i + 1 << ":\n";
            cartelas[i].exibir();
        }
    }

    bool marcarNumero(int numero) {
        bool encontrado = false;
        for (size_t i = 0; i < cartelas.size(); ++i) {
            if (cartelas[i].marcarNumero(numero)) {
                cout << "Número " << numero << " marcado na cartela " << i + 1 << ".\n";
                cartelas[i].verificarPadroes();
                cartelas[i].faltaUm();
                encontrado = true;
            }
        }
        return encontrado;
    }

    void salvarDados() {
        for (size_t i = 0; i < cartelas.size(); ++i) {
            ofstream arquivo("cartela_" + to_string(id) + "_" + to_string(i + 1) + ".txt");
            if (!arquivo) {
                cerr << "Erro ao salvar cartela " << i + 1 << ".\n";
                continue;
            }
            arquivo << "Cartela " << i + 1 << ":\n";
            for (int row = 0; row < TAM; row++) {
                for (int col = 0; col < TAM; col++) {
                    if (row == 2 && col == 2) {
                        arquivo << FREE << " ";
                    } else {
                        arquivo << cartelas[i].numeros[row][col] << " ";
                    }
                }
                arquivo << "\n";
            }
            arquivo.close();
        }
        cout << "Dados do usuário " << nome << " salvos com sucesso!\n";
    }
};

// Lista global para armazenar números chamados
set<int> numerosChamados;

// Função para gerar IDs únicos
int gerarID() {
    return rand() % 1000 + 1;
}

// Exibir os números já chamados
void exibirNumerosChamados() {
    cout << "Números já chamados: ";
    if (numerosChamados.empty()) {
        cout << "Nenhum número chamado ainda.\n";
    } else {
        for (int numero : numerosChamados) {
            cout << numero << " ";
        }
        cout << endl;
    }
}

// Menu principal
void menu() {
    vector<Usuario> usuarios;
    int opcao;
    do {
        cout << "\n=== Menu Principal ===\n";
        cout << "1. Cadastrar Usuário\n";
        cout << "2. Adicionar Cartelas ao Usuário\n";
        cout << "3. Exibir Cartelas de um Usuário\n";
        cout << "4. Marcar Número nas Cartelas\n";
        cout << "5. Exibir Números Já Chamados\n";
        cout << "6. Salvar Dados do Usuário\n";
        cout << "7. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;
        cin.ignore();

        switch (opcao) {
            case 1: {
                string nome;
                cout << "Digite o nome do usuário: ";
                getline(cin, nome);
                int id = gerarID();
                usuarios.emplace_back(nome, id);
                cout << "Usuário " << nome << " cadastrado com ID " << id << ".\n";
                break;
            }
            case 2: {
                int id;
                cout << "Digite o ID do usuário: ";
                cin >> id;
                auto it = find_if(usuarios.begin(), usuarios.end(), [&](Usuario &u) { return u.id == id; });
                if (it != usuarios.end()) {
                    int quantidade;
                    cout << "Quantas cartelas deseja gerar? ";
                    cin >> quantidade;
                    it->adicionarCartelas(quantidade);
                } else {
                    cout << "Usuário não encontrado.\n";
                }
                break;
            }
            case 3: {
                int id;
                cout << "Digite o ID do usuário: ";
                cin >> id;
                auto it = find_if(usuarios.begin(), usuarios.end(), [&](Usuario &u) { return u.id == id; });
                if (it != usuarios.end()) {
                    it->exibirCartelas();
                } else {
                    cout << "Usuário não encontrado.\n";
                }
                break;
            }
            case 4: {
                int id, numero;
                cout << "Digite o ID do usuário: ";
                cin >> id;
                auto it = find_if(usuarios.begin(), usuarios.end(), [&](Usuario &u) { return u.id == id; });
                if (it != usuarios.end()) {
                    cout << "Digite o número a ser marcado: ";
                    cin >> numero;
                    if (!it->marcarNumero(numero)) {
                        cout << "Número " << numero << " não encontrado em nenhuma cartela.\n";
                    } else {
                        numerosChamados.insert(numero);
                    }
                } else {
                    cout << "Usuário não encontrado.\n";
                }
                break;
            }
            case 5:
                exibirNumerosChamados();
                break;
            case 6: {
                int id;
                cout << "Digite o ID do usuário: ";
                cin >> id;
                auto it = find_if(usuarios.begin(), usuarios.end(), [&](Usuario &u) { return u.id == id; });
                if (it != usuarios.end()) {
                    it->salvarDados();
                } else {
                    cout << "Usuário não encontrado.\n";
                }
                break;
            }
            case 7:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção inválida.\n";
        }
    } while (opcao != 7);
}

int main() {
    srand(time(NULL));
    menu();
    return 0;
}
