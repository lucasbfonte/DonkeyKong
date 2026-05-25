#include "interface.h"
#include "movimentacao.h"
#include "monstro.h"
#include <stdio.h>
#include <string.h>

int main(){
    InitWindow(TAMANHO_HORIZONTAL, TAMANHO_VERTICAL, "Jogo Final");
    SetTargetFPS(FPS);

    TexturasJogo texturas;
    texturas.escada = LoadTexture("graficos/escada.png");
    texturas.plataforma = LoadTexture("graficos/plataforma.png");
    texturas.porta = LoadTexture("graficos/porta.png");
    texturas.personagem = LoadTexture("graficos/personagem.png");
    texturas.monstro = LoadTexture("graficos/monstro.png");
    // variaveis para diminuir a velocidade do personagem
    float tempoUltimoMovimento = 0.0f;
    float delayMovimento = 0.15f;
    int retornoMenu;
    int retornoJogo = 0;
    char m[MAPA_ALTURA][MAPA_LARGURA];

    float blocoTamanho = (float)GetScreenHeight() / MAPA_ALTURA;
    float comecoMapa = ((float)GetScreenWidth() - (MAPA_LARGURA * blocoTamanho)) / 2.0f;

    Monstro monstros[10];
    int numMonstros = 0;

    retornoMenu = Menu();
    switch (retornoMenu)
    {
    case 0:
        carregaMapa("mapas/Mapa1.txt", m);
        initMonstro(monstros, &numMonstros, m, blocoTamanho);

        while(!IsKeyPressed(KEY_ESCAPE) && retornoJogo == 0){
        retornoJogo = movimentoPersonagem(m, &tempoUltimoMovimento, &delayMovimento);
        desenhaMapa(texturas, m);
            for(int k = 0; k < numMonstros; k++){
            atualizaMonstro(&monstros[k], m, blocoTamanho, comecoMapa, texturas);
            } 
        }
        
        if(retornoJogo == 2){
            printf("Voce Perdeu!");
        }
        break;
    case 2:
        CloseWindow();
        break;
    default:
        break;
    }
    
    UnloadTexture(texturas.escada);
    UnloadTexture(texturas.plataforma);
    UnloadTexture(texturas.porta);
    UnloadTexture(texturas.personagem);
    UnloadTexture(texturas.monstro);
    CloseWindow();



}