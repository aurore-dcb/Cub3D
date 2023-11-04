#include "cub3d.h"

void display(t_map *data)
{
    int x;
    double cameraX;
    //coordonnees du vecteur rayon
    double rayDirX;
    double rayDirY;
    // coordonnees de la case dans laquelle on est (case de char **map) 
    int mapX;
    int mapY;
    //longueur entre la position actuelle et le prochain mur en x ou en y
    double sideDistX;
    double sideDistY;
    //longueur entre un mur en x ou en y et le prochain mur en x ou en y
    double deltaDistX;
    double deltaDistY;
    // la direction dans laquelle se deplacer en x et en y (+1 ou -1)
    int stepX;
    int stepY;

    int hit; // 1 si un mur a ete touche, 0 sinon
    int side; // est ce que c'est un mur N / S ou E / W qui a ete touche

    (void)side;
    x = -1;
    while (++x < data->width)
    {
        cameraX = 2 * x / (double)data->width - 1;
        rayDirX = data->dirX + data->planeX * cameraX;
        rayDirY = data->dirY + data->planeY * cameraX;

        mapX = (int)data->posX;
        mapY = (int)data->posY;

        if (rayDirX == 0)
            deltaDistX = 1e30;
        else
            deltaDistX = abs((int)(1 / rayDirX));
        if (rayDirY == 0)
            deltaDistY = 1e30;
        else
            deltaDistY = abs((int)(1 / rayDirY));

        hit = 0;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (data->posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (data->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
        }
    }
}
