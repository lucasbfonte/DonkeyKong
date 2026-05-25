#ifndef MONTRO_H
#define MONTRO_H
#include "interface.h"

typedef struct {
    float x;
    float y;
    float velocidade;
    int direcao; // 1 = direita, -1 = esquerda
        Texture2D textura;
    float tempoUltimoMovimento;
    float delayMovimento;
} Monstro;

void initMonstro(Monstro monstros[], int* numMonstros, char m[MAPA_ALTURA][MAPA_LARGURA], float blocoTamanho);
void movimentoMonstro(Monstro* monstro, char m[MAPA_ALTURA][MAPA_LARGURA], float blocoTamanho);
int verificaColisaoMonstro(char m[MAPA_ALTURA][MAPA_LARGURA], Monstro* monstro, float blocoTamanho);
void desenhaMonstro(Monstro* monstro, TexturasJogo texturas, float blocoTamanho, float comecoMapa);
void atualizaMonstro(Monstro* monstro, char m[MAPA_ALTURA][MAPA_LARGURA], float blocoTamanho, float comecoMapa, TexturasJogo texturas); 

#endif