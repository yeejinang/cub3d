/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:42:48 by hyap              #+#    #+#             */
/*   Updated: 2022/11/08 11:55:04 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

double get_max(double x_step, double y_step)
{
	if (fabs(x_step) > fabs(y_step))
		return (fabs(x_step));
	else
		return (fabs(y_step));
}

t_matrix scale(t_matrix matrix)
{
	matrix.x0 = matrix.x0 * SCALE;
	matrix.x1 = matrix.x1 * SCALE;
	matrix.y0 = matrix.y0 * SCALE;
	matrix.y1 = matrix.y1 * SCALE;
	return (matrix);
}

t_matrix centralize(t_matrix matrix, t_game *game)
{
	matrix.x0 -= game->minimap.start.x;
	matrix.x1 -= game->minimap.start.x;
	matrix.y0 -= game->minimap.start.y;
	matrix.y1 -= game->minimap.start.y;
	return (matrix);
}

int	within_minimap_size(t_matrix matrix, t_game *game)
{
	if (matrix.x0 < game->minimap.pxsize.x && \
		matrix.y0 < game->minimap.pxsize.y && \
		matrix.x0 > 0 && matrix.y0 > 0)
		return (1);
	return (0);
}

void dda_line(t_matrix matrix, t_game *game)
{
	double		x_step;
	double		y_step;
	double		max;

	matrix = centralize(matrix, game);
	matrix = scale(matrix);
	x_step = matrix.x1 - matrix.x0;
	y_step = matrix.y1 - matrix.y0;
	max = get_max(x_step, y_step);
	x_step /= max;
	y_step /= max;
	while (((int)(matrix.x0 - matrix.x1) || (int)(matrix.y0 - matrix.y1)) && \
		within_minimap_size(matrix, game))
	{
		my_mlx_pixel_put(&(game->minimap.img), matrix.x0, matrix.y0, ORANGE);
		matrix.x0 += x_step;
		matrix.y0 += y_step;
	}
}