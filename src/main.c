#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define MAP_WIDTH 16
#define MAP_HEIGHT 16
#define WIDTH 32
#define HEIGHT 32
#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_SPACE 32
#define ESC_KEY 65307
#define KEY_DELAY 3

typedef struct s_player {
	float x;
	float y;
} t_player;

typedef struct s_game {
	void *mlx;
	void *win;
	int width;
	int height;
	long key_delay;
	int key_states[256];
	t_player player;
} t_game;

int map[MAP_HEIGHT][MAP_WIDTH] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

long get_current_time() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000); // Milisaniye cinsine dönüştür
}

int handle_keypress(int keycode, t_game *game) {
	game->key_states[keycode] = 1;
	return 0;
}

int handle_keyrelease(int keycode, t_game *game) {
	game->key_states[keycode] = 0;
	return 0;
}

void draw_player(t_game *game) {
	int i;
	int j;
	int x;

	x = 0;
	i = -1;
	j = 0;
	while (++i < 8)
	{
		mlx_pixel_put(game->mlx, game->win, game->player.x + i , game->player.y + j, 0x00FF0000);
		j = -1;
		while (++j < 8)
			mlx_pixel_put(game->mlx, game->win, game->player.x + i , game->player.y + j, 0x00FF0000);
	}
}

void catch_keypress(t_game *game) {
	long current_time;

	current_time = get_current_time();
	if (current_time - game->key_delay >= KEY_DELAY)
	{
		if (game->key_states[KEY_W])
			game->player.y -= 1; game->key_delay = current_time; 
		if (game->key_states[KEY_S])
			game->player.y += 1; game->key_delay = current_time; 
		if (game->key_states[KEY_A])
			game->player.x -= 1; game->key_delay = current_time; 
		if (game->key_states[KEY_D])
			game->player.x += 1; game->key_delay = current_time; 
	}
}

void gameloop(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
    draw_player(game);
	catch_keypress(game);
}

int main() {
	t_game game;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "Raycasting");
	game.width = 0;
	game.height = 0;
	game.player.x = 100;
	game.player.y = 100;
	game.key_delay = get_current_time();
	for (int i = 0; i < 256; i++) {
		game.key_states[i] = 0;
	}

	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 3, 1L << 1, handle_keyrelease, &game);
	mlx_loop_hook(game.mlx, (int (*)())gameloop, &game);
	mlx_loop(game.mlx);

	return 0;
}
