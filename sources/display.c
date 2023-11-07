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

    double perpWallDist; // distance entre le plan camera et le mur
    int line_height; //hauteur du mur qu'on dessine

    x = -1;
    printf("posX : %f   -    posY : %f\n", data->posX, data->posY);
    printf("dirX : %f   -    dirY : %f\n", data->dirX, data->dirY);
    // data->dirX = 0;
    // data->dirY = 1;
    while (++x < data->width)
    {
        // if (data->dirX == 1 || data->dirX == -1)
        //     cameraX = 2 * x / (double)data->width + 1;
        // else
        cameraX = 2 * x / (double)data->width - 1;
        rayDirX = data->dirX + data->planeX * cameraX;
        rayDirY = data->dirY + data->planeY * cameraX;
        
        if (x == 0)
        {
            printf("cameraX : %f\n", cameraX);
            printf("rayDirX : %f   -   rayDirY : %f\n", rayDirX, rayDirY);
        }
        mapX = (int)data->posX;
        mapY = (int)data->posY;

        // printf("mapY : %d\n",mapY);
        
        if (rayDirX == 0)
            deltaDistX = pow(10, 30);
        else
            deltaDistX = fabs(1 / rayDirX);
        if (rayDirY == 0)
            deltaDistY = pow(10, 30);
        else
            deltaDistY = fabs(1 / rayDirY);

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
            stepY = 1;
            sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
        }
        else
        {
            stepY = -1;
            sideDistY = (data->posY - mapY) * deltaDistY;
        }

        // printf("sideDistX : %f   -   ", sideDistX);
        // printf("sideDistY : %f\n", sideDistY);
        // algo pour trouver ou le rayon tape un mur : DDA
        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;                
            }
            // on s'est deplacer jusqu'au prochain x ou y entier
            // donc verifier si c'est un mur
            if (data->map[mapY][mapX] == '1')
                hit = 1;
        }

        //Caculer la distance entre le plan camera et le mur
        if (side == 0)
            perpWallDist = sideDistX - deltaDistX;
        else
            perpWallDist = sideDistY - deltaDistY;
        
        //Calculer la taille du segment qu'il faut dessiner
        //cad la hauteur du mur en fonction de sa distance avec le plan camera
        line_height = (int)(data->height / perpWallDist);
        int drawStart = -line_height / 2 + data->height / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = line_height / 2 + data->height / 2;
        if (drawEnd >= data->height)
            drawEnd = data->height - 1;
        
        //couleur du mur
        int color = 0x0000FF;
        if (side == 1)
            color = color / 2;

        vertical_line(x, drawStart, drawEnd, color, data);
    }
}
