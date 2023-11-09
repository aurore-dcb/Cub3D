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

    // FLOOR CASTING

    // WALL CASTING
    x = -1;
    while (++x < data->width)
    {
        cameraX = 2 * x / (double)data->width - 1;
        rayDirX = data->dirX + data->planeX * cameraX;
        rayDirY = data->dirY + data->planeY * cameraX;

        mapX = (int)data->posX;
        mapY = (int)data->posY;
        
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
        
        int pitch = 100;
        //Calculer la taille du segment qu'il faut dessiner
        //cad la hauteur du mur en fonction de sa distance avec le plan camera
        line_height = (int)(data->height / perpWallDist);
        int drawStart = -line_height / 2 + data->height / 2 + pitch;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = line_height / 2 + data->height / 2 + pitch;
        if (drawEnd >= data->height)
            drawEnd = data->height - 1;
        // textures
        double wallX;
        if (side == 0)
            wallX = data->posY + perpWallDist * rayDirY;
        else
            wallX = data->posX + perpWallDist * rayDirX;
        wallX -= floor(wallX);

        int texX = (int)(wallX * (double)(data->tex_width));
        if (side == 0 && rayDirX > 0)
            texX = data->tex_width - texX - 1;
        if (side == 1 && rayDirY < 0)
            texX = data->tex_width - texX - 1;

        double step;
        step = 1.0 * data->tex_height / line_height;

        double texPos = (drawStart - pitch - data->height / 2 + line_height / 2) * step;
        
        int y = drawStart;
        int orien;

        // determiner l'orientation du mur que le rayon a touche
        if (side == 0)
        {
            if (stepX == 1) // est
                orien = 3;
            else if (stepX == -1) //ouest
                orien = 2;
        }
        else if (side == 1)
        {
            if (stepY == 1) //sud
                orien = 1;
            else if (stepY == -1) //nord
                orien = 0;
        }

        while (y < drawEnd)
        {
            int texY = (int)texPos & (data->tex_height - 1);
            texPos += step;
            int color = 0; // mettre en unsigned int ?
            color = what_color(data, texX, texY, orien);
            if(side == 1) 
                color = (color >> 1) & 8355711;
            data->buffer[y][x] = color;
            y++;
        }
    }
    draw(data);
    int y = 0;
    while (y < data->height)
    {
        int x = 0;
        while (x < data->width)
        {
            data->buffer[y][x] = 0;
            x++;
        }
        y++;
    }
}

int what_color(t_map *data, int texX, int texY, int orientation)
{
    // protections ?
    return (data->tex[orientation][data->tex_height * texY + texX]);
}

void	draw(t_map *data)
{
    int y;
    int x;

    y = 0;
	while (y < data->height)
	{
        x = 0;
		while (x < data->width)
		{
			data->img.data[y * data->width + x] = data->buffer[y][x];
            x++;
        }
        y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}
