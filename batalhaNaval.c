#include <stdio.h>
#include <stdlib.h>
#include <math.h> // Necessário para a função abs() (valor absoluto)


//  1. Definições Globais (Constantes) 
#define LINHAS 10
#define COLUNAS 10
#define TAM_HABILIDADE 5 // Tamanho das matrizes de habilidade (5x5)

// Valores internos da matriz
#define AGUA 0
#define NAVIO 3
#define EFEITO 5 // Novo valor para área de habilidade

// Tipos de origem da habilidade
#define ORIGEM_CENTRO 0
#define ORIGEM_TOPO 1

//  2. Protótipos das Funções 
void inicializarTabuleiro(int tab[LINHAS][COLUNAS]);
void posicionarNavios(int tab[LINHAS][COLUNAS]);
void exibirTabuleiro(int tab[LINHAS][COLUNAS]);

// Funções para criar as matrizes de habilidade dinamicamente
void criarMatrizCone(int hab[TAM_HABILIDADE][TAM_HABILIDADE]);
void criarMatrizCruz(int hab[TAM_HABILIDADE][TAM_HABILIDADE]);
void criarMatrizOctaedro(int hab[TAM_HABILIDADE][TAM_HABILIDADE]);

// Função para aplicar a habilidade ao tabuleiro principal
void aplicarHabilidade(int tab[LINHAS][COLUNAS], 
                       int hab[TAM_HABILIDADE][TAM_HABILIDADE], 
                       int origem_l, int origem_c, int tipo_origem);

//  3. Função Principal 
int main(void) {

    // Declaração dos tabuleiros e matrizes de habilidade
    int tabuleiro[LINHAS][COLUNAS];
    int hab_cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int hab_cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int hab_octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    //  Preparação do Jogo 
    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro); // Posiciona alguns navios de exemplo

    printf(" Tabuleiro Inicial (com Navios) \n");
    exibirTabuleiro(tabuleiro);

    //  Criação Dinâmica das Habilidades 
    // (Conforme requisito, são criadas com loops e condicionais)
    criarMatrizCone(hab_cone);
    criarMatrizCruz(hab_cruz);
    criarMatrizOctaedro(hab_octaedro);

    //  Aplicação das Habilidades no Tabuleiro 
    // (Posições hardcoded, conforme simplificação)

    // Aplica o Cone (origem no TOPO) na posição (1, 4)
    aplicarHabilidade(tabuleiro, hab_cone, 1, 4, ORIGEM_TOPO);

    // Aplica a Cruz (origem no CENTRO) na posição (7, 2)
    aplicarHabilidade(tabuleiro, hab_cruz, 7, 2, ORIGEM_CENTRO);
    
    // Aplica o Octaedro (origem no CENTRO) na posição (5, 7)
    aplicarHabilidade(tabuleiro, hab_octaedro, 5, 7, ORIGEM_CENTRO);

    //  Exibição Final 
    printf("\n\n--- Tabuleiro Final (com Habilidades) ---\n");
    printf("Simbologia: [~] Agua, [N] Navio, [*] Area de Efeito\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}


//  4. Implementação das Funções Auxiliares 

/**
 * @brief Preenche o tabuleiro principal com AGUA (0).
 */
void inicializarTabuleiro(int tab[LINHAS][COLUNAS]) {
    for (int l = 0; l < LINHAS; l++) {
        for (int c = 0; c < COLUNAS; c++) {
            tab[l][c] = AGUA;
        }
    }
}

/**
 * @brief Posiciona alguns navios de exemplo no tabuleiro.
 */
void posicionarNavios(int tab[LINHAS][COLUNAS]) {
    // Navio Horizontal (Tamanho 3) na linha 2, coluna 2
    tab[2][2] = NAVIO;
    tab[2][3] = NAVIO;
    tab[2][4] = NAVIO;

    // Navio Vertical (Tamanho 3) na linha 5, coluna 8
    tab[5][8] = NAVIO;
    tab[6][8] = NAVIO;
    tab[7][8] = NAVIO;
}

/**
 * @brief Exibe o tabuleiro no console com símbolos.
 */
void exibirTabuleiro(int tab[LINHAS][COLUNAS]) {
    // Imprime cabeçalho das colunas
    printf("  ");
    for(int c = 0; c < COLUNAS; c++) printf("%d ", c);
    printf("\n");

    // Imprime linhas e conteúdo
    for (int l = 0; l < LINHAS; l++) {
        printf("%d ", l); // Imprime cabeçalho da linha
        for (int c = 0; c < COLUNAS; c++) {
            switch (tab[l][c]) {
                case AGUA:
                    printf("~ "); // Água
                    break;
                case NAVIO:
                    printf("N "); // Navio
                    break;
                case EFEITO:
                    printf("* "); // Efeito de Habilidade
                    break;
                default:
                    printf("? "); // Desconhecido
            }
        }
        printf("\n"); // Pula linha
    }
}

//  5. Implementação da Criação Dinâmica de Habilidades 

/**
 * @brief Cria uma matriz 5x5 em forma de CONE (origem no topo).
 */
void criarMatrizCone(int hab[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2; // (centro = 2 para 5x5)

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Condição: (j) está dentro do "raio" (i) a partir do centro.
            if (j >= (centro - i) && j <= (centro + i)) {
                hab[i][j] = 1; // Afetado
            } else {
                hab[i][j] = 0; // Não afetado
            }
        }
    }
}

