#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include "FilaEleitor.h"


using namespace std;
// Declara��o da struct n� que armazenar� os dados de um Candidato
struct Candidato{
	int numero;
	string nome;
	Candidato *proximo;
};
// Declara��o da struct n� que armazenar� os dados de um Voto
struct Voto{
	int titulo;
	string nome;
	Voto *proximo;
};

// Fun��o que salva o candidato em um arquivo txt ap�s executar a adi��o desse candidato � lista de candidatos
void salvarCandidatoEmArquivo(const Candidato* candidato) {
	// Verificando se o arquivo existe, se sim, utilizar o m�todo append para adicionar informa��es ao final do arquivo
    ofstream arquivo("Candidatos.txt", ios::app);
    // verificando se ele est� aberto:
    if (arquivo.is_open()) {
    	// salvando informa��es na linha do arquivo
        arquivo << candidato->nome << ", " << candidato->numero << endl;
        // fechando arquivo
        arquivo.close();
        cout << "Candidato salvo com sucesso no arquivo Candidatos.txt" << endl;
    } else {
        cout << "N�o foi poss�vel abrir o arquivo Candidatos.txt" << endl;
    }
}

// funcao que lista as op��es do menu de candidatos, retornando um inteiro correspondente a op��o acessada
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
// funcao que vai inserir um novo candidato na lista encadeada
void inserirCandidato(Candidato*& lista, const string& nome, int numero) {
	// declaracao e alocacao do novo n� candidato
    Candidato* novoCandidato = new Candidato;
    novoCandidato->nome = nome;
    novoCandidato->numero = numero;
    novoCandidato->proximo = NULL;
	// se a lista estiver vazia, a primeira posi��o ser� o novoCandidato inserido
    if (lista == NULL) {
        lista = novoCandidato;
        // funcao que salva a informa��o do novo candidato dentro do arquivo txt
        salvarCandidatoEmArquivo(novoCandidato);
    } else {
    	// caso a lista n�o estiver vazia, � declarado um ponteiro do tipo Candidato que percorrer� a lista at� achar a ultima posicao
    	Candidato* ultimo = lista;
        while (ultimo->proximo != NULL) {
        	// o ponteiro apontar� para o ultimo elemento dessa lista
            ultimo = ultimo->proximo;
        }
        // o ponteiro do n� ultimo de proximo apontar� para o novo candidato inserido, colocando ele na ultima posicao da lista
        ultimo->proximo = novoCandidato;
        // salvando as informa��es no arquivo
        salvarCandidatoEmArquivo(novoCandidato);
    }
}
// funcao que vai pedir a insercao das informa��es do novo candidato a ser preenchido
void cadastrarCandidato(Candidato* lista){
	string nome;
	int num;
	cout << "Insira o nome do Candidato: ";
	cin >> nome;
	cout << "Insira o numero do candidato: ";
	cin >> num;
	// chamada da funcao inserir candidato
	inserirCandidato(lista, nome, num);
	 
}
// funcao que vai carregar os candidatos salvos no arquivo txt e coloc�-los na lista dinamica para uso
void carregarCandidatos(Candidato*& lista) {
	// verificando se o arquivo existe
    ifstream arquivo("Candidatos.txt");
    // verificando se o arquivo est� aberto
    if (arquivo.is_open()) {
        string nome;
        int numero;
        // percorrendo as informacoes do arquivo, por nome e numero
        while (arquivo >> nome >> numero) {
        	// alocando um novo n� candidato que receber� as informacoes da linha correspondente do loop
            Candidato* novoCandidato = new Candidato;
            novoCandidato->nome = nome;
            novoCandidato->numero = numero;
            novoCandidato->proximo = NULL;
			// verificando se a lista est� vazia para inserir o primeiro candidato
            if (lista == NULL) {
                lista = novoCandidato;
            } else {
            	// caso esteja com elementos, um novo n� ser� criado e percorrer� a lista at� o ultimo elemento
                Candidato* atual = lista;
                while (atual->proximo != NULL) {
                    atual = atual->proximo;
                }
                // realizando a insercao do novo candidato e fazendo o ponteiro apontar para o ultimo n� da lista, sendo 
                // o novo candidato alocado
                atual->proximo = novoCandidato;
            }
        }
        // fechando o arquivo
        arquivo.close();
        cout << "Candidatos carregados com sucesso!" << endl;
    } else {
        cout << "N�o foi poss�vel abrir o arquivo." << endl;
    }
    
    
}
// funcao responsavel por listar os candidatos da lista 
void listarCandidatos(const Candidato* lista) {
	// verificando se a lista est� vazia, exibindo uma mensagem de que n�o h� candidatos inseridos
    if (lista == NULL) {
        cout << "Nenhum candidato cadastrado." << endl;
        return;
    }
    // criando n� que receber� a lista e percorrer� n� por n� e exibir� as informa��es de cada candidato alocado
    const Candidato* candidatoAtual = lista;
    while (candidatoAtual != NULL) {
        cout << "Nome: " << candidatoAtual->nome << " N�mero: " << candidatoAtual->numero << endl;
        candidatoAtual = candidatoAtual->proximo;
    }
}
// funcao responsavel por sobrescrever o arquivo apos a remo��o de um candidato da lista
void sobrescreveArquivo(Candidato *&lista){
	// abrindo no modo grava��o e verificando se existe
	 ofstream arquivo("Candidatos.txt");
	 // verificando se est� aberto
    if (arquivo.is_open()) {
    	// declarando ponteiro que percorrer� a lista de candidatos
        Candidato *atual = lista;
        while (atual != NULL) {
        	// inserindo as informa��es dentro do arquivo sobrescrito
            arquivo << atual->nome << ", " << atual->numero << endl;
            atual = atual->proximo;
        }
        // fechando o arquivo
        arquivo.close();
    } else {
        cout << "Erro ao sobrescrever o arquivo" << endl;
    }
}
// funcao responsavel por liberar a memoria da lista de candidatos quando n�o mais necess�ria
void liberarMemoriaC(Candidato *&lista){
	// declaracao de um ponteiro que percorrer� a lista
	Candidato *candidatoAtual = NULL;
	if(lista == NULL){
		cout << "Lista est� vazia";
		
		
	}else{
		// percorrendo  a lista
		candidatoAtual = lista;
		while(candidatoAtual != NULL){
			// criando ponteiro que receber� a posicao seguinte da lista
			Candidato *prox = candidatoAtual->proximo;
			// desalocando da memoria o candidato atual
			delete candidatoAtual;
			// candidatoAtual recebe o valor do ponteiro prox, que est� apontando para o candidato da sequencia
			candidatoAtual = prox;
		}
		// apontando a lista pra NULL
		lista = NULL;
	}
}
// funcao responsavel por removar o candidato da lista dinamica
void removeCandidato(Candidato *&lista) {
	// carregando candidatos do arquivo
    carregarCandidatos(lista);
	// verificando se a lista est� vazia
    if (lista == NULL) {
        cout << "Nenhum candidato cadastrado at� o momento" << endl;
    } else {
    	// listando os candidatos para selecionar qual ser� removido
    	listarCandidatos(lista);
        int num = 0;
        cout << "Informe o n�mero do candidato que deseja excluir: ";
        cin >> num;
		// criando o ponteiro auxiliar que percorrer� a lista at� o ultimo candidato antes do candidato que ser� removido e guardar na memoria
		//criando ponteiro para percorrer a lista de candidatos
        Candidato *auxiliar = NULL;
        Candidato *atual = lista;

        while (atual != NULL) {
        	// verificando se o numero do candidato selecionado � igual ao que est� sendo percorrido na lista no momento
            if (num == atual->numero) {
            	// verificando se o ponteiro auxiliar est� nulo
                if (auxiliar == NULL) {
                	// atribuindo o valor da lista para o valor do proximo elemento da sequencia, pois significa que o primeiro 
                	// elemento ser� removido e desalocado, movendo o ponteiro para o proximo candidato
                    lista = atual->proximo;
                } else {
                	// caso contrario o ponteiro auxiliar de proximo vai receber o proximo elemento da lista
                    auxiliar->proximo = atual->proximo;
                }
                // desalocando o candidato que foi selecionado
                delete atual;
                cout << "Candidato removido com sucesso" << endl;
                break;
            } else {
            	// caso nao seja o elemento selecionado, o ponteiro auxiliar recebera o candidato atual
            	
                auxiliar = atual;
                // o ponteiro atual passar� a apontar para o proximo elemento da lista
                atual = atual->proximo;
            }
        }
        // salvando as informacoes no novo arquivo sobrescrito apos remo��o
        sobrescreveArquivo(lista);
    }
	// liberando memoria da lista encadeada de candidatos
    liberarMemoriaC(lista);
}
// funcao responsavel por exibir as op��es do menu de eleitores
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
// funcao responsavel por salvar o eleitor no arquivo de eleitores
void salvarEleitorEmArquivo(Eleitor *eleitor){
	// criacao do arquivo em modo append, caso ele j� exista
	ofstream arquivo("Eleitores.txt", ios::app);
	// verificando se est� aberto
    if (arquivo.is_open()) {
    	// inserindo as informa��es
        arquivo << eleitor->nome << ", " << eleitor->titulo << endl;
        //fechando o arquivo
        arquivo.close();
        cout << "Candidato salvo com sucesso no arquivo Candidatos.txt" << endl;
    } else {
        cout << "N�o foi poss�vel abrir o arquivo Candidatos.txt" << endl;
    }
}
// funcao que far� a insercao de um eleitor na lista dinamica de eleitores
void inserirEleitor(Eleitor*& lista, const std::string& nome, int numero){
	// alocando um novo eleitor na memoria
	Eleitor* novoEleitor = new Eleitor;
    novoEleitor->nome = nome;
    novoEleitor->titulo = numero;
    novoEleitor->proximo = NULL;
	// verificando se a lista est� vazia, para inserir na primeira posicao
    if (lista == NULL) {
        lista = novoEleitor;
        salvarEleitorEmArquivo(novoEleitor);
        // caso contrario, a lista � percorrida at� o ultimo elemento e ele ser� adicionado ao fim, no ultimo-> proximo
    } else {
        Eleitor* ultimo = lista;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = novoEleitor;
        // salvando informa��es no arquivo de eleitores
        salvarEleitorEmArquivo(novoEleitor);
    }
}
// funcao que informara os dados do eleitor para cadastr�-los 
void cadastraEleitor(Eleitor *lista){
	string nome;
	int num;
	cout << "Insira o nome do Eleitor: ";
	cin >> nome;
	cout << "Insira o numero do titulo de eleitor: ";
	cin >> num;
	// chamada da funcao para inserir em lista dinamica
	inserirEleitor(lista, nome, num);
}
// funcao para carregar as informa��es do arquivo de eleitores e coloc�-los na lista dinamica
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
// funcao que retorna true ou false, verificando se o eleitor est� apto para votar
bool verificaElegibilidade(int titulo, Eleitor* lista) {
    Eleitor* eleitorAtual = lista;
    bool boolean = false;
    // verificando se a lista est� vazia
    if (lista == NULL) {
        cout << "N�o h� eleitor a ser exibido" << endl;
        return false;
        // verificando se o numero do titulo do eleitor bate com o numero inserido na hora do cadastro da fila de vota��o
    } else {
        while (eleitorAtual != NULL) {
            if (eleitorAtual->titulo == titulo) {
                boolean = true;
                break;
            }
            // variavel de controle para passar para o proximo ponteiro da lista
            eleitorAtual = eleitorAtual->proximo;
        }
        return boolean;
    }
}
// funcao que libera a memoria alocada da lista encadeada de eleitores
void liberarMemoriaE(Eleitor *&lista){
	Eleitor *eleitorAtual = NULL;
	// verificando se a lista est� vazia
	if(lista == NULL){
		cout << "Lista est� vazia";
		
		
	}else{
		// percorrendo a lista com um eleitorAtual
		eleitorAtual = lista;
		while(eleitorAtual != NULL){
			// declarando ponteiro proximo que receber� o elemento seguinte de eleitorAtual
			Eleitor *prox = eleitorAtual->proximo;
			// desalocando o eleitorAtual
			delete eleitorAtual;
			// apontando o eleitorAtual para o elemento seguinte
			eleitorAtual = prox;
		}
		// fazendo a lista apontar para NULL
		lista = NULL;
	}
}
// funcao responsavel por liberar a memoria da lista encadeada de votos
void liberarMemoriaV(Voto *&lista){
	// novo ponteiro voto
	Voto *votoAtual = NULL;
	// verificando se a lista est� vazia
	if(lista == NULL){
		cout << "Lista est� vazia";
		
		// percorrendo a lista
	}else{
		votoAtual = lista;
		while(votoAtual != NULL){
			// declarando ponteiro proximo que receber� o elemento seguinte de votoAtual
			Voto *prox = votoAtual->proximo;
			// desalocando votoAtual
			delete votoAtual;
			// passando para o elemento seguinte da lista
			votoAtual = prox;
		}
		// fazendo a lista apontar para NULL ( sem aloca�ao)
		lista = NULL;
	}
}
// funcao responsavel por listar os eleitores cadastrados na lista
void listarEleitores(const Eleitor* lista) {
    if (lista == NULL) {
        cout << "Nenhum candidato cadastrado." << endl;
        return;
    }
    // percorrendo a lista e exibindo as informa��es dos eleitores
    const Eleitor* eleitorAtual = lista;
    while (eleitorAtual != NULL) {
        cout << "Nome: " << eleitorAtual->nome << " N�mero: " << eleitorAtual->titulo << endl;
        eleitorAtual = eleitorAtual->proximo;
    }
}

