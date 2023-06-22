#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include "FilaEleitor.h"

using namespace std;

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
void sobrescreveArquivo(Candidato *&lista){
	 ofstream arquivo("Candidatos.txt");
    if (arquivo.is_open()) {
        Candidato *atual = lista;
        while (atual != NULL) {
            arquivo << atual->nome << ", " << atual->numero << endl;
            atual = atual->proximo;
        }
        arquivo.close();
    } else {
        cout << "Erro ao sobrescrever o arquivo" << endl;
    }
}
void liberarMemoriaC(Candidato *&lista){
	Candidato *candidatoAtual = NULL;
	if(lista == NULL){
		cout << "Lista está vazia";
		
		
	}else{
		candidatoAtual = lista;
		while(candidatoAtual != NULL){
			Candidato *prox = candidatoAtual->proximo;
			delete candidatoAtual;
			candidatoAtual = prox;
		}
		lista = NULL;
	}
}
void removeCandidato(Candidato *&lista) {
    carregarCandidatos(lista);

    if (lista == NULL) {
        cout << "Nenhum candidato cadastrado até o momento" << endl;
    } else {
    	listarCandidatos(lista);
        int num = 0;
        cout << "Informe o número do candidato que deseja excluir: ";
        cin >> num;

        Candidato *auxiliar = NULL;
        Candidato *atual = lista;

        while (atual != NULL) {
            if (num == atual->numero) {
                if (auxiliar == NULL) {
                    lista = atual->proximo;
                } else {
                    auxiliar->proximo = atual->proximo;
                }
                delete atual;
                cout << "Candidato removido com sucesso" << endl;
                break;
            } else {
                auxiliar = atual;
                atual = atual->proximo;
            }
        }
        sobrescreveArquivo(lista);
    }

    liberarMemoriaC(lista);
}

