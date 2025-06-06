#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

int main() {
    // Declaração e inicialização do tabuleiro com valor 0 (água)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Coordenadas iniciais dos navios
    int linha_navio_horizontal = 2;
    int coluna_navio_horizontal = 4;

    int linha_navio_vertical = 5;
    int coluna_navio_vertical = 7;

    int i;
    int sobreposicao = 0;

    // Validação do navio horizontal
    if (coluna_navio_horizontal + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("Erro: Navio horizontal excede os limites do tabuleiro.\n");
        return 1;
    }

    // Validação do navio vertical
    if (linha_navio_vertical + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("Erro: Navio vertical excede os limites do tabuleiro.\n");
        return 1;
    }

    // Verifica se há sobreposição nas posições do navio horizontal
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha_navio_horizontal][coluna_navio_horizontal + i] != 0) {
            sobreposicao = 1;
        }
    }

    // Verifica se há sobreposição nas posições do navio vertical
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha_navio_vertical + i][coluna_navio_vertical] != 0) {
            sobreposicao = 1;
        }
    }

    if (sobreposicao) {
        printf("Erro: Sobreposição de navios detectada.\n");
        return 1;
    }

    // Posiciona navio horizontal (marca com valor 3)
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha_navio_horizontal][coluna_navio_horizontal + i] = 3;
    }

    // Posiciona navio vertical (marca com valor 3)
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha_navio_vertical + i][coluna_navio_vertical] = 3;
    }

    // Exibe o tabuleiro
    printf("=== TABULEIRO ===\n");
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }

    return 0;
}
