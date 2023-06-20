#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fstream>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct Candidato{
	int numero;
	string nome;
	Candidato *proximo;
};

// Função que salva o candidato em um arquivo txt após executar a adição desse candidato à lista de candidatos
void salvarCandidatoEmArquivo(const Candidato* candidato) {
    ofstream arquivo("Candidatos.txt", ios::app);
    if (arquivo.is_open()) {
        arquivo << candidato->nome << ", " << candidato->numero << endl;
        arquivo.close();
        cout << "Candidato salvo com sucesso no arquivo Candidatos.txt" << endl;
    } else {
        cout << "Não foi possível abrir o arquivo Candidatos.txt" << endl;
    }
}

int menuCandidatos(){
	cout << "Menu de candidatos"<<endl;
	cout << "--------------------" << endl;
	cout << "Escolha uma opção" << endl;
	cout << "[1] - Inserir novo candidato" << endl;
	cout << "[2] - Listar candidatos cadastrados" << endl;
	cout << "[3] - Remover candidato" << endl;
	cout << "[4] - Voltar" << endl;
	int subopc;
	cin >> subopc;
	return subopc;
}

void inserirCandidato(Candidato*& lista, const std::string& nome, int numero) {
    Candidato* novoCandidato = new Candidato;
    novoCandidato->nome = nome;
    novoCandidato->numero = numero;
    novoCandidato->proximo = NULL;

    if (lista == NULL) {
        lista = novoCandidato;
        salvarCandidatoEmArquivo(novoCandidato);
    } else {
        Candidato* ultimo = lista;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = novoCandidato;
        salvarCandidatoEmArquivo(novoCandidato);
    }
}
void cadastrarCandidato(Candidato* lista){
	string nome;
	int num;
	cout << "Insira o nome do Candidato: ";
	cin >> nome;
	cout << "Insira o numero do candidato: ";
	cin >> num;
	inserirCandidato(lista, nome, num);
	 
}
void carregarCandidatos(Candidato*& lista) {
    ifstream arquivo("Candidatos.txt");
    if (arquivo.is_open()) {
        string nome;
        int numero;
        while (arquivo >> nome >> numero) {
            Candidato* novoCandidato = new Candidato;
            novoCandidato->nome = nome;
            novoCandidato->numero = numero;
            novoCandidato->proximo = NULL;

            if (lista == NULL) {
                lista = novoCandidato;
            } else {
                Candidato* atual = lista;
                while (atual->proximo != NULL) {
                    atual = atual->proximo;
                }
                atual->proximo = novoCandidato;
            }
        }
        arquivo.close();
        cout << "Candidatos carregados com sucesso!" << endl;
    } else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }
    
}
void listarCandidatos(const Candidato* lista) {
    if (lista == NULL) {
        cout << "Nenhum candidato cadastrado." << endl;
        return;
    }
    
    const Candidato* candidatoAtual = lista;
    while (candidatoAtual != NULL) {
        cout << "Nome: " << candidatoAtual->nome << " Número: " << candidatoAtual->numero << endl;
        candidatoAtual = candidatoAtual->proximo;
    }
}
int menu(){
	
	cout << "Menu de opções" << endl;
	cout << "Escolha uma opção"<<endl;
	cout << "[1] - Menu Candidatos" << endl;
	cout << "[2] - Menu Eleitores" << endl;
	cout << "[3] - Menu Votos" << endl;
	cout << "[4] - Menu relatórios"<<endl;
	cout << "[5] - Encerrar" << endl;
	int opc;
	cin >> opc;
	return opc;
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	int opc = menu();
	Candidato *listacandidatos = NULL;
	while(opc !=5){
		int subopc;
		if(opc == 1){
			subopc = menuCandidatos();
			while(subopc !=4){
				if(subopc == 1){
					cadastrarCandidato(listacandidatos);
				}else if(subopc == 2){
					carregarCandidatos(listacandidatos);
					listarCandidatos(listacandidatos);
				}
				subopc = menuCandidatos();
			}
		}else if(opc == 2){
			
		}else if(opc == 3){
			
		}else if(opc == 4){
			
		}else{
			cout << "Opção inválida"<<endl;
		}
		opc = menu();
	}
	delete(listacandidatos);
}


