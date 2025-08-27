#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Desafio Detective Quest

// declaração da struct com a propriedade e próximos elementos
typedef struct sala
{
    char nome[40];
    struct sala *esquerda;
    struct sala *direita;
} Sala;

// declaraçao das funções
Sala *criarSala(char nome[]);
Sala *explorarSalas(Sala *raiz, char caminho);
void liberar(Sala *raiz);

// cria uma nova sala
Sala *criarSala(char nome[])
{
    Sala *novo = (Sala *)malloc(sizeof(Sala));
    strcpy(novo->nome, nome);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// explora as salas conforme caminho escolhido
Sala *explorarSalas(Sala *raiz, char caminho)
{
    if (raiz == NULL)
    {
        printf("\nSala inválida.\n");
        return NULL;
    }

    Sala *atual = raiz;

    if (caminho == 'E' || caminho == 'e')
    {
        if(atual->esquerda == NULL){
            printf("\nNão há sala à esquerda. Tente outro caminho.\n");
            return atual;
        }
        atual = atual->esquerda;
    }
    else if (caminho == 'D' || caminho == 'd')
    {
        if(atual->direita == NULL){
            printf("\nNão há sala à direita. Tente outro caminho.\n");
            return atual;
        }
        atual = atual->direita;
    }

    printf("\nVocê está na sala: %s\n", atual->nome);
    return atual;
}

// libera memoria alocada para a árvore
void liberar(Sala *raiz)
{
    if (raiz != NULL)
    {
        liberar(raiz->esquerda);
        liberar(raiz->direita);
        free(raiz);
    }
}

// função principal
int main()
{
    // inicializa variáveis
    char caminho = '\0';
    Sala *raiz = criarSala("Hall de Entrada");
    Sala *atual = raiz;
    raiz->esquerda = criarSala("Sala de Estar");
    raiz->direita = criarSala("Biblioteca");
    raiz->esquerda->esquerda = criarSala("Quarto");
    raiz->direita->direita = criarSala("Escritório");
    raiz->esquerda->esquerda->direita = criarSala("Sótão");
    raiz->direita->direita->esquerda = criarSala("Cozinha");
    raiz->esquerda->esquerda->esquerda = criarSala("Banheiro");

    printf("\n***********************************************************");
    printf("\n                      Detective Quest                      ");
    printf("\n***********************************************************\n");
    printf("\nVocê está no Hall de Entrada da Mansão! Selecione uma opção para explorar: ");

    // laço para menu principal
    do
    {
        printf("\nDigite 'E' para entrar à esquerda\nDigite 'D' para entrar à direita\nDigite 'S' para sair da sala");
        printf("\n-> Opção: ");
        scanf(" %c", &caminho);

        switch(caminho){
            case 'E': case 'e':
            case 'D': case 'd':
                // entra na sala conforme escolha
                atual = explorarSalas(atual, caminho);

                // se chegar a uma sala sem saída, encerra o jogo
                if (atual->esquerda == NULL && atual->direita == NULL)
                {
                    printf("\nEssa sala não tem saída. Fim do jogo!\n");
                    caminho = 'S';
                    break;
                }

                break;
            case 'S': case 's':
                printf("\nSaindo da mansão...\n");
                break;
            default:
                printf("\nOpção inválida. Use apenas 'E' para esquerda, 'D' para direita e 'S' para sair.\n");
                continue;
        }
    } while (caminho != 's' && caminho != 'S');

    // libera memoria alocada
    liberar(raiz);

    printf("\nEncerrando o jogo...\n\n");

    return 0;
}
