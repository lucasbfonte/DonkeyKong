#include "monstro.h"

    void initMonstro(Monstro monstros[], int* numMonstros, char m[MAPA_ALTURA][MAPA_LARGURA], float blocoTamanho){
    *numMonstros = 0;
    for(int i = 0; i < MAPA_ALTURA; i++){
        for(int j = 0; j < MAPA_LARGURA; j++){
            if(m[i][j] == 'M'){
                monstros[*numMonstros].velocidade = 1.0f;
                monstros[*numMonstros].direcao = 1;
                monstros[*numMonstros].textura = LoadTexture("graficos/monstro.png");
                monstros[*numMonstros].tempoUltimoMovimento = 0.0f;
                monstros[*numMonstros].delayMovimento = 0.5f;
                monstros[*numMonstros].x = j * blocoTamanho;
                monstros[*numMonstros].y = i * blocoTamanho;
                (*numMonstros)++;
            }
        }
    }
}

void movimentoMonstro(Monstro* monstro, char m[MAPA_ALTURA][MAPA_LARGURA], float blocoTamanho){
    float tempoAtual = GetTime();
    if (tempoAtual - monstro->tempoUltimoMovimento < monstro->delayMovimento) { 
        return;
    }

    int gridX = (int)(monstro->x / blocoTamanho); 
    int gridY = (int)(monstro->y / blocoTamanho);

    // Verifica se o próximo movimento é possível
    if(monstro->direcao == 1){ // Movendo para a direita
        if(gridX + 1 < MAPA_LARGURA && (m[gridY + 1][gridX + 1] == 'Z' || m[gridY + 1][gridX + 1] == 'H')){ // Verifica se o bloco à direita abaixo é um chão ou uma escada
            monstro->x += monstro->velocidade * blocoTamanho; // Move para a direita
        } else {
            monstro->direcao = -1; // Muda de direção
        }
    } else { // Movendo para a esquerda
        if(gridX - 1 >= 0 && (m[gridY + 1][gridX - 1] == 'Z' || m[gridY + 1][gridX - 1] == 'H')){ // Verifica se o bloco à esquerda abaixo é um chão ou uma escada
            monstro->x -= monstro->velocidade * blocoTamanho; // Move para a esquerda
        } else {
            monstro->direcao = 1; // Muda de direção
        }
    }

    monstro->tempoUltimoMovimento = tempoAtual;
}

void desenhaMonstro(Monstro* monstro, TexturasJogo texturas, float blocoTamanho, float comecoMapa){
Rectangle origem = {0, 0, monstro->textura.width, monstro->textura.height};
Rectangle destino = {comecoMapa + monstro->x, monstro->y, blocoTamanho, blocoTamanho};
DrawTexturePro(monstro->textura, origem, destino, (Vector2){0, 0}, 0.0f, WHITE);
}

int verificaColisaoMonstro(char m[MAPA_ALTURA][MAPA_LARGURA], Monstro* monstro, float blocoTamanho){
    for(int y = 0; y < MAPA_ALTURA; y++){
        for(int x = 0; x < MAPA_LARGURA; x++){
            if(m[y][x] == 'P'){
                int monstroGridX = (int)(monstro->x / blocoTamanho);
                int monstroGridY = (int)(monstro->y / blocoTamanho);
                if(monstroGridX == x && monstroGridY == y){
                    return 1; // Colisão detectada
                }
            }
        }
    }
    return 0; // Nenhuma colisão detectada
}

void atualizaMonstro(Monstro* monstro, char m[MAPA_ALTURA][MAPA_LARGURA], float blocoTamanho, float comecoMapa, TexturasJogo texturas){
    movimentoMonstro(monstro, m, blocoTamanho);
    desenhaMonstro(monstro, texturas, blocoTamanho, comecoMapa);
    if(verificaColisaoMonstro(m, monstro, blocoTamanho)){
        CloseWindow();
    }
}