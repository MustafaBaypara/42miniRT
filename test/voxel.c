#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 2160
#define HEIGHT 1440
#define VOXEL_SIZE 0.25f
#define GRID_SIZE 10
#define MOVE_SPEED 0.1f
#define ROTATE_SPEED 0.05f

typedef struct {
    float x, y, z;
} Vector3;

typedef struct {
    void *mlx;
    void *win;
    float cameraX, cameraY, cameraZ;
    float angleX, angleY, angleZ;
    int key_states[70000];  // Tuşların basılı olup olmadığını tutan bir dizi
    int current_color;    // Çizgi rengini belirleyen değişken
} App;

void draw_line(App *app, int x0, int y0, int x1, int y1, int color) {
    float dx = abs(x1 - x0), dy = abs(y1 - y0);
    float sx = (x0 < x1) ? 1 : -1;
    float sy = (y0 < y1) ? 1 : -1;
    float err = dx - dy;
    
    while (1) {
        if (x0 >= 0 && x0 < WIDTH && y0 >= 0 && y0 < HEIGHT)
            mlx_pixel_put(app->mlx, app->win, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        float e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}

Vector3 rotate(Vector3 p, float angleX, float angleY, float angleZ) {
    float x = p.x, y = p.y, z = p.z;
    
    y = p.y * cos(angleX) - p.z * sin(angleX);
    z = p.y * sin(angleX) + p.z * cos(angleX);
    p.x = x; p.y = y; p.z = z;

    x = p.x * cos(angleY) + p.z * sin(angleY);
    z = -p.x * sin(angleY) + p.z * cos(angleY);
    p.x = x; p.z = z;

    x = p.x * cos(angleZ) - p.y * sin(angleZ);
    y = p.x * sin(angleZ) + p.y * cos(angleZ);
    p.x = x; p.y = y;

    return p;
}

void draw_voxel(App *app, Vector3 pos) {
    Vector3 vertices[8] = {
        {pos.x - VOXEL_SIZE, pos.y - VOXEL_SIZE, pos.z - VOXEL_SIZE},
        {pos.x + VOXEL_SIZE, pos.y - VOXEL_SIZE, pos.z - VOXEL_SIZE},
        {pos.x + VOXEL_SIZE, pos.y + VOXEL_SIZE, pos.z - VOXEL_SIZE},
        {pos.x - VOXEL_SIZE, pos.y + VOXEL_SIZE, pos.z - VOXEL_SIZE},
        {pos.x - VOXEL_SIZE, pos.y - VOXEL_SIZE, pos.z + VOXEL_SIZE},
        {pos.x + VOXEL_SIZE, pos.y - VOXEL_SIZE, pos.z + VOXEL_SIZE},
        {pos.x + VOXEL_SIZE, pos.y + VOXEL_SIZE, pos.z + VOXEL_SIZE},
        {pos.x - VOXEL_SIZE, pos.y + VOXEL_SIZE, pos.z + VOXEL_SIZE}
    };

    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    Vector3 projected[8];
    for (int i = 0; i < 8; i++) {
        Vector3 rotated = rotate(vertices[i], app->angleX, app->angleY, app->angleZ);
        rotated.x += app->cameraX;
        rotated.y += app->cameraY;
        rotated.z += app->cameraZ;
        
        float distance = 5.0f;
        projected[i].x = (rotated.x / (distance - rotated.z)) * WIDTH / 4 + WIDTH / 2;
        projected[i].y = (rotated.y / (distance - rotated.z)) * HEIGHT / 4 + HEIGHT / 2;
    }

    for (int i = 0; i < 12; i++) {
        draw_line(app, (int)projected[edges[i][0]].x, (int)projected[edges[i][0]].y,
                  (int)projected[edges[i][1]].x, (int)projected[edges[i][1]].y, app->current_color);
    }
}

int key_press(int keycode, App *app) {
    if (keycode < 70000)
        app->key_states[keycode] = 1;
    
    // Tuşlara göre renk değişimi
    if (keycode == 65361) // R tuşu
        app->current_color = 0xFF0000; // Kırmızı
    else if (keycode == 65364) // G tuşu
        app->current_color = 0x00FF00; // Yeşil
    else if (keycode == 65363) // B tuşu
        app->current_color = 0x0000FF; // Mavi
    else if (keycode == 65362) // B tuşu
        app->current_color = 0xFFFFFF; // Mavi

    return 0;
}

int key_release(int keycode, App *app) {
    if (keycode < 70000)
        app->key_states[keycode] = 0;
    return 0;
}

void handle_input(App *app) {
    if (app->key_states[119]) // W tuşu
        app->cameraZ += MOVE_SPEED;
    if (app->key_states[115]) // S tuşu
        app->cameraZ -= MOVE_SPEED;
    if (app->key_states[97])  // A tuşu
        app->cameraX += MOVE_SPEED;
    if (app->key_states[100]) // D tuşu
        app->cameraX -= MOVE_SPEED;
    if (app->key_states[65361]) // Sol ok tuşu
        app->angleY -= ROTATE_SPEED;
    if (app->key_states[65363]) // Sağ ok tuşu
        app->angleY += ROTATE_SPEED;
    if (app->key_states[65362]) // Yukarı ok tuşu
        app->angleX -= ROTATE_SPEED;
    if (app->key_states[65364]) // Aşağı ok tuşu
        app->angleX += ROTATE_SPEED;
}

int render(App *app) {
    handle_input(app);
    mlx_clear_window(app->mlx, app->win);
    for (int x = -GRID_SIZE; x <= GRID_SIZE; x++) {
        for (int y = -GRID_SIZE; y <= GRID_SIZE; y++) {
            for (int z = -GRID_SIZE; z <= GRID_SIZE; z++) {
                if ((x + y + z) % 2 == 0) {
                    Vector3 pos = {x, y, z};
                    draw_voxel(app, pos);
                }
            }
        }
    }
    return 0;
}

int main() {
    App app = {0};
    app.mlx = mlx_init();
    app.win = mlx_new_window(app.mlx, WIDTH, HEIGHT, "Voxel Engine with Controls");
    app.cameraX = 0; app.cameraY = 0; app.cameraZ = -10;
    app.current_color = 0xFFFFFF; // Başlangıç rengi beyaz

    mlx_hook(app.win, 2, 1L << 0, key_press, &app);      // Tuş basma
    mlx_hook(app.win, 3, 1L << 1, key_release, &app);    // Tuş bırakma
    mlx_loop_hook(app.mlx, render, &app);                // Sürekli render
    mlx_loop(app.mlx);
    return 0;
}
