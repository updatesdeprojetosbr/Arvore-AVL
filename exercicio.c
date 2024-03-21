#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int chave;
    struct Node *esquerda;
    struct Node *direita;
    int altura;
} Nó;

Nó *novoNó(int chave) {
    Nó *nó = (Nó *)malloc(sizeof(Nó));
    nó->chave = chave;
    nó->esquerda = NULL;
    nó->direita = NULL;
    nó->altura = 1;
    return nó;
}

int altura(Nó *nó) {
    if (nó == NULL)
        return 0;
    return nó->altura;
}

int fatorBalanceamento(Nó *nó) {
    if (nó == NULL)
        return 0;
    return altura(nó->esquerda) - altura(nó->direita);
}

Nó *rotacaoDireita(Nó *y) {
    Nó *x = y->esquerda;
    Nó *T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = 1 + (altura(y->esquerda) > altura(y->direita) ? altura(y->esquerda) : altura(y->direita));
    x->altura = 1 + (altura(x->esquerda) > altura(x->direita) ? altura(x->esquerda) : altura(x->direita));

    return x;
}
Nó *rotacaoEsquerda(Nó *x) {
    Nó *y = x->direita;
    Nó *T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = 1 + (altura(x->esquerda) > altura(x->direita) ? altura(x->esquerda) : altura(x->direita));
    y->altura = 1 + (altura(y->esquerda) > altura(y->direita) ? altura(y->esquerda) : altura(y->direita));
    return y;
}

Nó *inserir(Nó *nó, int chave) {
    if (nó == NULL)
        return novoNó(chave);

    if (chave < nó->chave)
        nó->esquerda = inserir(nó->esquerda, chave);
    else if (chave > nó->chave)
        nó->direita = inserir(nó->direita, chave);
    else
        return nó;

    nó->altura = 1 + (altura(nó->esquerda) > altura(nó->direita) ? altura(nó->esquerda) : altura(nó->direita));

    int balanceamento = fatorBalanceamento(nó);

    if (balanceamento > 1 && chave < nó->esquerda->chave)
        return rotacaoDireita(nó);

    if (balanceamento < -1 && chave > nó->direita->chave)
        return rotacaoEsquerda(nó);

    if (balanceamento > 1 && chave > nó->esquerda->chave) {
        nó->esquerda = rotacaoEsquerda(nó->esquerda);
        return rotacaoDireita(nó);
    }

    if (balanceamento < -1 && chave < nó->direita->chave) {
        nó->direita = rotacaoDireita(nó->direita);
        return rotacaoEsquerda(nó);
    }

    return nó;
}

void percorrerEmOrdem(Nó *raiz) {
    if (raiz != NULL) {
        percorrerEmOrdem(raiz->esquerda);
        printf("%d ", raiz->chave);
        percorrerEmOrdem(raiz->direita);
    }
}

int main() {
    Nó *raiz = NULL;

    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 25);

    printf("Árvore AVL em ordem: ");
    percorrerEmOrdem(raiz);
    printf("\n");

    return 0;
}