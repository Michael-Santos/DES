#include<stdio.h>
#include<stdlib.h>

#define TAM_ENTRADA 8

int des() {
    return(0);
}


int main() {
    unsigned char entrada;
    unsigned long long int textoClaro = 0, palavraChave = 0;

    for(int i=0; i<TAM_ENTRADA; i++) {
        scanf("%hhu", &entrada);
        textoClaro = textoClaro << 8;
        textoClaro = textoClaro | entrada;
    }


    return(0);
}

/*
Despois de tanta luta por algum motivo não mudei nada e funcionou
como será que a gente vai receber a chave?
*/