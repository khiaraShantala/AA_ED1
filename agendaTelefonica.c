#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define clear() printf("\033[H\033[J")


struct contato {
   char nome[50];
   char tel[11];
};

typedef struct contato Contato;

struct agenda {
	Contato* info;
	struct agenda* prox;
};
typedef struct agenda Agenda;


Agenda* criaAgenda();
int agendaVazia(Agenda* agenda);
Contato* criaContato(char* nome, char* tel);


Agenda* insereAgenda(Agenda*, Contato* );
int maior(char*, char*);
int buscaContato (Agenda*);
Agenda* removeContato (Agenda*);
void imprimeAgenda (Agenda*);
void liberaAgenda (Agenda* );


Agenda* verificaAgenda(Agenda*);
void dump(Agenda*);





int main(int argc, char const *argv[]){

    int op = 9;
    int arq;
    Agenda* agenda;
    agenda = criaAgenda();
    agenda = verificaAgenda(agenda);

    while (op != 0) {

        printf ("\n\n################## Agenda Telefonica ################## \n\n");
        printf ("[1]-Inserir Contato   \n");
        printf ("[2]-Buscar Contato    \n");
        printf ("[3]-Remover Contato   \n");
        printf ("[4]-Imprime Contatos  \n");
        printf ("[0]-Sair              \n");

        scanf(" %d", &op);

        clear();

        switch (op) {

            case 1: {

                Contato* c;
                char nome[50];
                char tel[10];

                clear();

                printf ("Digite o Nome: ");
				scanf("%s", nome);
	
                
                printf ("Digite o Telefone: ");
                scanf("%s", tel);


                c = criaContato(nome, tel);
                clear();
                agenda = insereAgenda(agenda, c);
                printf("Contato Inserido\n");

                puts("\n");
                break;
            }
            case 2: {
                clear();
                buscaContato(agenda);
                break;
            }
            case 3: {
                clear();
                agenda = removeContato(agenda);
                break;
            }
            case 4: {
                clear();
                imprimeAgenda(agenda);
                break;
            }
            case 0: {
                printf("Agenda Fechada\n");
                break;
            }
            default: {
                printf("Opção invalida\n");
                continue;
            }
        }
    }

    dump(agenda);
    
    liberaAgenda(agenda);
   
    return 0;
}


Contato* criaContato(char* nome, char* tel){

    Contato* c = (Contato*)malloc(sizeof(Contato));
    strcpy(c->nome, nome);
    strcpy(c->tel, tel);

    return c;
}


Agenda* criaAgenda(void) {

	Agenda* agenda = (Agenda*)malloc(sizeof(Agenda));
	agenda = NULL;
	return agenda;
}


int agendaVazia(Agenda* agenda){
    if(agenda == NULL)
        return 1;
    else
        return 0;
}


Agenda* insereAgenda(Agenda* agenda, Contato* contato){

    Agenda* novo;
    Agenda* ant = NULL;
    Agenda* p = agenda;
	
 	
    while ((p != NULL) && (maior(p->info->nome, contato->nome) == 0)) {
        ant = p;
        p = p->prox;
    }

    novo = (Agenda*) malloc(sizeof(Agenda));
    novo->info = contato;
    novo->prox = NULL;

    if (ant == NULL) {
        novo->prox = agenda;
        agenda = novo;
    }

    else {
        novo->prox = ant->prox;
        ant->prox = novo;
    }

    return agenda;
}

int maior(char* nome1, char* nome2){
    
    for(int i = 0; i < 50; i++){
       
        int primeiro = nome1[i];
        int segundo = nome2[i];
        
        if(primeiro < segundo)
            return 0;
        else if(primeiro > segundo)
            return 1;
        else 
            continue;
    }
}

void imprimeAgenda (Agenda* agenda){

    Agenda* p;

    if(agendaVazia(agenda)){
        printf("Agenda Vazia\n");
        return ;
    }
    
    for (p = agenda; p != NULL; p = p->prox){
        printf("nome = %s\n", p->info->nome);
        printf("tel = %s\n", p->info->tel);
    }
}

int buscaContato (Agenda* agenda) {

    
    if(agendaVazia(agenda)){
        printf("Agenda Vazia\n");
        return 1;
    }

    char* nome;
    Contato *c = NULL;

    printf ("Para localizar digite nome do contato:");
    scanf ("%s", nome);


    for (Agenda* p = agenda; p != NULL; p = p->prox) {
        if (strcmp(p->info->nome, nome) == 0){
            c = p->info;
        }
    }

    if(c != NULL)
        printf("Nome : %s\nTelefone: %s\n", c->nome, c->tel);

    else
        printf("Contato não encontrado\n");
}

Agenda* removeContato (Agenda* agenda) {

   
    if(agendaVazia(agenda)){
        printf("Agenda Vazia\n");
        return NULL;
    }


    Agenda* p = agenda;
    Agenda* aux = NULL;
    char* nome;
    int achou = 0;


    printf ("Para localizar digite nome do contato:");
    scanf ("%s", nome);

    if (strcmp(p->info->nome, nome) == 0){
        achou = 2;
    }
    
    for (p = agenda; p != NULL && achou != 2; p = p->prox) {
        if (strcmp(p->prox->info->nome, nome) == 0){
            achou = 1;
            break;
        }
    }

    if(achou == 1) {
        aux = p->prox;
        p->prox = p->prox->prox;

        free(aux);
        puts("Contato Removido");
    }

    else if(achou == 2) {
        aux = p;
        p = p->prox;
        
        free(aux);
        puts("Contato Removido");
    }

    else
        printf("Contato não encontrado\n");


    return p;
}


void liberaAgenda (Agenda* agenda) {

    
    if(agendaVazia(agenda)){
        printf("Agenda Vazia\n");
        return ;
    }


    Agenda* p = agenda;
    Agenda* aux;

    while (p != NULL) {
       
        aux = p->prox;
        free(p);
        p = aux;
    }
    free(aux);
    aux = NULL;
}



Agenda* verificaAgenda(Agenda* agenda) {

    Contato* c;
    FILE* arquivo;
    arquivo = fopen("agenda.txt","r");
    char nome[50];
    char tel[11];

    if (arquivo == NULL){

        printf("ERRO!!");
        return NULL;
    }
	
    while(fgets(nome, sizeof(nome), arquivo) != NULL){
        fgets(tel, sizeof(tel), arquivo);
        int tamanhoNome = strlen(nome) - 1;
        if(nome[tamanhoNome] == '\n' ){
            nome[tamanhoNome] = '\0';
        }

        int tamanhoTel = strlen(tel) - 1;
        if(tel[tamanhoTel] == '\n'){
            tel[tamanhoTel] = '\0';
        }

        c = criaContato(nome, tel);

        agenda = insereAgenda(agenda, c);

    }

    fclose(arquivo);

    return agenda;	
}


void dump(Agenda* agenda) {

	FILE *arquivo = fopen("agenda.txt", "w");  
	Agenda* p = agenda;

	if(arquivo == NULL)
		printf("Ainda não Existe Contatos\n");

    while(p != NULL){

        fprintf(arquivo, "%s\n", p->info->nome);
        fprintf(arquivo, "%s\n", p->info->tel);
        p = p->prox;
    }
	
	fclose(arquivo);
	printf ("Contato Salvo(s)\n");
}
