#include<stdio.h>
#include<stdlib.h>

#define TAM_ENTRADA 8
#define TAM_TABELA(tabela)  (int)(sizeof(tabela) / sizeof(tabela[0]))
typedef unsigned long long int bits;


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
                   8, 9,10,11,12,13,
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

int ipinverso[] = { 40,  8, 48, 16, 56, 24, 64, 32,
                    39,  7, 47, 15, 55, 23, 63, 31,
                    38,  6, 46, 14, 54, 22, 62, 30,
                    37,  5, 45, 13, 53, 21, 61, 29,
                    36,  4, 44, 12, 52, 20, 60, 28,
                    35,  3, 43, 11, 51, 19, 59, 27,
                    34,  2, 42, 10, 50, 18, 58, 26,
                    33,  1, 41,  9, 49, 17, 57, 25};



bits permutacao(bits tabelaInicial, int ordem[], int tamI, int tamordem){

    int i = 0;
    bits mascara = 0, tabelaFinal = 0;

    //Insere na tabelaFinal os bits 1 na nova posição dada pela vetor ordem[]
    for(i = 0; i < tamordem; i++){
        //Cria a mascara para pegar o valor do bit na posição da tabela original;
        mascara = (bits) 1 << (tamI - ordem[i]);
        //Caso o bit for 1, é adicionado a tabelaFinal o bit 1 na posição i.
        if ( (mascara & tabelaInicial) != 0){
            tabelaFinal = tabelaFinal | ((bits)1 << (tamordem - i - 1));
        }
        mascara = 0;
    }
    return tabelaFinal;

}

bits rounds(bits entrada, bits chave, int nround){

    bits l,r, temp, saida, temp2;
    
    //Separa a entrada em L e R, cada uma com 32 bits
    l = entrada >> (32);
    temp =l  << 32;
    r =entrada  ^ temp;    

    //Expansion permutation
    saida = permutacao(r,etable,32,TAM_TABELA(etable));

    //XOR + Permuted Choice 2
    saida = saida ^ permutacao(chave,pc2table,56,TAM_TABELA(pc2table));
    printf("CHAVE ROUND %d\n%llX\n\n", nround+1, permutacao(chave,pc2table,56,TAM_TABELA(pc2table)) );


    //sbox 
    int s1[] = { 14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
                0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
                4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
                15, 12, 8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13};

    int s2[] = { 15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
                3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
                0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
               13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9};

    int s3[] = { 10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
               13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
               13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
                1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12};

    int s4[] = {  7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
               13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
               10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
                3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14};

    int s5[] = {  2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
               14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
                4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
               11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3};

    int s6[] = { 12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
               10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
                9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
                4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13};

    int s7[] = {  4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
               13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
                1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
                6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12};

    int s8[] = { 13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
                1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
                7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
                2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11};

    unsigned int mascara = 63; // 0011 1111 
    unsigned int linha[8], mlinha = 33; // 0010 0001
    unsigned int coluna[8], mcoluna = 30; // 0001 1110
    unsigned int aux = 0;
    
    //Pega a linha e a coluna a ser utilizada de cada S-Box
    for(int i = 0; i < 8; i++){
        temp = (saida >> (6 * (8-i-1))) & mascara; 
        
        linha[i] = temp & mlinha;
        aux = linha[i] >> 5 ;
        linha[i] = (linha[i] |(aux << 1)) & 3;
        coluna[i] = temp & mcoluna;
        coluna[i] = coluna[i] >> 1;
    }

    //Pega o valor das S-Box
    temp = 0;
    temp = s1[linha[0] * 16 + coluna[0]] << 4;
    temp = (temp | s2[linha[1] * 16 + coluna[1]]) << 4;
    temp = (temp | s3[linha[2] * 16 + coluna[2]]) << 4;
    temp = (temp | s4[linha[3] * 16 + coluna[3]]) << 4;
    temp = (temp | s5[linha[4] * 16 + coluna[4]]) << 4;
    temp = (temp | s6[linha[5] * 16 + coluna[5]]) << 4;
    temp = (temp | s7[linha[6] * 16 + coluna[6]]) << 4;
    temp = (temp | s8[linha[7] * 16 + coluna[7]]);

    saida = temp;

    //Permutação(P)
    saida= permutacao(saida,ptable,32,TAM_TABELA(ptable));

    //XOR 
    saida = saida ^ l;

    r = r << 32;
    return(saida | r);
}

bits lshiftkey(bits cd,int round){

    bits c,d, mascara, temp;

    //Separa a entrada em dois
    c = cd >> (28);
    mascara = c << 28;
    d = cd ^ mascara;

    mascara = 268435455; // 0000 1111 1111 1111 1111 1111 1111 1111


    switch (round){
        case 0 :
        case 1 : 
        case 8 :  
        case 15: //lshift 1 bit
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
    
    int i = 0;
    
    //Permutação Inicial
    bits lr = permutacao(textoClaro, ip, 64, TAM_TABELA(ip));
    
    //PC-1
    bits cd = permutacao(palavraChave, pc1table, 64, TAM_TABELA(pc1table));


    printf("IP\n%llX\n\n", lr);
    printf("CHAVE\n%llX\n\n", palavraChave);
    
    //ROUND
    for( i = 0; i < 16; i++){ 
        cd = lshiftkey(cd, i);
        lr =  rounds(lr, cd, i);
        printf("ROUND %d\n%llX\n\n", i+1, lr );
    }    

    //SWAP
    bits temp = 0;

    temp = lr >> 32;
    lr = lr & (4294967295);
    lr = (lr << 32) | temp;

    printf("SWAP\n%llX\n\n", lr);

    //Permutação final
    lr = permutacao(lr, ipinverso, 64, TAM_TABELA(ipinverso)); 

    printf("IP Inverso: %llX\n\n", lr);

    return(0);
}

int main() {
    unsigned char entrada, chave;
    unsigned long long int textoClaro = 0, palavraChave = 0, a;

    //Recebe o texto claro 
    for(int i=0; i<TAM_ENTRADA; i++) {
        scanf("%hhX", &entrada);
        textoClaro = textoClaro << 8;
        textoClaro = textoClaro | entrada;
    }

    //Recebe a chave
    for(int i=0; i<TAM_ENTRADA; i++) {
        scanf("%hhX", &chave);
        palavraChave = palavraChave << 8;
        palavraChave = palavraChave | chave;
    }

    printf("PLAIN TEXT\n%llX\n\n", textoClaro);
    //printf("CHAVE\n%llX\n\n", palavraChave);

    des(textoClaro,palavraChave);

    return(0);
}