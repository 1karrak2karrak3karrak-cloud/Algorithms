#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int** allocate_matrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}

void free_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void print_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void generate_random_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 1; // wartości od 0 do 9
        }
    }
}

// Klasyczne mnożenie macierzy (trzy zagnieżdżone pętle)
int** classic_matrix_multiply(int** A, int** B, int n) {
    int** C = allocate_matrix(n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j]; 
            }
        }
    }
    
    return C;
}

void matrix_add(int** A, int** B, int** C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j]; 
        }
    }
}

void matrix_subtract(int** A, int** B, int** C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] - B[i][j]; 
        }
    }
}

void split_matrix(int** parent, int** child, int i_start, int j_start, int size) {
    for (int i1 = 0, i2 = i_start; i1 < size; i1++, i2++) {
        for (int j1 = 0, j2 = j_start; j1 < size; j1++, j2++) {
            child[i1][j1] = parent[i2][j2];
        }
    }
}

void merge_matrix(int** child, int** parent, int i_start, int j_start, int size) {
    for (int i1 = 0, i2 = i_start; i1 < size; i1++, i2++) {
        for (int j1 = 0, j2 = j_start; j1 < size; j1++, j2++) {
            parent[i2][j2] = child[i1][j1];
        }
    }
}

// Mnożenie macierzy metodą "dziel i zwyciężaj"
int** divide_and_conquer_multiply(int** A, int** B, int n) {
    int** C = allocate_matrix(n);
    
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    } else {
        int new_size = n / 2;
        
        int** A11 = allocate_matrix(new_size);
        int** A12 = allocate_matrix(new_size);
        int** A21 = allocate_matrix(new_size);
        int** A22 = allocate_matrix(new_size);
        
        int** B11 = allocate_matrix(new_size);
        int** B12 = allocate_matrix(new_size);
        int** B21 = allocate_matrix(new_size);
        int** B22 = allocate_matrix(new_size);
        
        int** C11 = allocate_matrix(new_size);
        int** C12 = allocate_matrix(new_size);
        int** C21 = allocate_matrix(new_size);
        int** C22 = allocate_matrix(new_size);
        
        // Podział macierzy A i B na podmacierze
        split_matrix(A, A11, 0, 0, new_size);
        split_matrix(A, A12, 0, new_size, new_size);
        split_matrix(A, A21, new_size, 0, new_size);
        split_matrix(A, A22, new_size, new_size, new_size);
        
        split_matrix(B, B11, 0, 0, new_size);
        split_matrix(B, B12, 0, new_size, new_size);
        split_matrix(B, B21, new_size, 0, new_size);
        split_matrix(B, B22, new_size, new_size, new_size);
        
        int** temp1 = allocate_matrix(new_size);
        int** temp2 = allocate_matrix(new_size);
        
        // C11 = A11*B11 + A12*B21
        matrix_add(divide_and_conquer_multiply(A11, B11, new_size),
                  divide_and_conquer_multiply(A12, B21, new_size),
                  C11, new_size);
        
        // C12 = A11*B12 + A12*B22
        matrix_add(divide_and_conquer_multiply(A11, B12, new_size),
                  divide_and_conquer_multiply(A12, B22, new_size),
                  C12, new_size);
        
        // C21 = A21*B11 + A22*B21
        matrix_add(divide_and_conquer_multiply(A21, B11, new_size),
                  divide_and_conquer_multiply(A22, B21, new_size),
                  C21, new_size);
        
        // C22 = A21*B12 + A22*B22
        matrix_add(divide_and_conquer_multiply(A21, B12, new_size),
                  divide_and_conquer_multiply(A22, B22, new_size),
                  C22, new_size);
        
        merge_matrix(C11, C, 0, 0, new_size);
        merge_matrix(C12, C, 0, new_size, new_size);
        merge_matrix(C21, C, new_size, 0, new_size);
        merge_matrix(C22, C, new_size, new_size, new_size);
        
        free_matrix(A11, new_size);
        free_matrix(A12, new_size);
        free_matrix(A21, new_size);
        free_matrix(A22, new_size);
        
        free_matrix(B11, new_size);
        free_matrix(B12, new_size);
        free_matrix(B21, new_size);
        free_matrix(B22, new_size);
        
        free_matrix(C11, new_size);
        free_matrix(C12, new_size);
        free_matrix(C21, new_size);
        free_matrix(C22, new_size);
        
        free_matrix(temp1, new_size);
        free_matrix(temp2, new_size);
    }
    
    return C;
}

