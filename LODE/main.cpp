#include <iostream>
#include <stdlib.h>

using namespace std;

class pet{
public:
    string nome;
    char tipo;
    int idade; 
    string raca;
    pet *prox = NULL;
    pet *ant = NULL;

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
            pet* atual = R[0]; 

            if (novo->tipo == 'c') {
                while (atual != NULL && atual->tipo == 'c' && atual->nome < novo->nome) {
                    atual = atual->prox;
                }
            }
            else if (novo->tipo == 'g') {
                while (atual != NULL && atual->tipo == 'c') { 
                    atual = atual->prox;
                }
                while (atual != NULL && atual->nome < novo->nome) {
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
                novo->prox = R[0];
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

    
    void listar(pet **R, char t){
        if(t == 'g'){
            pet *atual = R[1];
            while(atual != NULL && atual->tipo == 'g'){
                cout << atual->nome << endl;
                atual = atual->ant;
            }
        }
        else if(t == 'c'){
            pet *atual = R[0];
            while(atual != NULL && atual->tipo == 'c'){
                cout << atual->nome << endl;
                atual = atual->prox;
            }
        }
        else{ 
            pet *atual = R[0];
            while(atual != NULL){
                cout << atual->nome << endl;
                atual = atual->prox;
            }
        }
    }

    pet** excluir(pet **R, string n, char t){
        pet* atual = procurar(R, n, t);
        if(atual != NULL){
            if(atual == R[0]){ 
                R[0] = R[0]->prox;
                if(R[0] != NULL) R[0]->ant = NULL;
            }else if(atual == R[1]){ 
                R[1] = R[1]->ant;
                if(R[1] != NULL) R[1]->prox = NULL;
            }else{ 
                atual->ant->prox = atual->prox;
                atual->prox->ant = atual->ant;  
            }
            delete(atual);
        }
        return R;
    }

    void dados(){
        cout << this->nome << endl;
        cout << this->tipo << endl;
        cout << this->idade << endl;
        cout << this->raca << endl;
    }

    pet* procurar(pet **R, string n, char t){
        pet* atual = R[0];
        while(atual != NULL){
            if(atual->nome == n && atual->tipo == t){
                cout << "Pet encontrado: " << endl;
                atual->dados();
                return atual;
            }
            atual = atual->prox;    
        }
        cout << "Nao cadastrado" << endl;
        return NULL;
    }
};

void menuopcoes(){
    cout <<  "1. Cadastrar Pet" << endl;
    cout <<  "2. Excluir Pet" << endl;
    cout <<  "3. Listagem Geral" << endl;
    cout <<  "4. Listagem de cães" << endl;
    cout <<  "5. Listagem de gatos" << endl;
    cout << "6. Pesquisar Pet" << endl;
    cout << "7. Sair" << endl;
    cout << "Escolha uma opção: ";
}

int main() {
    pet *R[2] = {NULL, NULL}; 
    pet p; 
    int i, op, top;
    string n, r;
    char t;

    do{
        menuopcoes();
        cin >> op;
        cin.ignore();

        switch(op){  
            
            case 1:
            system("clear || cls");
                cout << "Insira o nome: ";
                getline(cin, n);
                cout << "Insira a raca: ";
                getline(cin, r);
                cout << "Insira a idade: ";
                cin >> i;
                do{
                    cout << "Qual o tipo?\n1. Cao\n2. Gato" << endl;
                    cin >> top;
                }while(top != 1 && top!= 2);
                
                if(top == 1){t = 'c';} else {t = 'g';}
                p.inserir(R, n, t, i, r);
                system("clear || cls");
                break;

            case 2:
                cout << "Insira o nome: ";
                getline(cin, n);
                do{
                    cout << "Qual o tipo?\n1. Cao\n2. Gato" << endl;
                    cin >> top;
                }while(top != 1 && top != 2);
                if (top == 1) t = 'c'; else t = 'g';
                p.excluir(R, n, t);
                break;

            case 3:
            system("clear || cls");
                p.listar(R, 't');
                break;

            case 4:
            system("clear || cls");
                p.listar(R, 'c');
                break;

            case 5:
            system("clear || cls");
                p.listar(R, 'g');
                break;

            case 6:
            system("clear || cls");
                cout << "Insira o nome: ";
                getline(cin, n);
                do{
                    cout << "Qual o tipo?\n1. Cao\n2. Gato" << endl;
                    cin >> top;
                }while(top != 1 && top != 2);
                if(top == 1){t = 'c';}else{t = 'g';}
                p.procurar(R, n, t);
                break;

            case 7:
                cout << "Saindo..." << endl;
                break;
        }
        
    }while(op != 7);

    return 0;
}
