#ifndef EXAMPLE_H
#define EXAMPLE_H

typedef struct s_img
{
	void *img;
	char *addr;
	int bpp;
	int size;
	int x;
	int y;
	int endian;
} t_img;

typedef struct s_win
{
	void *mlx;
	void *win;
	t_img *img;
	char *line;
	unsigned int color;
} t_win;

#endif // WOLF_WOLF_H