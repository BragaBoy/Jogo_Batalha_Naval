#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Função auxiliar para verificar se há sobreposição
int temSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int coordenadas[3][2]) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = coordenadas[i][0];
        int coluna = coordenadas[i][1];
        if (tabuleiro[linha][coluna] != 0) {
            return 1; // sobreposição
        }
    }
    return 0;
}

// Função auxiliar para marcar navio no tabuleiro
void marcarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int coordenadas[3][2]) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = coordenadas[i][0];
        int coluna = coordenadas[i][1];
        tabuleiro[linha][coluna] = 3;
    }
}

int main() {
    // Inicializa tabuleiro com água (0)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    int sobreposicao = 0;

    // --- NAVIO 1: Horizontal (linha 2, colunas 4 a 6) ---
    int navio1[3][2] = {{2, 4}, {2, 5}, {2, 6}};
    // --- NAVIO 2: Vertical (coluna 7, linhas 5 a 7) ---
    int navio2[3][2] = {{5, 7}, {6, 7}, {7, 7}};
    // --- NAVIO 3: Diagonal Principal (↘) iniciando em (0, 0) ---
    int navio3[3][2] = {{0, 0}, {1, 1}, {2, 2}};
    // --- NAVIO 4: Diagonal Secundária (↙) iniciando em (0, 9) ---
    int navio4[3][2] = {{0, 9}, {1, 8}, {2, 7}};

    // Validação e marcação de todos os navios
    int *navios[] = {&navio1[0][0], &navio2[0][0], &navio3[0][0], &navio4[0][0]};
    for (int n = 0; n < 4; n++) {
        int (*navio)[2] = (int (*)[2])navios[n];

        // Verifica se está dentro dos limites
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            int linha = navio[i][0];
            int coluna = navio[i][1];
            if (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 || coluna >= TAMANHO_TABULEIRO) {
                printf("Erro: Navio %d ultrapassa os limites do tabuleiro.\n", n + 1);
                return 1;
            }
        }

        // Verifica sobreposição
        if (temSobreposicao(tabuleiro, navio)) {
            printf("Erro: Sobreposição detectada no navio %d.\n", n + 1);
            return 1;
        }

        // Marca o navio no tabuleiro
        marcarNavio(tabuleiro, navio);
    }

    // Exibe o tabuleiro final
    printf("=== TABULEIRO FINAL ===\n");
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }

    return 0;
}
