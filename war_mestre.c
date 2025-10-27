#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 30
#define MAX_COR 10

// Estrutura que representa um território
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// Estrutura para representar jogador
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    char *missao; // ponteiro para missão alocada dinamicamente
} Jogador;

/* ---------- Funções de cadastro/exibição ---------- */

// Cadastra territórios dinamicamente no vetor mapa (já alocado)
void cadastrarTerritorios(Territorio *mapa, int qtd) {
    printf("\n=== Cadastro de Territórios ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Cor do exército (ex: Vermelho, Azul): ");
        scanf(" %[^\n]", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        if (mapa[i].tropas < 0) mapa[i].tropas = 0;
    }
}

// Exibe todos os territórios do mapa
void exibirMapa(Territorio *mapa, int qtd) {
    printf("\n=== Mapa Atual ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

/* ---------- Funções de missão ---------- */

// Atribui uma missão aleatória copiando a string para 'destino' (checar tamanho antes de chamar)
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    strcpy(destino, missoes[idx]); // destino deve apontar para espaço alocado
}

// Exibe missão (passagem por valor - aqui é apenas mostrar)
void exibirMissao(const char *missao) {
    printf("Missão designada: %s\n", missao);
}

/*
 Verifica se a missão foi cumprida.
 Retorna: 1 se cumprida, 0 caso contrário.

 Observação: para simplificar, a verificação usa comparações exatas
 com as strings de missões conhecidas.
*/
int verificarMissao(const char *missao, Territorio *mapa, int tamanho, const char *corJogador) {
    // Missões implementadas (devem coincidir exatamente com o vetor de missões)
    if (strcmp(missao, "Conquistar 3 territorios") == 0) {
        int contador = 0;
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, corJogador) == 0) contador++;
        return (contador >= 3) ? 1 : 0;
    }

    if (strcmp(missao, "Ter 10 tropas no total") == 0) {
        int total = 0;
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, corJogador) == 0) total += mapa[i].tropas;
        return (total >= 10) ? 1 : 0;
    }

    if (strcmp(missao, "Eliminar todas as tropas da cor Vermelho") == 0) {
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, "Vermelho") == 0 && mapa[i].tropas > 0) return 0;
        return 1;
    }

    if (strcmp(missao, "Possuir um territorio com >=8 tropas") == 0) {
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas >= 8) return 1;
        return 0;
    }

    if (strcmp(missao, "Conquistar 5 territorios") == 0) {
        int contador = 0;
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, corJogador) == 0) contador++;
        return (contador >= 5) ? 1 : 0;
    }

    // Se missão desconhecida - não cumprida
    return 0;
}

/* ---------- Função de ataque ---------- */

