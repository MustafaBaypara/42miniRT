#include "mlx.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct s_vec3 {
    double x, y, z;
} t_vec3;

typedef struct s_ray {
    t_vec3 origin;
    t_vec3 direction;
} t_ray;

typedef struct s_sphere {
    t_vec3 center;
    double radius;
    int color;
} t_sphere;

typedef struct s_light {
    t_vec3 position;
    double intensity;
    int color; // Işığın rengini tutacak yeni alan
} t_light;

typedef struct s_image {
    void *img_ptr;
    char *data;
    int bpp;
    int size_line;
    int endian;
} t_image;

typedef struct s_mlx {
    void *mlx_ptr;
    void *win_ptr;
    t_image img;
    t_sphere sphere;
    t_light light;
} t_mlx;

// Vektör işlemleri
t_vec3 vec3_sub(t_vec3 a, t_vec3 b) {
    // İki vektörün farkını hesaplar ve yeni bir vektör döner
    return (t_vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_vec3 vec3_add(t_vec3 a, t_vec3 b) {
    // İki vektörün toplamını hesaplar ve yeni bir vektör döner
    return (t_vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vec3 vec3_mult(t_vec3 v, double scalar) {
    // Bir vektörü bir skaler ile çarpar ve yeni bir vektör döner
    return (t_vec3){v.x * scalar, v.y * scalar, v.z * scalar};
}

double vec3_dot(t_vec3 a, t_vec3 b) {
    // İki vektörün nokta çarpımını hesaplar ve bir skaler döner
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double vec3_length(t_vec3 v) {
    // Bir vektörün uzunluğunu hesaplar ve bir skaler döner
    return sqrt(vec3_dot(v, v));
}

t_vec3 vec3_normalize(t_vec3 v) {
    // Bir vektörü normalize eder (birim vektör yapar) ve yeni bir vektör döner
    double len = vec3_length(v);
    return (t_vec3){v.x / len, v.y / len, v.z / len};
}
// Işın-küre kesişimi
int intersect_sphere(t_ray ray, t_sphere sphere, double *t)
{
    // Işının küre ile kesişip kesişmediğini kontrol eder
    t_vec3 oc = vec3_sub(ray.origin, sphere.center); // Işının başlangıç noktası ile kürenin merkezi arasındaki vektör
    double a = vec3_dot(ray.direction, ray.direction); // Işının yön vektörünün nokta çarpımı
    double b = 2.0 * vec3_dot(oc, ray.direction); // Işının yön vektörü ile oc vektörünün nokta çarpımının iki katı
    double c = vec3_dot(oc, oc) - sphere.radius * sphere.radius; // oc vektörünün nokta çarpımı eksi kürenin yarıçapının karesi
    double discriminant = b * b - 4 * a * c; // Diskriminant hesaplanır
    if (discriminant < 0)
        return 0; // Kesişim yok
    else
    {
        discriminant = sqrt(discriminant); // Diskriminantın karekökü alınır
        double t0 = (-b - discriminant) / (2 * a); // İlk kesişim noktası
        double t1 = (-b + discriminant) / (2 * a); // İkinci kesişim noktası
        *t = (t0 < t1) ? t0 : t1; // Daha küçük olan t değeri seçilir
        return 1; // Kesişim var
    }
}

// Renk oluşturma
int create_color(int r, int g, int b) {
    // RGB değerlerinden bir renk oluşturur
    return (r << 16 | g << 8 | b);
}

// Piksel çizme
void put_pixel(t_image *img, int x, int y, int color)
{
    char *pixel;
    int offset;

    // Pikselin görüntü sınırları içinde olup olmadığını kontrol eder
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    offset = (y * img->size_line) + (x * (img->bpp / 8)); // Pikselin görüntüdeki konumunu hesaplar
    pixel = img->data + offset; // Pikselin adresini alır
    *(int *)pixel = color; // Pikseli renklendirir
}

void render_scene(t_mlx *mlx)
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            double u = (double)x / WIDTH;
            double v = (double)y / HEIGHT;
            t_ray ray = {{0, 0, 0}, {2 * u - 1, 1 - 2 * v, -1}};
            ray.direction = vec3_normalize(ray.direction);

            double t;
            if (intersect_sphere(ray, mlx->sphere, &t))
            {
                t_vec3 hit_point = vec3_add(ray.origin, vec3_mult(ray.direction, t));
                t_vec3 normal = vec3_normalize(vec3_sub(hit_point, mlx->sphere.center));
                t_vec3 light_dir = vec3_normalize(vec3_sub(mlx->light.position, hit_point));
                double diffuse = fmax(0.0, vec3_dot(normal, light_dir)) * mlx->light.intensity;

                // Işığın rengini hesaba katar
                int light_r = (mlx->light.color >> 16) & 0xFF;
                int light_g = (mlx->light.color >> 8) & 0xFF;
                int light_b = mlx->light.color & 0xFF;

                int sphere_r = (mlx->sphere.color >> 16) & 0xFF;
                int sphere_g = (mlx->sphere.color >> 8) & 0xFF;
                int sphere_b = mlx->sphere.color & 0xFF;

                int r = (int)(diffuse * sphere_r * light_r / 255);
                int g = (int)(diffuse * sphere_g * light_g / 255);
                int b = (int)(diffuse * sphere_b * light_b / 255);

                put_pixel(&mlx->img, x, y, create_color(r, g, b));
            }
            else
                put_pixel(&mlx->img, x, y, create_color(0, 0, 0));
        }
    }
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
}

int main() {
    t_mlx mlx;

    mlx.mlx_ptr = mlx_init();
    if (!mlx.mlx_ptr)
        return (EXIT_FAILURE);
    mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "miniRT - Sphere & Light");
    if (!mlx.win_ptr)
        return (EXIT_FAILURE);
    mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIDTH, HEIGHT);
    mlx.img.data = mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_line, &mlx.img.endian);

    // Küre ve ışık kaynağını başlatma
    mlx.sphere = (t_sphere){{0, 0, -5}, 1.0, create_color(150, 0, 200)};
    mlx.light = (t_light){{-8, 5, -3}, 1.0, create_color(0, 255, 255)}; // Işığın rengi beyaz olarak ayarlandı

    render_scene(&mlx);

    mlx_loop(mlx.mlx_ptr);
    return (EXIT_SUCCESS);
}