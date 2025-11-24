#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Desafio Batalha Naval - MateCheck
// protótipo das funçoes usadas, a configuração estão após a main
void mostraTabuleiro(int tabuleiro[10][10]);
void posicionarNavios(int tabuleiro[10][10]);
void limparTabuleiro(int tabuleiro[10][10]);

int main() {
    
    int jogar = 1;

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
    
    while(jogar > 0){
        mostraTabuleiro(tabuleiro);
        printf("\nSelecione: \n");
        printf("1) Posicionar Navios\n");
        printf("2) Limpar tabuleiro\n");
        printf("0) Sair\n");
        printf("Digite o numero da opcao desejada: ");
        scanf("%d", &jogar);
        
        switch (jogar)
        {
        case 1: limparTabuleiro(tabuleiro); posicionarNavios(tabuleiro); break;
        case 2: limparTabuleiro(tabuleiro); break;
        default: break;
        }
    }

    return 0;
}

// sobrescreve o tabuleiro com zeros
void limparTabuleiro(int tabuleiro[10][10]){
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            
            tabuleiro[i][j] = 0;
        }
    }
}

//exibe o tabuleiro
void mostraTabuleiro(int tabuleiro[10][10]){

    char letras[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    int coluna = 1;
    
    //Iniciando:
    printf("\n=-=-=-= BATALHA NAVAL =-=-=-=\n\n");    
    
    //Exibindo o tabuleiro
    //Enumerando a primera linha com letras
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
}

//posiciona os navios no tabuleiro
void posicionarNavios(int tabuleiro[10][10]){
       
    int navio[3] = {3,3,3};
    
    int Xnavio1, Ynavio1;
    int Xnavio2, Ynavio2;
       
    
    // adicionando valores de posicao aleatorios aos navios
    srand(time(NULL));  // inicializa a semente

    Xnavio1 = Ynavio1 = rand() % 11;  // gera número de 0 a 10
    Xnavio2 = Ynavio2 = rand() % 11;  // gera número de 0 a 10
    
    //implementando colisão simples a ser melhorada depois
    //evitando bordas do tabuleiro e evitando um ao outro
    
    while((Xnavio1 +3) > 10){
        Xnavio1--;
    }

    while((Ynavio2 - 3) < 0){
        Ynavio2++;
    }
        
    
        
    // posicionando na horizontal

    for(int i=0; i<3; i++)
        tabuleiro[Ynavio1][Xnavio1++] = navio[i];
    
    // posicionamento vertical
    for(int i=0; i<3; i++)
        tabuleiro[Ynavio2--][Xnavio2] = navio[i];
}


