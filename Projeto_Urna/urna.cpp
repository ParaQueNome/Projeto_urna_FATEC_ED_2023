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

struct Voto{
	int titulo;
	string nome;
	Voto *proximo;
};

// Fun��o que salva o candidato em um arquivo txt ap�s executar a adi��o desse candidato � lista de candidatos
void salvarCandidatoEmArquivo(const Candidato* candidato) {
    ofstream arquivo("Candidatos.txt", ios::app);
    if (arquivo.is_open()) {
        arquivo << candidato->nome << ", " << candidato->numero << endl;
        arquivo.close();
        cout << "Candidato salvo com sucesso no arquivo Candidatos.txt" << endl;
    } else {
        cout << "N�o foi poss�vel abrir o arquivo Candidatos.txt" << endl;
    }
}


int menuCandidatos(){
	cout << "Menu de candidatos"<<endl;
	cout << "--------------------" << endl;
	cout << "Escolha uma op��o" << endl;
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
        cout << "N�o foi poss�vel abrir o arquivo." << endl;
    }
    
    
}
void listarCandidatos(const Candidato* lista) {
    if (lista == NULL) {
        cout << "Nenhum candidato cadastrado." << endl;
        return;
    }
    
    const Candidato* candidatoAtual = lista;
    while (candidatoAtual != NULL) {
        cout << "Nome: " << candidatoAtual->nome << " N�mero: " << candidatoAtual->numero << endl;
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
		cout << "Lista est� vazia";
		
		
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
        cout << "Nenhum candidato cadastrado at� o momento" << endl;
    } else {
    	listarCandidatos(lista);
        int num = 0;
        cout << "Informe o n�mero do candidato que deseja excluir: ";
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
	cout << "Escolha uma op��o" << endl;
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
        cout << "N�o foi poss�vel abrir o arquivo Candidatos.txt" << endl;
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
        cout << "N�o foi poss�vel abrir o arquivo." << endl;
    }
    
    
}
bool verificaElegibilidade(int titulo, Eleitor* lista) {
    Eleitor* eleitorAtual = lista;
    bool boolean = false;
    
    if (lista == NULL) {
        cout << "N�o h� eleitor a ser exibido" << endl;
        return false;
    } else {
        while (eleitorAtual != NULL) {
            if (eleitorAtual->titulo == titulo) {
                boolean = true;
                break;
            }
            eleitorAtual = eleitorAtual->proximo;
        }
        return boolean;
    }
}
void liberarMemoriaE(Eleitor *&lista){
	Eleitor *eleitorAtual = NULL;
	if(lista == NULL){
		cout << "Lista est� vazia";
		
		
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
        cout << "Nome: " << eleitorAtual->nome << " N�mero: " << eleitorAtual->titulo << endl;
        eleitorAtual = eleitorAtual->proximo;
    }
}


int menu(){
	
	cout << "Menu de op��es" << endl;
	cout << "Escolha uma op��o"<<endl;
	cout << "[1] - Menu Candidatos" << endl;
	cout << "[2] - Menu Eleitores" << endl;
	cout << "[3] - Menu Votos" << endl;
	cout << "[4] - Gerar Relat�rio"<<endl;
	cout << "[5] - Encerrar" << endl;
	int opc;
	cin >> opc;
	return opc;
}

void insereFila(FilaEleitor*& fila, Eleitor *lista){
	int titulo;
	
	cout << "Entre na fila de vota��o!" << endl;
	cout << "Insira o numero de seu t�tulo de eleitor: ";
	cin >> titulo;
	
	if(verificaElegibilidade(titulo, lista)){
		
		cout << "T�tulo verificado, entrando na fila de vota��o ..." << endl;
		Eleitor *eleitorAtual = lista;
		while(eleitorAtual != NULL){
			if(eleitorAtual->titulo == titulo){
				fila->enfileirar(titulo, eleitorAtual->nome);
				fila->exibirFila();
			}
			eleitorAtual = eleitorAtual->proximo;
		}
		
		
	}else{
		cout << "Voc� n�o est� eleg�vel para votar, regularize seu cadastro!" << endl;
	}
	
}
string pesquisaNomeCandidato(int num, Candidato *lista){
	Candidato *atual = lista;
	while(atual != NULL){
		if(num == atual->numero){
			string nome = atual->nome;
			return nome;
		}
		atual = atual->proximo;
	}
	return "";
}
void inserirVoto(Voto*& lista, const std::string& nome, int numero){
	Voto* novoVoto = new Voto;
    novoVoto->nome = nome;
    novoVoto->titulo = numero;
    novoVoto->proximo = NULL;

    if (lista == NULL) {
        lista = novoVoto;
        
    } else {
        Voto* ultimo = lista;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = novoVoto;
        
    }
}

