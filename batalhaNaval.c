#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//-------
//definindo cores utilizando a tabela ASCII
//-------
#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

// Desafio Batalha Naval - MateCheck
// protótipo das funçoes usadas, a configuração estão após a main
void mostraTabuleiro(int tabuleiro[10][10]);
void posicionarNavios(int tabuleiro[10][10]);
void limparTabuleiro(int tabuleiro[10][10]);
void limparTela();

int main() {
    
    int jogar = 1;

    int tabuleiro[10][10];
    
    // adicionando valores de posicao aleatorios aos navios
    srand(time(NULL));  // inicializa a semente
    
    //limpa e preenche o tabuleiro
    limparTabuleiro(tabuleiro);

    while(jogar > 0){
        limparTela();
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

    // bai bai
    printf("\nAte logo...\n");


    return 0;
}

    // funcao para limpar a tela
void limparTela(){
    printf("\033[2J\033[H");
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
            if(tabuleiro[i][j] == 0){
                printf(BLUE "%d " RESET, tabuleiro[i][j]);
            }else
                printf(GREEN "%d " RESET, tabuleiro[i][j]);

        }
        // Pula para a próxima linha após imprimir todos os elementos da linha atual
        printf("\n");
    }
}


// Verificando se é possível colocar navio na posição horizontal

int podeColocarHorizontal(int tabuleiro[10][10], int x, int y, int tamanho){
    
    // Se passar do limite do tabuleiro, retorna falso
    if (x + tamanho > 10) return 0;

    // Verifica se as posições já estão ocupadas
    for (int i = 0; i < tamanho; i++){
        if (tabuleiro[y][x + i] != 0) return 0;
    }

    return 1;
}


// Verifica se é possível colocar Vertical
int podeColocarVertical(int tabuleiro[10][10], int x, int y, int tamanho){

    // Se passar do limite retorna falso
    if (y + tamanho > 10) return 0;

    // Verifica as posições se tem algum outro posicionado
    for (int i = 0; i < tamanho; i++){
        if (tabuleiro[y + i][x] != 0) return 0;
    }

    return 1;
}


// Verifica se é possível colocar navio diagonal 1 "\"
int podeColocarDiagonal(int tabuleiro[10][10], int x, int y, int tamanho, int dir){
    int r = dir;
    printf("%d\n", r);
    // Se passar do limite
    if(r == 1){
        if (x + tamanho > 10 || y + tamanho > 10) return 0;
    
        // Verifica as posições para diagonal "\" separa um bloco 3x3 para evitar colisão
        for (int i = 0; i < tamanho; i++){
            for(int j = 0; j < tamanho; j++){
                if (tabuleiro[y + i][x + j] != 0) return 0;
                
            }
        }
    }else if(r == 0){
        
        if (x + tamanho > 10 || y - tamanho < 0) return 0;
        
        // Verifica as posições para diagonal "/" separa um bloco 3x3 para evitar colisão
        for (int i = 0; i < tamanho; i++){
            for(int j = 0; j < tamanho; j++){
                if (tabuleiro[y - i][x + j] != 0) return 0;

            }
        }
    }

    return 1;
}


// Função principal para posicionar navios no tabuleiro
void posicionarNavios(int tabuleiro[10][10]){
    
    int tamanho = 3; // os navios têm tamanho 3
    int x, y;
    
    // Inserir navio horizontal
    while (1){
        x = rand() % 10;   // posição aleatória X
        y = rand() % 10;   // posição aleatória Y

        if (podeColocarHorizontal(tabuleiro, x, y, tamanho)){
            for(int i = 0; i < tamanho; i++){
                tabuleiro[y][x + i] = 1; 
            }
            break;
        }
    }

    // Inserir navio vertical
    while (1){
        x = rand() % 10;
        y = rand() % 10;

        if (podeColocarVertical(tabuleiro, x, y, tamanho)){ // se o retorno não for verdadeiro ele não entra no if
            for(int i = 0; i < tamanho; i++){
                tabuleiro[y + i][x] = 2; 
            }
            break;
        }
    }

    // Inserir navio diagonal 1 "\" (envia int 1 para função)
    while (1){
        x = rand() % 10;
        y = rand() % 10;

        if (podeColocarDiagonal(tabuleiro, x, y, tamanho, 1)){
            for(int i = 0; i < tamanho; i++){
                tabuleiro[y + i][x + i] = 3; 
            }
            break;
        }
    }

    // Inserir navio diagonal 2 "/" (envia int 0 para função)
    while (1){
        x = rand() % 10;
        y = rand() % 10;

        if (podeColocarDiagonal(tabuleiro, x, y, tamanho, 0)){
            for(int i = 0; i < tamanho; i++){
                tabuleiro[y - i][x + i] = 4; 
            }
            break;
        }
    }
}