int menuEleitores(){
	cout << "Menu de eleitores"<<endl;
	cout << "--------------------" << endl;
	cout << "Escolha uma opção" << endl;
	cout << "[1] - Inserir novo eleitor" << endl;
	cout << "[2] - Listar eleitores cadastrados" << endl;
	cout << "[3] - Voltar" << endl;
	int subopc;
	cin >> subopc;
	return subopc;
}
void salvarEleitorEmArquivo(Eleitor *eleitor){
	ofstream arquivo("Eleitores.txt", ios::app);
    if (arquivo.is_open()) {
        arquivo << eleitor->nome << ", " << eleitor->titulo << endl;
        arquivo.close();
        cout << "Candidato salvo com sucesso no arquivo Candidatos.txt" << endl;
    } else {
        cout << "Não foi possível abrir o arquivo Candidatos.txt" << endl;
    }
}
void inserirEleitor(Eleitor*& lista, const std::string& nome, int numero){
	Eleitor* novoEleitor = new Eleitor;
    novoEleitor->nome = nome;
    novoEleitor->titulo = numero;
    novoEleitor->proximo = NULL;

    if (lista == NULL) {
        lista = novoEleitor;
        salvarEleitorEmArquivo(novoEleitor);
    } else {
        Eleitor* ultimo = lista;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = novoEleitor;
        salvarEleitorEmArquivo(novoEleitor);
    }
}
void cadastraEleitor(Eleitor *lista){
	string nome;
	int num;
	cout << "Insira o nome do Eleitor: ";
	cin >> nome;
	cout << "Insira o numero do titulo de eleitor: ";
	cin >> num;
	inserirEleitor(lista, nome, num);
}
void carregarEleitores(Eleitor *&lista) {
    ifstream arquivo("Eleitores.txt");
    if (arquivo.is_open()) {
        string nome;
        int numero;
        while (arquivo >> nome >> numero) {
            Eleitor* novoEleitor = new Eleitor;
            novoEleitor->nome = nome;
            novoEleitor->titulo = numero;
            novoEleitor->proximo = NULL;

            if (lista == NULL) {
                lista = novoEleitor;
            } else {
                Eleitor* atual = lista;
                while (atual->proximo != NULL) {
                    atual = atual->proximo;
                }
                atual->proximo = novoEleitor;
            }
        }
        arquivo.close();
        cout << "Eleitores carregados com sucesso!" << endl;
    } else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }
    
    
}
bool verificaElegibilidade(int titulo,Eleitor *lista){
	Eleitor *eleitorAtual = lista;
	bool boolean;
	if(lista == NULL){
		cout << "Não há eleitor há ser exibido";
		return false;
	}else{
		while(eleitorAtual != NULL){
			if(eleitorAtual->titulo == titulo){
				boolean =  true;
			
			eleitorAtual = eleitorAtual->proximo;
		}
		return boolean;
	}
}
}
void liberarMemoriaE(Eleitor *&lista){
	Eleitor *eleitorAtual = NULL;
	if(lista == NULL){
		cout << "Lista está vazia";
		
		
	}else{
		eleitorAtual = lista;
		while(eleitorAtual != NULL){
			Eleitor *prox = eleitorAtual->proximo;
			delete eleitorAtual;
			eleitorAtual = prox;
		}
		lista = NULL;
	}
}
void listarEleitores(const Eleitor* lista) {
    if (lista == NULL) {
        cout << "Nenhum candidato cadastrado." << endl;
        return;
    }
    
    const Eleitor* eleitorAtual = lista;
    while (eleitorAtual != NULL) {
        cout << "Nome: " << eleitorAtual->nome << " Número: " << eleitorAtual->titulo << endl;
        eleitorAtual = eleitorAtual->proximo;
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

void insereFila(FilaEleitor*& fila, Eleitor *lista){
	int titulo;
	
	cout << "Entre na fila de votação!" << endl;
	cout << "Insira o numero de seu título de eleitor: ";
	cin >> titulo;
	
	if(verificaElegibilidade(titulo, lista)){
		
		cout << "Título verificado, entrando na fila de votação ..." << endl;
		Eleitor *eleitorAtual = lista;
		while(eleitorAtual != NULL){
			if(eleitorAtual->titulo == titulo){
				fila->enfileirar(titulo, eleitorAtual->nome);
				fila->exibirFila();
			}
			eleitorAtual = eleitorAtual->proximo;
		}
		
		
	}else{
		cout << "Você não está elegível para votar, regularize seu cadastro!" << endl;
	}
	
}
int menuVoto(){
	int opc;
	cout << "Votação " << endl;
	cout << "Insira a opção correspondente" << endl;
	cout << "[1] - Cadastro na fila de votação" << endl;
	cout << "[2] - Votar" << endl;
	cout << "[3] - Retornar" << endl;
	cin >> opc;
	return opc;
}
int main() {
	setlocale(LC_ALL, "Portuguese");
	FilaEleitor *fila = new FilaEleitor();
	
	int opc = menu();
	Candidato *listacandidatos = NULL;
	Eleitor *listaeleitores = NULL;
	
	while(opc !=5){
		int subopc;
		if(opc == 1){
			subopc = menuCandidatos();
			while(subopc !=4){
				if(subopc == 1){
					cadastrarCandidato(listacandidatos);
					liberarMemoriaC(listacandidatos);
				}else if(subopc == 2){
					carregarCandidatos(listacandidatos);
					listarCandidatos(listacandidatos);
					liberarMemoriaC(listacandidatos);
					
				}else if(subopc == 3){
					removeCandidato(listacandidatos);
				}else{
					cout << "Informe uma opção válida!" << endl;
				}
				subopc = menuCandidatos();
			}
		}else if(opc == 2){
			subopc = menuEleitores();
			while(subopc !=3){
				if(subopc == 1){
					
					cadastraEleitor(listaeleitores);
					
				}else if(subopc == 2){
					carregarEleitores(listaeleitores);
					listarEleitores(listaeleitores);
					liberarMemoriaE(listaeleitores);
				}
				subopc = menuEleitores();
			}
		}else if(opc == 3){
			subopc = menuVoto();
			while(subopc != 3){
				if(subopc == 1 ){
					
					carregarEleitores(listaeleitores);
					insereFila(fila, listaeleitores);
				}
				subopc = menuVoto();
			}
			
		}else if(opc == 4){
			
		}else{
			cout << "Opção inválida"<<endl;
		}
		opc = menu();
	}
	delete fila;
}


