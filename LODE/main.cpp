#include <iostream>

using namespace std;

class pet{
public:
string nome;
char tipo;
int idade; 
string raca;
pet *prox;
pet *ant;

pet** inserir(pet **R, string n, char t, int i, string r){
    pet *novo = new pet();
    novo->nome = n;
    novo->tipo = t;
    novo->idade = i;
    novo->raca = r;

    if(R[0] == NULL){
        R[0] = novo;
        R[1] = novo;
        R[1]->prox = NULL;
        R[0]->ant = NULL;        
    }else{
        pet *atual = R[0];

        if(novo->tipo == 'g'){
        while((atual != NULL) && (atual->tipo != 'c') && (atual->nome < novo->nome)){
            atual = atual->prox;
        }
        }else if(novo->tipo == 'c'){
        while((atual != NULL) && (atual->tipo != 'g') && (atual->nome < novo->nome)){
        atual = atual->prox;
        }
    }
        if(atual == NULL){
            novo->ant = R[1];
            R[1]->prox = novo;
            R[1] = novo;
            R[1]->prox = NULL;
        }else if(atual->ant == NULL){
            R[0]->ant = novo;
            R[0] = novo;
            R[0]->ant = NULL;
        }else{
            novo->prox = atual;
            novo->ant = atual->ant;
            atual->ant->prox = novo;
            atual->ant = novo;
        }

    }
    return R;
}

    };

   int main() {
    pet *R[2] = {NULL, NULL}; 

    pet p; 
    p.inserir(R, "Rex", 'g', 5, "Vira-lata");

    return 0;
}
