#define FILAELEITOR_H
// biblioteca da fila de eleitores criada com POO
#include <iostream>
#include <string>
using namespace std;
// Struct N� do eleitor 
struct Eleitor {
    int titulo;
    string nome;
    Eleitor* proximo;
};
// declaracao de uma classe para a fila
class FilaEleitor {
private:
	// atributos primeiro posicao e ultima posicao da fila
    Eleitor* primeiro;
    Eleitor* ultimo;

public:
	// m�todo construtor, declarando primeiro e ultimo como NULL
    FilaEleitor() {
        primeiro = NULL;
        ultimo = NULL;
    }
	// metodo que verifica se a fila est� vazia
    bool estaVazia() {
        return primeiro == NULL;
    }
	// metodo que faz a insercao de novos eleitores na fila
    void enfileirar(int titulo, const string &nome) {
    	// alocacao de um novo n� eleitor
        Eleitor* novoEleitor = new Eleitor;
        novoEleitor->titulo = titulo;
        novoEleitor->nome = nome;
        novoEleitor->proximo = NULL;
		// verificando se est� vazia, caso sim, a primeira e ultima posicao recebem o novo eleitor
        if (estaVazia()) {
            primeiro = novoEleitor;
            ultimo = novoEleitor;
            // caso contr�rio, a ultima posicao apontara para o novoEleitor
        } else {
            ultimo->proximo = novoEleitor;
            ultimo = novoEleitor;
        }

        cout << "Eleitor " << nome << " adicionado � fila." << endl;
    }
	// metodo que retira o primeiro elemento da fila
    void desenfileirar() {
        if (estaVazia()) {
            cout << "A fila est� vazia." << endl;
            return;
        }
		// declarando um ponteiro auxiliar que recebera o proximo elemento da fila
        Eleitor* eleitorRemovido = primeiro;
        primeiro = primeiro->proximo;

        if (primeiro == NULL) {
            ultimo = NULL;
        }
		
        cout << "Eleitor " << eleitorRemovido->nome << " removido da fila." << endl;
        delete eleitorRemovido;
    }
	// metodo responsavel por percorrer a fila e exibir suas informa��es
    void exibirFila() {
        if (estaVazia()) {
            cout << "A fila est� vazia." << endl;
            return;
        }

        Eleitor* atual = primeiro;
        cout << "Fila de eleitores:" << endl;
        while (atual != NULL) {
            cout << "T�tulo: " << atual->titulo << ", Nome: " << atual->nome << endl;
            atual = atual->proximo;
        }
    }
    // metodo responsavel por cadastrar o voto do eleitor
	int votar() {
    if (estaVazia()) {
        cout << "A fila est� vazia" << endl;
        return -1; // Ou qualquer outro valor indicando uma situa��o de erro
    }
    // retornando o numero do titulo do eleitor para cadastrar na lista encadeada
    Eleitor* atual = primeiro;
    while (atual != NULL) {
        return atual->titulo;
        atual = atual->proximo;
    }

    return -1; // Se a execu��o chegar aqui, significa que n�o foi poss�vel encontrar o t�tulo de eleitor
}
	//metodo destrutor, desalocando a memoria da lista encadeada de eleitores
    ~FilaEleitor() {
    Eleitor* atual = primeiro;
    while (atual != NULL) {
        Eleitor* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
}
};
