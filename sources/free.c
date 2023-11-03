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

