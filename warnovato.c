#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
// Esta struct armazena o nome do território, a cor do exército e a quantidade de tropas
struct Territorio {
    char nome[30];  // nome do território
    char cor[10];  // cor do exército
    int tropas;  // quantidade de tropas
};

int main() {
    struct Territorio territorios[5];  // vetor de 5 territórios

    // Entrada de dados
    for (int i = 0; i < 5; i++)    {
        printf("Digite o nome do territorio %d: ", i+1);
        scanf(" %[^\n]", territorios[i].nome);  // lê nome com espaços

        printf("Digite a cor do exército do territorio %d: ", i+1);
        scanf(" %s", territorios[i].cor);  // lê cor do exército

        printf("Digite a quantidade de tropas do territorio %d: ", i+1);
        scanf("%d", &territorios[i].tropas);  // lê número de tropas

        printf("\n"); // linha em branco para melhor visualização
    }
    
    // Exibição dos dados cadastros
    printf("\n=== Dados dos Territórios ===\n");
    for (int i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i+1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n\n", territorios[i].tropas);
    }
    
    return 0;

}