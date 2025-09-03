#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Wersja z programowaniem dynamicznym
void wydawanie_reszty_dynamiczne(int kwota, int liczba_nominalow, int nominaly[], int ilosc_monet[]) {
        printf("kwota: %d\n",kwota);
        printf("nominaly: ");
        for(int i = 0; i < liczba_nominalow; i++){
        printf("%d",nominaly[i]);
        if(i==liczba_nominalow-1){
        printf("\n");
        }else printf(", ");
        }
        printf("ilosc monet(po koleji): ");
        for(int i = 0; i < liczba_nominalow; i++){
        printf("%d",ilosc_monet[i]);
        if(i==liczba_nominalow-1){
        printf("\n");
        }else printf(", ");
        }

    int *dp = (int *)malloc((kwota + 1) * sizeof(int));
    int *last_coin = (int *)malloc((kwota + 1) * sizeof(int));
    
    dp[0] = 0;
    for (int i = 1; i <= kwota; i++) {
        dp[i] = INT_MAX;
        last_coin[i] = -1;
    }
    
    for (int i = 0; i < liczba_nominalow; i++) {
        for (int j = nominaly[i]; j <= kwota; j++) {
            if (ilosc_monet[i] > 0 && dp[j - nominaly[i]] != INT_MAX && dp[j - nominaly[i]] + 1 < dp[j]) {
                dp[j] = dp[j - nominaly[i]] + 1;
                last_coin[j] = i;
            }
        }
    }
    
    if (dp[kwota] == INT_MAX) {
        printf("-1;");
    } else {
        int pozostalo = kwota;
        int *uzyte_monety = (int *)calloc(liczba_nominalow, sizeof(int));
        
        while (pozostalo > 0) {
            int nominal_index = last_coin[pozostalo];
            uzyte_monety[nominal_index]++;
            pozostalo -= nominaly[nominal_index];
            ilosc_monet[nominal_index]--;
        }
        
        int sum = 0;
        for (int i = 0; i < liczba_nominalow; i++) {
            if (uzyte_monety[i] > 0) {
            sum += uzyte_monety[i];
            }
        }
        printf("programowanie dynamiczne\n");
        printf("suma uzytych monet: %d\n",sum);
        printf("liczba uzytych nominalow(po koleji): ");
        for (int i = 0; i < liczba_nominalow; i++) {
                printf("%d", uzyte_monety[i]);
                if(i==liczba_nominalow-1){
                printf("\n");
                }else printf(", ");
        }
        
        free(uzyte_monety);
    }
    
    free(dp);
    free(last_coin);
}

// Wersja zachłanna
void wydawanie_reszty_zachlanna(int kwota, int liczba_nominalow, int nominaly[], int ilosc_monet[]){
    int *uzyte_monety = (int *)calloc(liczba_nominalow, sizeof(int));
    int pozostalo = kwota;
    
    for (int i = liczba_nominalow - 1; i >= 0; i--) {
        while (nominaly[i] <= pozostalo && ilosc_monet[i] > 0) {
            pozostalo -= nominaly[i];
            uzyte_monety[i]++;
            ilosc_monet[i]--;
        }
    }
    int sum = 0;
    if (pozostalo != 0) {
        printf("-1\n");
    } else {
        for (int i = 0; i < liczba_nominalow; i++) {
            if (uzyte_monety[i] > 0) {
            sum += uzyte_monety[i];
            }
        }
        printf("metoda zachlanna\n");
        printf("suma uzytych monet: %d\n",sum);
        printf("liczba uzytych nominalow(po koleji): ");
        for (int i = 0; i < liczba_nominalow; i++) {
                printf("%d", uzyte_monety[i]);
                if(i==liczba_nominalow-1){
                printf("\n");
                }else printf(", ");
        }
        printf("\n");
    }
    
    free(uzyte_monety);
}

int main() {
    int kwota = 9;
    int liczba_nominalow = 3;
    
    
    int nominaly[] = {1,2,5};
    int ilosc_monet[] = {2,2,2};
    int ilosc_monet_kopia[liczba_nominalow];
    
    for (int i = 0; i < liczba_nominalow; i++) {
        ilosc_monet_kopia[i] = ilosc_monet[i];
    }
       
    wydawanie_reszty_dynamiczne(kwota, liczba_nominalow, nominaly, ilosc_monet);
    
    // Przywrócenie oryginalnych ilości monet dla metody zachłannej
    for (int i = 0; i < liczba_nominalow; i++) {
        ilosc_monet[i] = ilosc_monet_kopia[i];
    }
    wydawanie_reszty_zachlanna(kwota, liczba_nominalow, nominaly, ilosc_monet);
    
    
    return 0;
}
