#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600
#define VOXEL_SIZE 0.5f
#define GRID_SIZE 5  // Küplerin oluşturacağı dünyadaki birim uzunluğu
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

void draw_voxel(App *app, Vector3 pos, int color) {
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
                  (int)projected[edges[i][1]].x, (int)projected[edges[i][1]].y, color);
    }
}

int key_handler(int keycode, App *app) {
    if (keycode == 119)  // W tuşu
        app->cameraZ += MOVE_SPEED;
    if (keycode == 115)   // S tuşu
        app->cameraZ -= MOVE_SPEED;
    if (keycode == 97)   // A tuşu
        app->cameraX += MOVE_SPEED;
    if (keycode == 100)   // D tuşu
        app->cameraX -= MOVE_SPEED;
    if (keycode == 113) // Sol ok tuşu
        app->angleY -= ROTATE_SPEED;
    if (keycode == 114) // Sağ ok tuşu
        app->angleY += ROTATE_SPEED;
    if (keycode == 111) // Yukarı ok tuşu
        app->angleX -= ROTATE_SPEED;
    if (keycode == 116) // Aşağı ok tuşu
        app->angleX += ROTATE_SPEED;
    if (keycode == 53)  // ESC tuşu
        exit(0);
    return 0;
}

int render(App *app) {
    mlx_clear_window(app->mlx, app->win);
    for (int x = -GRID_SIZE; x <= GRID_SIZE; x++) {
        for (int y = -GRID_SIZE; y <= GRID_SIZE; y++) {
            for (int z = -GRID_SIZE; z <= GRID_SIZE; z++) {
                if ((x + y + z) % 2 == 0) {
                    Vector3 pos = {x, y, z};
                    draw_voxel(app, pos, 0xFFFFFF);
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
    app.cameraX = 0; app.cameraY = 0; app.cameraZ = -5;

    mlx_key_hook(app.win, key_handler, &app);
    mlx_loop_hook(app.mlx, render, &app);
    mlx_loop(app.mlx);
    return 0;
}