// funcao do menu principal
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
// funcao que realizara a insercao de eleitores na fila de eleicao
void insereFila(FilaEleitor*& fila, Eleitor *lista){
	int titulo;
	
	cout << "Entre na fila de vota��o!" << endl;
	cout << "Insira o numero de seu t�tulo de eleitor: ";
	cin >> titulo;
	// verificando se o eleitor est� apto a votar
	if(verificaElegibilidade(titulo, lista)){
		
		cout << "T�tulo verificado, entrando na fila de vota��o ..." << endl;
		Eleitor *eleitorAtual = lista;
		// percorrendo a lista de eleitores
		while(eleitorAtual != NULL){
			// verificando se o numero do titulo informado � igual com o numero do titulo de eleitorAtual
			if(eleitorAtual->titulo == titulo){
				// chamada do metodo enfileirar do objeto fila, inserindo o eleitor na fila de vota��o
				fila->enfileirar(titulo, eleitorAtual->nome);
				// exibindo a fila de eleitores;
				fila->exibirFila();
			}
			// apontando para o proximo elemento da lista, caso a condi��o acima n�o seja satisfeita
			eleitorAtual = eleitorAtual->proximo;
		}
		
		
	}else{
		// se nao estiver apto, exibir mensagem regularizar cadastro
		cout << "Voc� n�o est� eleg�vel para votar, regularize seu cadastro!" << endl;
	}
	
}
// funcao que pesquisa o nome do candidato e retorna ele na lista
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
// funcao responsavel por inserir votos na listas de votos
void inserirVoto(Voto*& lista, const std::string& nome, int numero){
	// alocando novo n� voto
	Voto* novoVoto = new Voto;
    novoVoto->nome = nome;
    novoVoto->titulo = numero;
    novoVoto->proximo = NULL;
	// verificando se a lista est� vazia, para inserir na primeira posicao
    if (lista == NULL) {
        lista = novoVoto;
    // caso contrario, percorre a lista at� o ultimo elemento alocando ele na ultima posicao NULL
    } else {
        Voto* ultimo = lista;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = novoVoto;
        
    }
}
// funcao responsavel por registar o voto e salvar na lista de votos
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
		// pesquisando nome do candidato para inserir na lista de voto realizado
		string nome = pesquisaNomeCandidato(num, candidatos);
		if(nome != ""){
        // chamada da funcao para inserir os votos na lista dinamica
		inserirVoto(votos,nome,num );
		cout << "Voto realizado com sucesso! Agradecemos � sua presen�a!" << endl;
        }else{
              cout << "Erro" << endl;
              } 
		// chamada do metodo para remover o candidato da primeira posicao da lista, ap�s votar
		fila->desenfileirar();
	}
}

