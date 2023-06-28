/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:51:14 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/27 12:53:07 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_double(void **elem)
{
	char	**aux;
	int		i;

	aux = (char **)elem;
	i = 0;
	while (aux[i])
	{
		free(aux[i]);
		i++;
	}
	free(aux);
}
