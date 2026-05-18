#include <stdio.h>
#include <string.h>
#include "raylib.h"
#define TILE 32

int main()
{
    int i, j;
    char m[30][64];
    int x, y;
   
    FILE *arquivo = fopen("Mapa1.txt", "r");

    for (i = 0; i < 30; i++)
    {
        fgets(m[i], 64, arquivo);

        // Remove \n e \r do final da string
        m[i][strcspn(m[i], "\r\n")] = '\0';
    }

    for (i = 0; i < 30; i++)
    {
        printf("%s\n", m[i]);
    }
    
    fclose(arquivo);

    InitWindow(960, 960, "Mapa1Teste");

    Texture2D lad = LoadTexture("escada.png");
    Texture2D plat = LoadTexture("plataforma.png");

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);

        for (y = 0; y < 30; y++)
        {
            for (x = 0; x < 30; x++)
            {
                if (m[y][x] == 'Z')
                {
                    Rectangle origem = {0, 0, plat.width, plat.height};
                    Rectangle destino = {x * TILE, y * TILE, TILE, TILE};
                    DrawTexturePro(plat, origem, destino, (Vector2){0, 0}, 0.0f, WHITE);
                }
                if (m[y][x] == 'H')
                {
                    Rectangle origem = {0, 0, lad.width, lad.height};
                    Rectangle destino = {x * TILE, y * TILE, TILE, TILE};
                    DrawTexturePro(lad, origem, destino, (Vector2){0, 0}, 0.0f, WHITE);
                }
            }
        }

        EndDrawing();
    }

    UnloadTexture(lad);
    printf("%d %d\n", lad.width, lad.height);
    CloseWindow();

    return 0;
}