// funcao do menu de votos
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
// funcao que salva o relatorio de quantidade de votos por candidatos
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
// funcao que salva a quantidade de votos total
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
// funcao que salva a quantidade de faltas na eleicao
void salvarRelatorioFaltas(int qtd){
	ofstream arquivo("Relatorios.txt", ios::app);
    if (arquivo.is_open()) {
    	arquivo << "Relat�rio da quantidade de faltas: " << endl;
    	arquivo << endl;
        arquivo <<"Quantidade de faltas: "<< qtd << endl;
        arquivo.close();
        cout << "Relatorio salvo com sucesso no arquivo Relatorios.txt" << endl;
    } else {
        cout << "N�o foi poss�vel abrir o arquivo Relatorios.txt" << endl;
    }
}// relatorio de quantidade de votos por candidato
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
// relatorio de quantidade total de votos
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
            

            

            
            
        }
        cout << "A quantidade de votos � de: " << qtd << "votos" << endl;
        salvarRelatorioQtdVotos(qtd);
    }
    
}
// relatorio de quantidade de faltas da eleicao
void relatorioQtdFaltas(Voto*& votos, Eleitor*& lista) {
    Eleitor *eleitorAtual = lista;
    Voto* votoAtual = votos;
    int totalEleitores = 0;
    int totalVotos = 0;

    while (eleitorAtual != NULL) {
        totalEleitores++;
        eleitorAtual = eleitorAtual->proximo;
    }

    while (votoAtual != NULL) {
        totalVotos++;
        votoAtual = votoAtual->proximo;
    }

    int faltas = totalEleitores - totalVotos;
    
    cout << "Quantidade de faltas: " << faltas << endl;
    salvarRelatorioFaltas(faltas);
}
  // funcao que exclui o arquivo de relatorios para criar um novo quando solicitado 
void excluirArquivo(const std::string& nomeArquivo) {
    if (std::remove(nomeArquivo.c_str()) == 0) {
        std::cout << "Arquivo exclu�do com sucesso." << std::endl;
    } else {
        std::cout << "Erro ao excluir o arquivo." << std::endl;
    }
}
// funcao principal em que o codigo rodar� 
// possui a estrutura base do programa
int main() {
	setlocale(LC_ALL, "Portuguese");
	FilaEleitor *fila = new FilaEleitor();
	string relatorios = "Relatorios.txt";
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
			excluirArquivo(relatorios);
			carregarCandidatos(listacandidatos);
			carregarEleitores(listaeleitores);
			relatorioQtdVotosCandidato(listavotos,listacandidatos);
			relatorioQtdVotos(listavotos);
			relatorioQtdFaltas(listavotos,listaeleitores);
			liberarMemoriaC(listacandidatos);
			liberarMemoriaE(listaeleitores);
			liberarMemoriaV(listavotos);
		}else{
			cout << "Op��o inv�lida"<<endl;
		}
		opc = menu();
	}
	// desalocando fila;
	delete fila;
}


