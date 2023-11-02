#include "cub3d.h"

void	free_char(char **tableau)
{
	int	i;

	i = 0;
	if (tableau == NULL)
		return ;
	while (tableau[i] != NULL)
	{
		free(tableau[i]);
		i++;
	}
	free(tableau);
}

void	free_char_spe(char **tableau, int len)
{
	int	i;

	i = 0;
	if (tableau == NULL)
		return ;
	while (i < len)
	{
		free(tableau[i]);
		i++;
	}
	free(tableau);
}