// Simula um ataque entre dois territórios (acessa via ponteiros)
void atacar(Territorio *atacante, Territorio *defensor) {
    printf("\nSimulando ataque: %s (%s) -> %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoAt = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAt, dadoDef);

    if (dadoAt > dadoDef) {
        printf("Resultado: atacante venceu!\n");
        // Transferência: defensor muda de cor e recebe metade das tropas do atacante
        int tropasTransferidas = atacante->tropas / 2;
        if (tropasTransferidas < 1) tropasTransferidas = 1; // pelo menos 1 tropa conquista
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = tropasTransferidas;
        atacante->tropas = atacante->tropas - tropasTransferidas;
        if (atacante->tropas < 0) atacante->tropas = 0;
        printf("%s conquistou %s e deixou %d tropas. %s agora tem %d tropas.\n",
               atacante->nome, defensor->nome, atacante->tropas, defensor->nome, defensor->tropas);
    } else {
        printf("Resultado: defensor resistiu. Atacante perde 1 tropa.\n");
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

/* ---------- Gerenciamento de memória ---------- */

// Libera memória alocada dinamicamente para mapa e missões dos jogadores
void liberarMemoria(Territorio *mapa, Jogador *jogadores, int numJogadores) {
    if (mapa != NULL) free(mapa);
    for (int i = 0; i < numJogadores; i++) {
        if (jogadores[i].missao != NULL) {
            free(jogadores[i].missao);
            jogadores[i].missao = NULL;
        }
    }
}

/* ---------- Função principal (fluxo do jogo) ---------- */

int main() {
    srand((unsigned int)time(NULL));

    int qtdTerritorios;
    printf("Bem-vindo ao Desafio War Estruturado - Nível Mestre!\n");
    printf("Digite o número de territórios no mapa: ");
    scanf("%d", &qtdTerritorios);
    if (qtdTerritorios <= 0) {
        printf("Quantidade inválida. Encerrando.\n");
        return 1;
    }

    // Aloca mapa dinamicamente
    Territorio *mapa = (Territorio *)calloc(qtdTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Falha na alocação de memória.\n");
        return 1;
    }

    // Cadastra territórios
    cadastrarTerritorios(mapa, qtdTerritorios);
    exibirMapa(mapa, qtdTerritorios);

    // Configura jogadores (2 jogadores neste exemplo)
    int numJogadores = 2;
    Jogador jogadores[2];
    for (int i = 0; i < numJogadores; i++) {
        printf("\nDigite o nome do jogador %d: ", i + 1);
        scanf(" %[^\n]", jogadores[i].nome);
        printf("Digite a cor do jogador %d (cor do exército): ", i + 1);
        scanf(" %[^\n]", jogadores[i].cor);
        jogadores[i].missao = NULL; // será alocada abaixo
    }

    // Vetor de missões (mínimo 5)
    char *missoesDisponiveis[] = {
        "Conquistar 3 territorios",
        "Ter 10 tropas no total",
        "Eliminar todas as tropas da cor Vermelho",
        "Possuir um territorio com >=8 tropas",
        "Conquistar 5 territorios"
    };
    int totalMissoes = sizeof(missoesDisponiveis) / sizeof(missoesDisponiveis[0]);

    // Atribui missões: aloca espaço para cada missão e copia a string sorteada
    for (int i = 0; i < numJogadores; i++) {
        // aloca tamanho suficiente para a missão (strlen + 1)
        jogadores[i].missao = (char *)malloc((strlen(missoesDisponiveis[0]) + 50) * sizeof(char));
        if (jogadores[i].missao == NULL) {
            printf("Erro ao alocar memória para missão.\n");
            liberarMemoria(mapa, jogadores, numJogadores);
            return 1;
        }
        atribuirMissao(jogadores[i].missao, missoesDisponiveis, totalMissoes);
        printf("\nJogador: %s | Cor: %s\n", jogadores[i].nome, jogadores[i].cor);
        printf("Sua missão (será mostrada apenas uma vez):\n");
        exibirMissao(jogadores[i].missao);
    }

    // Loop de jogo: turnos com ataques até alguém cumprir a missão ou o usuário parar
    char continuar = 's';
    while ((continuar == 's' || continuar == 'S')) {
        exibirMapa(mapa, qtdTerritorios);

        // Mostrar jogadores e suas cores para facilitar escolha
        printf("\nJogadores:\n");
        for (int i = 0; i < numJogadores; i++)
            printf("[%d] %s (Cor: %s)\n", i + 1, jogadores[i].nome, jogadores[i].cor);

        // Escolher atacante por índice de território
        int idxAt, idxDef;
        printf("\nEscolha o índice do território atacante (1-%d): ", qtdTerritorios);
        scanf("%d", &idxAt);
        printf("Escolha o índice do território defensor (1-%d): ", qtdTerritorios);
        scanf("%d", &idxDef);

        // Valida índices
        if (idxAt < 1 || idxAt > qtdTerritorios || idxDef < 1 || idxDef > qtdTerritorios) {
            printf("Índice inválido. Tente novamente.\n");
        } else if (idxAt == idxDef) {
            printf("Um território não pode atacar a si mesmo.\n");
        } else if (strcmp(mapa[idxAt - 1].cor, mapa[idxDef - 1].cor) == 0) {
            printf("Não é permitido atacar um território da mesma cor (aliado).\n");
        } else if (mapa[idxAt - 1].tropas <= 0) {
            printf("Território atacante não possui tropas suficientes para atacar.\n");
        } else {
            // Realiza ataque
            atacar(&mapa[idxAt - 1], &mapa[idxDef - 1]);
        }

        // Verifica missões silenciosamente para cada jogador
        for (int p = 0; p < numJogadores; p++) {
            if (verificarMissao(jogadores[p].missao, mapa, qtdTerritorios, jogadores[p].cor)) {
                printf("\n🎉 Jogador %s (Cor: %s) cumpriu a missão!\n", jogadores[p].nome, jogadores[p].cor);
                printf("Missão cumprida: %s\n", jogadores[p].missao);
                // Limpa memória e encerra
                liberarMemoria(mapa, jogadores, numJogadores);
                printf("\nFim do jogo. Parabéns!\n");
                return 0;
            }
        }

        printf("\nDeseja continuar jogando? (s/n): ");
        scanf(" %c", &continuar);
    }

    // Ao sair do loop, libera memória e finaliza
    liberarMemoria(mapa, jogadores, numJogadores);
    printf("\nJogo encerrado pelo usuário. Até a próxima!\n");
    return 0;
}