void votar(FilaEleitor*& fila,Voto*& votos,Candidato*& candidatos){
	int num;
	if(fila->estaVazia()){
		cout << "N�o h� eleitores na fila de elei��o!" << endl;
		
	}else{
		int titulo = fila->votar();
		Candidato *atual = candidatos;
		listarCandidatos(candidatos);
		
		cout << "Insira o n�mero do candidato que deseja votar: ";
		cin >> num;
		string nome = pesquisaNomeCandidato(num, candidatos);
		if(nome != ""){
                
		inserirVoto(votos,nome,num );
		cout << "Voto realizado com sucesso! Agradecemos � sua presen�a!" << endl;
        }else{
              cout << "Erro" << endl;
              } 
		
		fila->desenfileirar();
	}
}


int menuVoto(){
	int opc;
	cout << "Vota��o " << endl;
	cout << "Insira a op��o correspondente" << endl;
	cout << "[1] - Cadastro na fila de vota��o" << endl;
	cout << "[2] - Votar" << endl;
	cout << "[3] - Retornar" << endl;
	cin >> opc;
	return opc;
}
void salvarRelatorioCEmArquivo(string nome, int qtd){
	ofstream arquivo("Relatorios.txt", ios::app);
    if (arquivo.is_open()) {
    	arquivo << "Relat�rio de Votos por candidatos: " << endl;
        arquivo << "Nome: " << nome << ", " <<"Quantidade de votos: "<< qtd << endl;
        arquivo.close();
        cout << "Candidato salvo com sucesso no arquivo Relatorios.txt" << endl;
    } else {
        cout << "N�o foi poss�vel abrir o arquivo Relatorios.txt" << endl;
    }
}
void salvarRelatorioQtdVotos(int qtd){
	ofstream arquivo("Relatorios.txt", ios::app);
    if (arquivo.is_open()) {
    	arquivo << "Relat�rio da quantidade de votos: " << endl;
        arquivo <<"Quantidade de votos: "<< qtd << endl;
        arquivo.close();
        cout << "Voto salvo com sucesso no arquivo Relatorios.txt" << endl;
    } else {
        cout << "N�o foi poss�vel abrir o arquivo Relatorios.txt" << endl;
    }
}
void relatorioQtdVotosCandidato(Voto*& votos, Candidato*& lista) {
    Candidato* candidatoAtual = lista;
    Voto* votoAtual = votos;

    if (votos == NULL) {
        cout << "As elei��es ainda n�o foram realizadas!" << endl;
    } else {
        while (votoAtual != NULL) {
            cout << votoAtual->titulo << endl;
            votoAtual = votoAtual->proximo;
        }

        while (candidatoAtual != NULL) {
            int qtd = 0;
            votoAtual = votos;

            while (votoAtual != NULL) {
                if (candidatoAtual->nome == votoAtual->nome) {
                    qtd++;
                }
                votoAtual = votoAtual->proximo;
            }

            salvarRelatorioCEmArquivo(candidatoAtual->nome, qtd);
            cout << "A quantidade de votos do candidato " << candidatoAtual->nome << " �: " << qtd << " votos" << endl;

            candidatoAtual = candidatoAtual->proximo;
        }
        
    }
}
void relatorioQtdVotos(Voto*& votos) {
    
    Voto* votoAtual = votos;

    if (votos == NULL) {
        cout << "As elei��es ainda n�o foram realizadas!" << endl;
    } else {
        while (votoAtual != NULL) {
            cout << votoAtual->titulo << endl;
            votoAtual = votoAtual->proximo;
        }

        
		int qtd = 0;
        while (votoAtual != NULL) {
            
            qtd++;
            
            votoAtual = votoAtual->proximo;
            

            

            
            //salvarRelatorioCEmArquivo(candidatoAtual->nome, qtd);
        }
        cout << "A quantidade de votos � de: " << qtd << "votos" << endl;
        salvarRelatorioQtdVotos(qtd);
    }
    
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	FilaEleitor *fila = new FilaEleitor();
	
	int opc = menu();
	Candidato *listacandidatos = NULL;
	Eleitor *listaeleitores = NULL;
	Voto *listavotos = NULL;
	
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
					cout << "Informe uma op��o v�lida!" << endl;
				}
				subopc = menuCandidatos();
			}
		}else if(opc == 2){
			subopc = menuEleitores();
			while(subopc !=3){
				if(subopc == 1){
					
					cadastraEleitor(listaeleitores);
					liberarMemoriaE(listaeleitores);
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
					liberarMemoriaE(listaeleitores);
				}else if(subopc == 2){
					carregarCandidatos(listacandidatos);
					votar(fila, listavotos, listacandidatos);
					liberarMemoriaC(listacandidatos);
				}
				subopc = menuVoto();
			}
			
		}else if(opc == 4){
			carregarCandidatos(listacandidatos);
			relatorioQtdVotosCandidato(listavotos,listacandidatos);
			relatorioQtdVotos(listavotos);
			liberarMemoriaC(listacandidatos);
		}else{
			cout << "Op��o inv�lida"<<endl;
		}
		opc = menu();
	}
	delete fila;
}


