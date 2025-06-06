#include <stdio.h>

#define TAM 10
#define TAM_HAB 5
#define TAM_NAVIO 3

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tab[i][j] = 0;
}

// Verifica sobreposição e posiciona navio no tabuleiro
int posicionarNavio(int tab[TAM][TAM], int coords[3][2]) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = coords[i][0], c = coords[i][1];
        if (l < 0 || l >= TAM || c < 0 || c >= TAM || tab[l][c] != 0)
            return 0; // erro
    }
    for (int i = 0; i < TAM_NAVIO; i++)
        tab[coords[i][0]][coords[i][1]] = 3;
    return 1;
}

// Gera matriz de habilidade Cone (5x5)
void gerarCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++)
            matriz[i][j] = (j >= 2 - i && j <= 2 + i) ? 1 : 0;
}

// Gera matriz de habilidade Cruz (5x5)
void gerarCruz(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++)
            matriz[i][j] = (i == 2 || j == 2) ? 1 : 0;
}

// Gera matriz de habilidade Octaedro (losango 5x5)
void gerarOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++)
            matriz[i][j] = (abs(i - 2) + abs(j - 2) <= 2) ? 1 : 0;
}

// Sobrepõe matriz de habilidade no tabuleiro com valor 5
void aplicarHabilidade(int tab[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int centroLinha, int centroColuna) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (habilidade[i][j] == 1) {
                int l = centroLinha - 2 + i;
                int c = centroColuna - 2 + j;
                if (l >= 0 && l < TAM && c >= 0 && c < TAM && tab[l][c] == 0) {
                    tab[l][c] = 5;
                }
            }
        }
    }
}

// Exibe o tabuleiro com legenda
void exibirTabuleiro(int tab[TAM][TAM]) {
    printf("\n=== TABULEIRO FINAL ===\n");
    printf("Legenda: 0=Água  3=Navio  5=Habilidade\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // --- POSICIONAMENTO DOS NAVIOS ---
    int navio1[3][2] = {{2, 4}, {2, 5}, {2, 6}};     // Horizontal
    int navio2[3][2] = {{5, 7}, {6, 7}, {7, 7}};     // Vertical
    int navio3[3][2] = {{0, 0}, {1, 1}, {2, 2}};     // Diagonal ↘
    int navio4[3][2] = {{0, 9}, {1, 8}, {2, 7}};     // Diagonal ↙

    // Validar e posicionar todos
    if (!posicionarNavio(tabuleiro, navio1) ||
        !posicionarNavio(tabuleiro, navio2) ||
        !posicionarNavio(tabuleiro, navio3) ||
        !posicionarNavio(tabuleiro, navio4)) {
        printf("Erro ao posicionar navios.\n");
        return 1;
    }

    // --- MATRIZES DE HABILIDADE ---
    int cone[TAM_HAB][TAM_HAB], cruz[TAM_HAB][TAM_HAB], octaedro[TAM_HAB][TAM_HAB];

    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    // --- POSIÇÕES DAS HABILIDADES ---
    aplicarHabilidade(tabuleiro, cone, 4, 4);       // Cone centrado em (4,4)
    aplicarHabilidade(tabuleiro, cruz, 6, 2);       // Cruz centrada em (6,2)
    aplicarHabilidade(tabuleiro, octaedro, 6, 6);   // Octaedro centrado em (6,6)

    // --- EXIBIR TABULEIRO ---
    exibirTabuleiro(tabuleiro);

    return 0;
}