/**
 * @brief Cria uma matriz 5x5 em forma de CRUZ (origem no centro).
 */
void criarMatrizCruz(int hab[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Condição: Está na linha central OU na coluna central.
            if (i == centro || j == centro) {
                hab[i][j] = 1; // Afetado
            } else {
                hab[i][j] = 0; // Não afetado
            }
        }
    }
}

/**
 * @brief Cria uma matriz 5x5 em forma de LOSANGO (Octaedro).
 */
void criarMatrizOctaedro(int hab[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Condição: Distância de Manhattan (abs(i-c) + abs(j-c))
            // é menor ou igual ao "raio" (centro).
            int dist = abs(i - centro) + abs(j - centro);
            if (dist <= centro) {
                hab[i][j] = 1; // Afetado
            } else {
                hab[i][j] = 0; // Não afetado
            }
        }
    }
}

// --- 6. Implementação da Sobreposição de Habilidade ---

/**
 * @brief Sobrepõe uma matriz de habilidade 5x5 no tabuleiro 10x10.
 * Valida os limites do tabuleiro.
 */
void aplicarHabilidade(int tab[LINHAS][COLUNAS], 
                       int hab[TAM_HABILIDADE][TAM_HABILIDADE], 
                       int origem_l, int origem_c, int tipo_origem) {
    
    int centro_hab = TAM_HABILIDADE / 2; // (centro = 2)
    int target_l, target_c;

    // Itera sobre a matriz de habilidade (5x5)
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            
            // 1. Verifica se esta parte da habilidade afeta (== 1)
            if (hab[i][j] == 1) {
                
                // 2. Calcula a coordenada alvo no tabuleiro principal
                if (tipo_origem == ORIGEM_CENTRO) {
                    // (i - centro_hab) calcula o deslocamento (ex: -2, -1, 0, 1, 2)
                    target_l = origem_l + (i - centro_hab);
                    target_c = origem_c + (j - centro_hab);
                } else { // ORIGEM_TOPO (para o Cone)
                    target_l = origem_l + i; // O 'i' já é o deslocamento vertical
                    target_c = origem_c + (j - centro_hab);
                }

                // 3. Validação de Limites
                // Verifica se o (target_l, target_c) está DENTRO do 10x10
                if ((target_l >= 0) && (target_l < LINHAS) &&
                    (target_c >= 0) && (target_c < COLUNAS)) 
                {
                    // 4. Aplica o efeito no tabuleiro
                    // (Não sobrescreve navios, apenas água)
                    if (tab[target_l][target_c] == AGUA) {
                         tab[target_l][target_c] = EFEITO;
                    }
                }
            }
        }
    }
}
