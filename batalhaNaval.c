#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//--------------------------------------------
// Definindo cores utilizando a tabela ASCII
//-------------------------------------------
#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

//-----------------------------------------
// Definindo tamanho do tabuleiro
//-----------------------------------------
#define LINHAS 12
#define COLUNAS 12
#define MAR 126 // '~' onde será representado como

//---------------------------------------------------------------
// protótipo das funçoes usadas, as implementações estão após a main
//---------------------------------------------------------------
void limparTela();
void limparTabuleiro(int tabuleiro[LINHAS][COLUNAS]);
void mostraTabuleiro(int tabuleiro[LINHAS][COLUNAS]);
int podeColocarHorizontal(int tabuleiro[LINHAS][COLUNAS], int x, int y, int tamanho);
int podeColocarVertical(int tabuleiro[LINHAS][COLUNAS], int x, int y, int tamanho);
int podeColocarDiagonal(int tabuleiro[LINHAS][COLUNAS], int x, int y, int tamanho, int dir);
void posicionarNavios(int tabuleiro[LINHAS][COLUNAS]);
void habilidades(int tabuleiro[LINHAS][COLUNAS]);
void ataque(int ataque, int tabuleiro[LINHAS][COLUNAS]);

typedef enum{
    BLITZ = 1,
    CRUZ,
    FLASH
}Habilidade;

int main() {
    
    int jogar = 1;

    int tabuleiro[LINHAS][COLUNAS];
    
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
        printf("3) Habilidades\n");
        printf("0) Sair\n\n");
        printf("Digite o numero da opcao desejada: ");
        scanf("%d", &jogar);
        
        switch (jogar)
        {
        case 1: limparTabuleiro(tabuleiro); posicionarNavios(tabuleiro); break;
        case 2: limparTabuleiro(tabuleiro); break;
        case 3: habilidades(tabuleiro); break;
        default: break;
        }
    }

    // bai bai
    printf("\nAte logo...\n");


    return 0;
}

// funcao para limpar a tela
void limparTela(){
    printf("\e[H\e[2J");
}

// Reinicia o tabuleiro retirando todos os navios
void limparTabuleiro(int tabuleiro[LINHAS][COLUNAS]){
    for(int i = 0; i < LINHAS; i++){
        for(int j = 0; j < COLUNAS; j++){
            
            tabuleiro[i][j] = MAR; // 126 = '~' na tabela ASCII 
        }
    }
}

// Exibe o tabuleiro
void mostraTabuleiro(int tabuleiro[LINHAS][COLUNAS]){

    
    //Iniciando:
    printf("\n=-=-=-= BATALHA NAVAL =-=-=-=\n\n");    
    
    //Exibindo o tabuleiro
    //Enumerando a primera linha com letras
    printf("# # # ");
    for(int j=0; j < COLUNAS; j++){
        printf("%c ", 65 + j); // 'A' ASCII
    }
    
    printf("\n");
    
    
    //exibindo e enumerando as linhas;
    short int lin = 1; // para contar as linhas a partir de 1
    for (int i = 0; i < LINHAS; i++){
        
        lin<10? printf(" %2d - ", lin++) : printf(" %d - ", lin++);
        
        
        for (int j = 0; j < COLUNAS; j++) {
            
            if(tabuleiro[i][j] == MAR ){
                printf(BLUE "%c " RESET, tabuleiro[i][j]);
            }
            else if(tabuleiro[i][j] == 35){
                printf(RED "%c " RESET, tabuleiro[i][j]);
            }
            else{
                printf(GREEN "%c " RESET, tabuleiro[i][j]);
            }
        }

        // Pula para a próxima linha após imprimir todos os elementos da linha atual
        printf("\n");
    }
}


// Verifica se é possível colocar navio na posição horizontal

int podeColocarHorizontal(int tabuleiro[LINHAS][COLUNAS], int x, int y, int tamanho){
    
    // Se passar do limite do tabuleiro, retorna falso
    if (x + tamanho > LINHAS) return 0;

    // Verifica se as posições já estão ocupadas
    for (int i = 0; i < tamanho; i++){
        if (tabuleiro[y][x + i] != MAR) return 0;
    }

    return 1;
}


// Verifica se é possível colocar Vertical
int podeColocarVertical(int tabuleiro[LINHAS][COLUNAS], int x, int y, int tamanho){

    int tam = (tamanho += 2); // acrescenta 2 ao tamanho para verificar uma área de 5x3
    int y1 = y - 1;
    int x1 = x -1;
    // Se passar do limite retorna falso
    if (y + tamanho > LINHAS) return 0;

    // Verifica as posições se tem algum outro posicionado
    for (int i = 0; i < tam; i++){
        for(int j = 0; j < tamanho; j++){
            if (tabuleiro[y1 + i][x1 + j] != MAR) return 0;
        }
    }

    return 1;
}


