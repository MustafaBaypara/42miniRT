/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:30:29 by mbaypara          #+#    #+#             */
/*   Updated: 2025/03/04 02:31:52 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	solve_pl(t_vector3 origin, t_vector3 dir, t_vector3 pos, t_vector3 n)
{
	double	denom;
	double	t;

	denom = dot_pd(n, dir); // isin vesilindir kapagi arasindaki aci
	if (denom == 0)
		return (INFINITY); // isin ve duzlem paralel ise kesisim yok
	t = dot_pd(n, vec3_sub(pos, origin)) / denom; // isin ve duzlem arasindaki kesisim mesafesi / denom aciyi hesaba katmasi icin
	if (t > EPSILON) // kesisim mesafesi varsa
		return (t);
	return (INFINITY); // kesisim yoksa
}

int	solve_cyl(double a[2], t_ray ray, t_cylinder cyl)
{
	t_vector3	v;
	t_vector3	u;
	double		i;
	double		j;
	double		k;

	// İkinci dereceden bir denklem (it² + jt + k = 0) oluşturulur ve çözülür.
	v = vec3_mult(cyl.dir, dot_pd(ray.dir, cyl.dir)); // isin yonu silindir eksenine paralel olan kisim
	v = vec3_sub(ray.dir, v); // paralel olmayan kisim // eksene dik kisim
	u = vec3_mult(cyl.dir, dot_pd(vec3_sub(ray.origin, cyl.pos), cyl.dir)); // isin baslangic noktasi silindir eksenine paralel olan kisim
	u = vec3_sub(vec3_sub(ray.origin, cyl.pos), u); // paralel olmayan kisim // eksene dik kisim
	
	i = dot_pd(v, v); // ikinci dereceden denklem icin t² katsayisi
	j = 2 * dot_pd(v, u); //  t katsayisi
	k = dot_pd(u, u) - pow(cyl.radius, 2); // sabit katsayisi
	a[0] = (-j + sqrt(pow(j, 2) - 4 * i * k)) / (2 * i); // denklemin birinci koku t = (-j + √(j² - 4ik)) / (2i)
	a[1] = (-j - sqrt(pow(j, 2) - 4 * i * k)) / (2 * i); // denklemin ikinci koku t = (-j - √(j² - 4ik)) / (2i)
	if (a[0] < EPSILON && a[1] < EPSILON) // kesisim mesafesi sifirdan kucukse kesisim yok
		return (0);
	return (1); // kesisim varsa a[0] ve a[1] degerleri atanir ve 1 dondurulur
}

void	calc_normal(double a[2], t_cylinder cyl, double d1, double d2)
{
	double	i;

	if ((d1 >= 0 && d1 <= cyl.height && a[0] > EPSILON) // iki adet kesisim varsa
		&& (d2 >= 0 && d2 <= cyl.height && a[1] > EPSILON))
	{
		i = a[1];
		if (a[0] < a[1]) // en yakin olan secilir
			i = a[0];
	}
	else if (d1 >= 0 && d1 <= cyl.height && a[0] > EPSILON) // sadece bir kesisim varsa
		i = a[0];
	else // o kesisim alinir
		i = a[1];
	a[0] = i;
}

double	isec_cap(t_ray ray, t_cylinder cyl, double d1, double d2)
{
	t_vector3	p1;
	t_vector3	p2;
	t_vector3	cap;

	cap = vec3_add(cyl.pos, vec3_mult(cyl.dir, cyl.height)); // alt capin pozisyonu icin yon ve uzunluk carpilir pozisyona eklenir
	d1 = solve_pl(ray.origin, ray.dir, cyl.pos, cyl.dir); // ust cap kesisim mesafesi hesaplaniyor // aci hesaplanir
	d2 = solve_pl(ray.origin, ray.dir, cap, cyl.dir); // alt cap kesisim mesafesi hesaplaniyor // dik aci ise kesisiyor
	if (d1 < INFINITY && d2 < INFINITY) // iki cap varsa
	{
		p1 = vec3_add(ray.origin, vec3_mult(ray.dir, d1)); // kesisim noktasi hesaplaniyor
		p2 = vec3_add(ray.origin, vec3_mult(ray.dir, d2)); // kesisim mesaesi ile isin yonu carpilir ve isin baslangic noktasina eklenir
		if ((d1 < INFINITY && distance(p1, cyl.pos) <= cyl.radius) // kesisim noktasi ile cap yaricapi icinde mi kontrolu
			&& (d2 < INFINITY && distance(p2, cap) <= cyl.radius))
			return (get_minf(d1, d2)); // ikisi de kesisiyorsa en yakin olan alinir
		else if (d1 < INFINITY && distance(p1, cyl.pos) <= cyl.radius) // sadece ust
			return (d1);
		else if (d2 < INFINITY && distance(p2, cap) <= cyl.radius) // sadece alt
			return (d2);
	}
	return (INFINITY); // kesisim yoksa
}

double	isec_side(t_ray ray, t_cylinder cyl)
{
	double	a[2];
	double	d1;
	double	d2;

	if (!solve_cyl(a, ray, cyl)) // ikinci dereceden denklemi cozer
		return (INFINITY);
	d1 = dot_pd(cyl.dir, vec3_sub(vec3_mult(ray.dir, a[0]), // silindir ekseni ustundeki ilk kesisim noktasi mesafesi hesaplaniyor
				vec3_sub(cyl.pos, ray.origin)));
	d2 = dot_pd(cyl.dir, vec3_sub(vec3_mult(ray.dir, a[1]), // silindir ekseni ustundeki ikinci kesisim noktasi mesafesi hesaplaniyor
				vec3_sub(cyl.pos, ray.origin)));
	if (!((d1 >= 0 && d1 <= cyl.height && a[0] > EPSILON) // kesisim noktasi silindir yuksekligi icinde mi kontrolu
			|| (d2 >= 0 && d2 <= cyl.height && a[1] > EPSILON))) // mainde duzelecek
		return (INFINITY); // kesisim yoksa
	calc_normal(a, cyl, d1, d2); // fonksiyon devami, uygun mesafe secilir ve a guncellenir
	return (a[0]); // kesisim mesafesi dondurulur
}
