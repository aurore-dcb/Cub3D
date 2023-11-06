#include "cub3d.h"

void coor_direction_begin(t_map *data)
{
	// printf("data->y_player = %d\n", data->y_player);
	// printf("data->x_player = %d\n", data->x_player);
	int player;
	player = data->x_player;
	data->x_player = data->y_player;
	data->y_player = player;
	printf("\ndata->y_player = %d  -  ", data->y_player);
	printf("data->x_player = %d\n", data->x_player);

	if (data->map[data->y_player][data->x_player] == 'N')
	{
		printf("NORD\n");
		data->dirY = 1;
		data->dirX = 0;
	}
	else if (data->map[data->y_player][data->x_player] == 'S')
	{
		data->dirY = -1;
		data->dirX = 0;
	}
	else if (data->map[data->y_player][data->x_player] == 'E')
	{
		data->dirY = 0;
		data->dirX = 1;
	}
	else if (data->map[data->y_player][data->x_player] == 'W')
	{
		data->dirY = 0;
		data->dirX = -1;
	}
	data->posX = (double)data->x_player + 0.5;
	data->posY = (double)data->y_player + 0.5;
}

//dessiner la colonne de pixels
void vertical_line(int x, int drawStart, int drawEnd, char *color, t_map *data)
{
	(void)color;
	while (drawStart <= drawEnd)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, drawStart, 0xFF0000);
		drawStart++;
	}
}

void display_render(t_map *data)
{
	int i = data->height / data->nb_line;
	int j;

	while (i < data->height)
	{
		j = data->width / data->nb_col;
		while (j < data->width)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j, i, 0xFFFFFF);
			j += data->width / data->nb_col;
		}
		i += data->height / data->nb_line;
	}
}

// void drawHalfLine(void *mlx_ptr, void *win_ptr, int x, int y, int a, int b) {
//     int currentX = x;
//     int currentY = y;

//     // Assurez-vous que la fenêtre est ouverte et que le contexte graphique est initialisé

//     if (mlx_ptr && win_ptr) {
//         // Utilisez la Minilibx pour initialiser la fenêtre et le contexte graphique si ce n'est pas déjà fait

//         mlx_pixel_put(mlx_ptr, win_ptr, currentX, currentY, 0xFFFFFF); // Affiche le point de départ

//         // Assurez-vous que (a, b) est un vecteur non nul
//         if (a != 0 || b != 0) {
//             // Calculez la pente de la demi-droite
//             float slope = (float)b / (float)a;

//             // Déplacez-vous le long de la direction du vecteur (a, b)
//             while (currentX >= 0 && currentY >= 0) {
//                 currentX += a;
//                 currentY += b;
// 				printf("currentX : %f   -   currentY : %f\n", currentX, currentY);
//                 mlx_pixel_put(mlx_ptr, win_ptr, currentX, currentY, 0xFFFFFF); // Dessinez un pixel

//                 if (currentX < 0 || currentY < 0) {
//                     break; // Arrêtez-vous si vous sortez de l'écran
//                 }
//             }
//         }
//     }
// }
