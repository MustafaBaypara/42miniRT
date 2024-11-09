#include <mlx.h>
#include <math.h>
#include <stdio.h>

#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define TILE_SIZE 1.0
#define FOV 60.0 * (M_PI / 180.0) // 60 derece görüş açısı

// Harita tanımı (1 = duvar, 0 = boşluk)
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

typedef struct {
    double x;
    double y;
    double dir_x;
    double dir_y;
} player_t;

typedef struct {
    void *mlx;
    void *win;
    player_t player;
} game_t;

// Temel dikey çizgi çizer
void draw_vertical_line(game_t *game, int x, int start, int end, int color) {
    for (int y = start; y < end; y++) {
        mlx_pixel_put(game->mlx, game->win, x, y, color);
    }
}

void raycast(game_t *game) {
    for (int x = 0; x < WIN_WIDTH; x++) {
        // Kamera düzlemindeki koordinat (-1 ile 1 arasında değişen bir değer)
        double camera_x = 2 * x / (double)WIN_WIDTH - 1;
        double ray_dir_x = game->player.dir_x + cos(FOV / 2) * camera_x;
        double ray_dir_y = game->player.dir_y + sin(FOV / 2) * camera_x;

        // Oyuncunun bulunduğu harita karesi
        int map_x = (int)game->player.x;
        int map_y = (int)game->player.y;

        // Delta ve başlangıç mesafeleri
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);
        double side_dist_x;
        double side_dist_y;

        // Adımlar
        int step_x;
        int step_y;

        // Çarpışma tespiti
        int hit = 0;
        int side;

        // Başlangıç mesafesi ve adım belirleme
        if (ray_dir_x < 0) {
            step_x = -1;
            side_dist_x = (game->player.x - map_x) * delta_dist_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - game->player.x) * delta_dist_x;
        }
        if (ray_dir_y < 0) {
            step_y = -1;
            side_dist_y = (game->player.y - map_y) * delta_dist_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - game->player.y) * delta_dist_y;
        }

        // DDA (Dijital Diferansiyel Analiz) algoritması
        while (hit == 0) {
            // Adımı ilerlet
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            // Duvar çarpışması
            if (map[map_y][map_x] > 0) hit = 1;
        }

        // Duvarın uzunluğunu hesaplama
        double perp_wall_dist = (side == 0) ? (map_x - game->player.x + (1 - step_x) / 2) / ray_dir_x
                                            : (map_y - game->player.y + (1 - step_y) / 2) / ray_dir_y;
        int line_height = (int)(WIN_HEIGHT / perp_wall_dist);

        // Duvar çizim başlangıcı ve bitişi
        int draw_start = -line_height / 2 + WIN_HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + WIN_HEIGHT / 2;
        if (draw_end >= WIN_HEIGHT) draw_end = WIN_HEIGHT - 1;

        // Duvar rengini belirleme
        int color = (side == 1) ? 0xAAAAAA : 0xFFFFFF;

        // Dikey çizgiyi çiz
        draw_vertical_line(game, x, draw_start, draw_end, color);
    }
}

int main() {
    game_t game;
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "Simple Raycast Example");

    // Oyuncunun başlangıç konumu ve yönü
    game.player.x = 7.0;
    game.player.y = 7.0;
    game.player.dir_x = -1.0;
    game.player.dir_y = 0.0;

    // Sürekli render döngüsü
    while (1) {
        raycast(&game);
        mlx_loop(game.mlx);
    }

    return 0;
}
