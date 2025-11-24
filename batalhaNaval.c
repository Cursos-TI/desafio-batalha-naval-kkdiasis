#include <stdio.h>

// Desafio Batalha Naval - MateCheck



int main() {
    
    // int index = 0;
    
    int tabuleiro[10][10] = {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
    };
    char letras[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    int coluna = 1;
    
    
    //Exibindo o tabuleiro
    //Exibindo as letras    
    printf("# # ");
    for(int i=0; i<10; i++){
        printf("%c ", letras[i]);
    }
    printf("\n");

    //exibindo e enumerando colunas e linhas;
    for (int i = 0; i < 10; i++) {
        //enumerando colunas
        printf("%d - ", coluna++);
        
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        // Pula para a próxima linha após imprimir todos os elementos da linha atual
        printf("\n");
    }
    
    


    return 0;
}
