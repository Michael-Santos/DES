#include<stdio.h>
#include<stdlib.h>

#define TAM_ENTRADA 8
#define TAM_TABELA(tabela)  (int)(sizeof(tabela) / sizeof(tabela[0]))
typedef unsigned long long int bits;


//FAZER ESSAS DUAS TABELAS DE UM JEITO CERTO
int ip[] = {58, 50, 42, 34, 26, 18, 10, 2, 
            60, 52, 44, 36, 28, 20, 12, 4, 
            62, 54, 46, 38, 30, 22, 14, 6,
            64, 56, 48, 40, 32, 24, 16, 8,
            57, 49, 41, 33, 25, 17,  9, 1,
            59, 51, 43, 35, 27, 19, 11, 3,
            61, 53, 45, 37, 29, 21, 13, 5,
            63, 55, 47, 39, 31, 23, 15, 7,};
int etable[] = { 32, 1, 2, 3, 4, 5,
                   4, 5, 6, 7, 8, 9,
                  12,13,14,15,16,17,
                  16,17,18,19,20,21,
                  20,21,22,23,24,25,
                  24,25,26,27,28,29,
                  28,29,30,31,32, 1};
            
int ptable[] = { 16,  7, 20, 21, 29, 12, 28, 17,
                  1, 15, 23, 26,  5, 18, 31, 10,
                  2,  8, 24, 14, 32, 27,  3,  9,
                 19, 13, 30,  6, 22, 11,  4, 25};

int pc1table[] = { 57, 49, 41, 33, 25, 17,  9,
                    1, 58, 50, 42, 34, 26, 18,
                   10,  2, 59, 51, 43, 35, 27,
                   19, 11,  3, 60, 52, 44, 36,
                   63, 55, 47, 39, 31, 23, 15,
                    7, 62, 54, 46, 38, 30, 22,
                   14,  6, 61, 53, 45, 37, 29,
                   21, 13,  5, 28, 20, 12,  4};

int pc2table[] = { 14, 17, 11, 24,  1,  5,  3, 28,
                   15,  6, 21, 10, 23, 19, 12,  4,
                   26,  8, 16,  7, 27, 20, 13,  2,
                   41, 52, 31, 37, 47, 55, 30, 40,
                   51, 45, 33, 48, 44, 49, 39, 56,
                   34, 53, 46, 42, 50, 36, 29, 32};


bits permutacao(bits tabelaInicial, int ordem[], int tam){

    int i = 0;
    bits mascara = 0, tabelaFinal = 0;

    //Insere na tabelaFinal os bits 1 na nova posição dada pela vetor ordem[]
    for(i = 0; i < tam; i++){
        //Cria a mascara para pegar o valor do bit na posição da tabela original;
        mascara = (bits) 1 << (tam - ordem[i]);
        //Caso o bit for 1, é adicionado a tabelaFinal o bit 1 na posição i.
        if ( (mascara & tabelaInicial) != 0){
            tabelaFinal = tabelaFinal | ((bits)1 << (tam - i - 1));
        }
        mascara = 0;
    }
    return tabelaFinal;

}

bits rounds(bits entrada, bits chave, int nround){



    return(0);
}
bits lshiftkey(bits cd,int round){

    bits c,d, mascara, temp;

    c = cd >> (28);
    mascara = c << 28;
    d = cd ^ mascara;

    mascara = 268435455; // 1111 1111 1111 1111 1111 1111 1111


    switch (round){
        case 0 || 1 || 8 || 15: //lshift 1 bit
            temp  = c >> 27;
            c = (c << 1) | temp;
            c = c & 268435455; 

            temp = d >> 27;
            d = (d << 1) | temp;
            d = d & 268435455;
            break;
    
        default: //lshift 2 bits
            temp = c >> 26;
            c = (c << 2) | temp;
            c = c & 268435455;

            temp = d >> 26;
            d = (d << 2) | temp;
            d = d & 268435455;

            break;
    }

    c = c << 28;
    return c | d;

}


int des(bits textoClaro, bits palavraChave) {
    
    int i;
    
    bits lr = permutacao(textoClaro, ip, TAM_TABELA(ip));
    bits cd = permutacao(palavraChave, pc1table, TAM_TABELA(pc1table));


    printf("HEX : %llX", lr);

    for( i = 0; i < 16; i++){
        cd = lshiftkey(cd, i);
        lr =  rounds(lr, cd, i);
    }    
    return(0);
}
int main() {
    unsigned char entrada, chave;
    unsigned long long int textoClaro = 0, palavraChave = 0, a;

    //Recebe o texto claro 
    for(int i=0; i<TAM_ENTRADA; i++) {
        scanf("%hhu", &entrada);
        textoClaro = textoClaro << 8;
        textoClaro = textoClaro | entrada;
    }

    //Recebe a chave
    for(int i=0; i<TAM_ENTRADA; i++) {
        scanf("%hhu", &chave);
        palavraChave = palavraChave << 8;
        palavraChave = palavraChave | chave;
    }

    printf("Entrada : %llu\n", textoClaro);
    des(textoClaro,palavraChave);

    return(0);
}

/*
Despois de tanta luta por algum motivo não mudei nada e funcionou
como será que a gente vai receber a chave?
*/