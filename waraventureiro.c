#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura base de território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar territórios dinamicamente
void cadastrarTerritorios(Territorio *mapa, int qtd) {
    printf("\n=== Cadastro de Territorios ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf(" %[^\n]", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir todos os territórios
void exibirTerritorios(Territorio *mapa, int qtd) {
    printf("\n=== Dados do Territorio ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\n[%d] Nome: %s", i + 1, mapa[i].nome);
        printf("\n       Cor do exercito: %s", mapa[i].cor);
        printf("\n       Tropas: %d\n", mapa[i].tropas);
    }
    
}

// Função que simula o ataque entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor) {
    printf("\n\n=== Simulando Ataque ===\n");
    printf("%s (%s) está atacando %s (%s)\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoAtacante = (rand () % 6) +1;  // 1 a 6
    int dadoDefensor = (rand () % 6) +1;

    printf("\nDado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\n O atacante venceu a batalha!\n");

        // Mudança de domínio do território
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas /= 2;

        printf("%s conquistou o território %s!\n", atacante->nome, defensor->nome);

    } else {
        printf("\n O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1;
        if (atacante->tropas < 0)
            atacante->tropas = 0;
        
    }
    
}

// Função para liberar memória alocada dinamicamente
void liberarMemoria(Territorio *mapa) {
    free(mapa);
    printf("\nMemoria liberada com sucesso!\n");
}

// Função principal
int main() {
    srand(time(NULL)); // Garante aleatoriedade dos dados

    int qtd;
    printf("Digite o numero do territorio: ");
    scanf("%d", &qtd);

    // Alocação dinâmica
    Territorio *mapa = (Territorio *)calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }
    
    cadastrarTerritorios(mapa, qtd);
    exibirTerritorios(mapa, qtd);

    char continuar;
    do {
        int at, def;
        printf("\nEscolha o territorio atacante (1-%d): ", qtd);
        scanf("%d", &at);
        printf("Escolha o territorio defensor (1-%d): ", qtd);
        scanf("%d", &def);

        if (at == def) {
            printf("Um territorio nao pode atacar a si mesmo!\n");
        } else if (strcmp(mapa[at - 1].cor, mapa[def - 1].cor) == 0) {
            printf("Territorios da mesma cor nao podem batalhar!\n");
        } else {
            atacar(&mapa[at - 1], &mapa[def - 1]);
        }

        exibirTerritorios(mapa, qtd);

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');

    liberarMemoria(mapa);
    printf("\nFim de jogo. Ate a proxima batalha!\n");

    return 0;
    
}