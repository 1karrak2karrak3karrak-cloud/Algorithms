#include <stdio.h>
#include <stdlib.h>

int maxDiamonds(int N, int M, int D[N][M]) {
    int C[N][M];
    C[0][0] = D[0][0];
    
    for (int j = 1; j < M; j++) {
        C[0][j] = C[0][j-1] + D[0][j];
    }
    
    for (int i = 1; i < N; i++) {
        C[i][0] = C[i-1][0] + D[i][0];
    }
    
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            C[i][j] = (C[i-1][j] > C[i][j-1] ? C[i-1][j] : C[i][j-1]) + D[i][j];
        }
    }
    
    return C[N-1][M-1];
}

int main() {
    int N, M;
    
    printf("Podaj liczbę wierszy (N): ");
    scanf("%d", &N);
    printf("Podaj liczbę kolumn (M): ");
    scanf("%d", &M);
    
    int D[N][M];
    
    printf("Wprowadź planszę (0 - brak diamentu, 1 - diament):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &D[i][j]);
        }
        printf("%d wiersz\n",i);
    }
    
    int result = maxDiamonds(N, M, D);
    printf("Maksymalna liczba diamentów do zebrania: %d\n", result);
    
    return 0;
}