// Mnożenie macierzy algorytmem Strassena
int** strassen_multiply(int** A, int** B, int n) {
    int** C = allocate_matrix(n);
    
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    } else {
        int new_size = n / 2;
        
        int** A11 = allocate_matrix(new_size);
        int** A12 = allocate_matrix(new_size);
        int** A21 = allocate_matrix(new_size);
        int** A22 = allocate_matrix(new_size);
        
        int** B11 = allocate_matrix(new_size);
        int** B12 = allocate_matrix(new_size);
        int** B21 = allocate_matrix(new_size);
        int** B22 = allocate_matrix(new_size);
        
        int** C11 = allocate_matrix(new_size);
        int** C12 = allocate_matrix(new_size);
        int** C21 = allocate_matrix(new_size);
        int** C22 = allocate_matrix(new_size);
        
        split_matrix(A, A11, 0, 0, new_size);
        split_matrix(A, A12, 0, new_size, new_size);
        split_matrix(A, A21, new_size, 0, new_size);
        split_matrix(A, A22, new_size, new_size, new_size);
        
        split_matrix(B, B11, 0, 0, new_size);
        split_matrix(B, B12, 0, new_size, new_size);
        split_matrix(B, B21, new_size, 0, new_size);
        split_matrix(B, B22, new_size, new_size, new_size);
        
        int** M1 = allocate_matrix(new_size);
        int** M2 = allocate_matrix(new_size);
        int** M3 = allocate_matrix(new_size);
        int** M4 = allocate_matrix(new_size);
        int** M5 = allocate_matrix(new_size);
        int** M6 = allocate_matrix(new_size);
        int** M7 = allocate_matrix(new_size);
        
        int** temp1 = allocate_matrix(new_size);
        int** temp2 = allocate_matrix(new_size);
        
        // Obliczanie M1 do M7
        // M1 = (A11 + A22) * (B11 + B22)
        matrix_add(A11, A22, temp1, new_size);
        matrix_add(B11, B22, temp2, new_size);
        M1 = strassen_multiply(temp1, temp2, new_size);
        
        // M2 = (A21 + A22) * B11
        matrix_add(A21, A22, temp1, new_size);
        M2 = strassen_multiply(temp1, B11, new_size);
        
        // M3 = A11 * (B12 - B22)
        matrix_subtract(B12, B22, temp2, new_size);
        M3 = strassen_multiply(A11, temp2, new_size);
        
        // M4 = A22 * (B21 - B11)
        matrix_subtract(B21, B11, temp2, new_size);
        M4 = strassen_multiply(A22, temp2, new_size);
        
        // M5 = (A11 + A12) * B22
        matrix_add(A11, A12, temp1, new_size);
        M5 = strassen_multiply(temp1, B22, new_size);
        
        // M6 = (A21 - A11) * (B11 + B12)
        matrix_subtract(A21, A11, temp1, new_size);
        matrix_add(B11, B12, temp2, new_size);
        M6 = strassen_multiply(temp1, temp2, new_size);
        
        // M7 = (A12 - A22) * (B21 + B22)
        matrix_subtract(A12, A22, temp1, new_size);
        matrix_add(B21, B22, temp2, new_size);
        M7 = strassen_multiply(temp1, temp2, new_size);
        
        // Obliczanie C11, C12, C21, C22
        // C11 = M1 + M4 - M5 + M7
        matrix_add(M1, M4, temp1, new_size);
        matrix_subtract(temp1, M5, temp2, new_size);
        matrix_add(temp2, M7, C11, new_size);
        
        // C12 = M3 + M5
        matrix_add(M3, M5, C12, new_size);
        
        // C21 = M2 + M4
        matrix_add(M2, M4, C21, new_size);
        
        // C22 = M1 - M2 + M3 + M6
        matrix_subtract(M1, M2, temp1, new_size);
        matrix_add(temp1, M3, temp2, new_size);
        matrix_add(temp2, M6, C22, new_size);
        
        merge_matrix(C11, C, 0, 0, new_size);
        merge_matrix(C12, C, 0, new_size, new_size);
        merge_matrix(C21, C, new_size, 0, new_size);
        merge_matrix(C22, C, new_size, new_size, new_size);
        
        free_matrix(A11, new_size);
        free_matrix(A12, new_size);
        free_matrix(A21, new_size);
        free_matrix(A22, new_size);
        
        free_matrix(B11, new_size);
        free_matrix(B12, new_size);
        free_matrix(B21, new_size);
        free_matrix(B22, new_size);
        
        free_matrix(C11, new_size);
        free_matrix(C12, new_size);
        free_matrix(C21, new_size);
        free_matrix(C22, new_size);
        
        free_matrix(M1, new_size);
        free_matrix(M2, new_size);
        free_matrix(M3, new_size);
        free_matrix(M4, new_size);
        free_matrix(M5, new_size);
        free_matrix(M6, new_size);
        free_matrix(M7, new_size);
        
        free_matrix(temp1, new_size);
        free_matrix(temp2, new_size);
    }
    
    return C;
}

int main() {
    srand(time(NULL));

for(int n = 16; n <= 512; n = n*2){    
    //int n = 4; // Rozmiar macierzy (musi być potęgą dwójki)
    
    int** A = allocate_matrix(n);
    int** B = allocate_matrix(n);
    
    generate_random_matrix(A, n);
    generate_random_matrix(B, n);
    
    print_matrix(A, n);
    print_matrix(B, n);
    printf("%d ",n);
    // Klasyczne mnożenie
  printf("\nKlasyczne mnożenie macierzy:\n");
  clock_t start = clock();
  int** C_classic = classic_matrix_multiply(A, B, n);
  clock_t stop = clock();

printf ("%lf ", (double)(stop - start)/CLOCKS_PER_SEC);
    print_matrix(C_classic, n);
    free_matrix(C_classic, n);
    
    // Mnożenie "dziel i zwyciężaj"
  printf("\nMnożenie 'dziel i zwyciężaj':\n");
  start = clock();
  int** C_dac = divide_and_conquer_multiply(A, B, n);
  stop = clock();

printf ("%lf ", (double)(stop - start)/CLOCKS_PER_SEC); 
    print_matrix(C_dac, n);
    free_matrix(C_dac, n);
    
    // Mnożenie algorytmem Strassena
   printf("\nMnożenie algorytmem Strassena:\n");
   start = clock(); 
   int** C_strassen = strassen_multiply(A, B, n);
   stop = clock();

printf ("%lf\n", (double)(stop - start)/CLOCKS_PER_SEC);

    print_matrix(C_strassen, n);
    free_matrix(C_strassen, n);
    
    free_matrix(A, n);
    free_matrix(B, n);
    
}

    return 0;
}