// Verifica se é possível colocar navio diagonal 1 "\"
int podeColocarDiagonal(int tabuleiro[LINHAS][COLUNAS], int x, int y, int tamanho, int dir){
    int r = dir; // variavel para definir a direção da diagonal
    int tam = (tamanho += 2);
    int x1, y1, x2, y2;
    x1 = x - 1;
    y1 = y - 1;
    x2 = x - 1;
    y2 = y + 1;

    if(r == 1){
        // Se passar do limite retorna
        if (x + tamanho > LINHAS || y + tamanho > COLUNAS) return 0;
    
        // Verifica as posições para diagonal "\" separa um bloco 5x5 para evitar colisão
        for (int i = 0; i < tam; i++){
            for(int j = 0; j < tam; j++){
                if (tabuleiro[y1 + i][x1 + j] != MAR) return 0;
                
            }
        }
    }else if(r == 0){
        
        if (x + tamanho > LINHAS || y - tamanho < 0) return 0;
        
        // Verifica as posições para diagonal "/" separa um bloco 5x5 para evitar colisão
        for (int i = 0; i < tam; i++){
            for(int j = 0; j < tam; j++){
                if (tabuleiro[y2 - i][x2 + j] != MAR) return 0;

            }
        }
    }

    return 1;
}


// Função principal para posicionar navios no tabuleiro
void posicionarNavios(int tabuleiro[LINHAS][COLUNAS]){
    
    int tamanho = 3; // os navios têm tamanho 3
    int x, y; // cartesiano
    
    // Inserir navio horizontal
    while (1){
        x = rand() % LINHAS;   // posição aleatória X
        y = rand() % COLUNAS;   // posição aleatória Y

        if (podeColocarHorizontal(tabuleiro, x, y, tamanho)){
            for(int i = 0; i < tamanho; i++){
                tabuleiro[y][x + i] = 49; // 1 ASCII para fins de depuracao, mudar depois para uma constante 
            }
            break;
        }
    }
    
    
    // Inserir navio vertical
    while (1){
        x = rand() % COLUNAS; //traçado horizontal
        y = rand() % LINHAS; //traçado vertical

        if (podeColocarVertical(tabuleiro, x, y, tamanho)){ // se o retorno não for verdadeiro ele não entra no if
            for(int i = 0; i < tamanho; i++){
                tabuleiro[y + i][x] = 50; //ASCII 
            }
            break;
        }
    }

    // Inserir navio diagonal 1 "\" (envia int 1 para função)
    while (1){
        x = rand() % LINHAS;
        y = rand() % COLUNAS;

        if (podeColocarDiagonal(tabuleiro, x, y, tamanho, 1)){
            for(int i = 0; i < tamanho; i++){
                tabuleiro[y + i][x + i] = 51; //ASCII 
            }
            break;
        }
    }

    // Inserir navio diagonal 2 "/" (envia int 0 para função)
    while (1){
        x = rand() % LINHAS;
        y = rand() % COLUNAS;

        if (podeColocarDiagonal(tabuleiro, x, y, tamanho, 0)){
            for(int i = 0; i < tamanho; i++){
                tabuleiro[y - i][x + i] = 52; //ASCII 
            }
            break;
        }
    }
}

void habilidades(int tabuleiro[LINHAS][COLUNAS]){
    int menu = 1;

    while(menu > 0){
        limparTela();
        mostraTabuleiro(tabuleiro);
        printf("\nSelecione: \n");
        printf("1) Blitz (Cone)\n");
        printf("2) Cruz de Fogo (Cruz)\n");
        printf("3) Flash (Octaedro)\n");
        printf("0) Voltar ao menu anterior\n\n");
        printf("Digite o numero da opcao desejada: ");
        scanf("%d", &menu);
        
        switch (menu)
        {
        case 1: ataque(BLITZ, tabuleiro); break;
        case 2: ataque(CRUZ, tabuleiro); break;
        case 3: ataque(FLASH, tabuleiro); break;
        default: break;
        }
    }

}

void ataque(int ataque, int tabuleiro[LINHAS][COLUNAS]){

    switch (ataque)
    {
        case BLITZ:
        int jI = 1;
        int ini = 7; // inicio da posicao (corresponde ao index das linhas)
        int jT = 9; // corresponde ao index das colunas

        for(int i=ini; i<(ini + 3); i++){
            for(int j=0; j<jI; j++){
                tabuleiro[i][jT + j] = 35; // '#' ASCII
            }
            // cont += 2;
            jI += 2;
            jT--;
        }
    break;    
    case CRUZ:
        for(int i=0; i<LINHAS; i++){
            for(int j=0; j<COLUNAS; j++){
                if(i==((LINHAS / 2) - 1) || j==((COLUNAS / 2) - 1)){
                    tabuleiro[i][j] = 35; // '#' ASCII
                }
            }
        printf("\n");
        }
    break;
    case FLASH:
        int verificador = 1;
        jT = 2;
        jI = 1;
        ini = 0;

        for(int i=ini; i<(ini+7); i++){
            for(int j=0; j<jI; j++){
                tabuleiro[i][jT + j] = 35; // '#' ASCII
            }
                if(verificador == 1){
                    if(jI < 5){
                        jI += 2;
                        jT--;
                    }
                    else{
                        verificador = 0;
                        jI -= 2;
                        jT++;
                    }   
                }
                else{
                    jI -= 2;
                    jT++;
                }
        }
    break;    
    
    default: break;
    }

}