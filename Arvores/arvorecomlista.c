

// codigo para uma lista a ser usada em busca na arvore
struct nol {
struct noa *enoa; // endereço do nó da arvore 
struct nol *prox;
};

typedef struct nol nol;

void l_inserir_comeco(struct nol **l, noa *enoa)
{
if(enoa == NULL)
return;

if(*l == NULL){
struct nol *aux = malloc(sizeof(struct nol));
aux->enoa = enoa;
aux->prox = NULL;
*l = aux;
} else {
struct nol *aux = malloc(sizeof(struct nol));
aux->enoa = enoa;
aux->prox = *l;
*l = aux;
}
}

struct nol *l_buscar(const struct nol *lista, noa *enoa)
{
struct nol *aux = lista;
while(aux != NULL && aux->enoa != enoa){
aux = aux->prox;
}
return aux;
}

void l_alterar(struct nol *lista, noa *enoa, noa *novo_enoa)
{
struct nol *no = l_buscar(lista, enoa);
if(no){
no->enoa = novo_enoa;
}
}

struct nol *l_pega_no_anterior(struct nol *lista, struct nol *no)
{
struct nol *aux = lista;
while(aux != NULL && aux->prox != no){
aux = aux->prox;
}
return aux;
}

void l_inserir_final(struct nol **l, noa *enoa)
{
if(enoa == NULL)
return;

struct nol *aux = malloc(sizeof(struct nol));
aux->enoa = enoa;
aux->prox = NULL;

if(*l == NULL){
*l = aux;
return;
}
struct nol *ant = l_pega_no_anterior(*l, NULL);
ant->prox = aux;
}


int l_remover(struct nol **lista, noa *enoa)
{
struct nol *aux = l_buscar(*lista, enoa);
if(*lista == NULL || aux == NULL)
return -1; // não há o que remover if(aux == *lista){ // está nol começo *lista = (*lista)->prox;
free(aux);
} else if (aux->prox == NULL){ // está nol fim struct nol *ant = l_pega_no_anterior(*lista, aux);
ant->prox = NULL;
free(aux);
} else { // está nol meio struct nol *ant = l_pega_no_anterior(*lista, aux);
ant->prox = aux->prox;
free(aux);
}
return 0;
}

nol *l_remover_comeco(struct nol **lista)
{
if(*lista == NULL)
return NULL; // não há o que remover nol *aux = *lista;
*lista = (*lista)->prox;
return aux;
}


void l_listar(const struct nol *lista)
{
struct nol *aux = lista;
printf("[ ");
while(aux != NULL){
printf("%p", aux->enoa);
if(aux->prox != NULL)
printf(", ");
aux = aux->prox;
}
printf("]\n");
}

int l_vazia(nol *lista){
if(lista == NULL)
return 1;
else return 0;
}


void busca_largura(noa *raiz)
{
if(raiz == NULL)
return;

nol *borda = NULL; // borda é uma lista com os nós a serem visitados(mostrados) l_inserir_final(&borda, raiz); // insere a raiz while(!l_vazia(borda))
{
nol *l_cabeca = l_remover_comeco(&borda);
// visito tal elemento (imprimir por exemplo) noa *no_arvore = l_cabeca->enoa;
printf("%d ", no_arvore->valor);
// pego os filhos e coloco na borda no fim da lista l_inserir_final(&borda, no_arvore->esq); // nao insiro se ponteiro enoa for NULL, ajustei codigo l_inserir_final(&borda, no_arvore->dir); // nao insiro se ponteiro enoa for NULL, ajustei codigo free(l_cabeca);
}
}

void busca_profundidade(noa *raiz)
{
if(raiz == NULL)
return;

nol *borda = NULL; // borda é uma lista com os nós a serem visitados(mostrados) l_inserir_final(&borda, raiz); // insere a raiz while(!l_vazia(borda))
{
nol *l_cabeca = l_remover_comeco(&borda);
// visito tal elemento (imprimir por exemplo) noa *no_arvore = l_cabeca->enoa;
printf("%d ", no_arvore->valor);
// pego os filhos e coloco na borda no fim da lista l_inserir_comeco(&borda, no_arvore->dir); // nao insiro se ponteiro enoa for NULL, ajustei codigo l_inserir_comeco(&borda, no_arvore->esq); // nao insiro se ponteiro enoa for NULL, ajustei codigo free(l_cabeca);
}
}