/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:30:29 by mbaypara          #+#    #+#             */
/*   Updated: 2025/03/02 23:17:00 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	solve_pl(t_vector3 origin, t_vector3 dir, t_vector3 pos, t_vector3 n)
{
	double	denom;
	double	t;

	denom = dot_pd(n, dir); // isin ve duzlem arasindaki aci
	if (denom == 0)
		return (INFINITY); // isin ve duzlem paralel ise kesisim yok
	t = dot_pd(n, vec3_sub(pos, origin)) / denom; // isin ve duzlem arasindaki mesafe kesisim mesafesi
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

	v = vec3_mult(cyl.dir, dot_pd(ray.dir, cyl.dir));
	v = vec3_sub(ray.dir, v);
	u = vec3_mult(cyl.dir, dot_pd(vec3_sub(ray.origin, cyl.pos), cyl.dir));
	u = vec3_sub(vec3_sub(ray.origin, cyl.pos), u);
	i = dot_pd(v, v);
	j = 2 * dot_pd(v, u);
	k = dot_pd(u, u) - pow(cyl.radius, 2);
	a[0] = (-j + sqrt(pow(j, 2) - 4 * i * k)) / (2 * i);
	a[1] = (-j - sqrt(pow(j, 2) - 4 * i * k)) / (2 * i);
	if (a[0] < EPSILON && a[1] < EPSILON)
		return (0);
	return (1);
}

void	calc_normal(double a[2], t_cylinder cyl, double d1, double d2)
{
	double	i;

	if ((d1 >= 0 && d1 <= cyl.height && a[0] > EPSILON)
		&& (d2 >= 0 && d2 <= cyl.height && a[1] > EPSILON))
	{
		i = a[1];
		if (a[0] < a[1])
			i = a[0];
	}
	else if (d1 >= 0 && d1 <= cyl.height && a[0] > EPSILON)
		i = a[0];
	else
		i = a[1];
	a[0] = i;
}

double	isec_cap(t_ray ray, t_cylinder cyl, double d1, double d2)
{
	t_vector3	p1;
	t_vector3	p2;
	t_vector3	cap;

	cap = vec3_add(cyl.pos, vec3_mult(cyl.dir, cyl.height)); // alt capin pozisyonu icin yon ve uzunluk carpilir pozisyona eklenir
	d1 = solve_pl(ray.origin, ray.dir, cyl.pos, cyl.dir); // ust cap kesisim mesafesi hesaplaniyor
	d2 = solve_pl(ray.origin, ray.dir, cap, cyl.dir); // alt cap kesisim mesafesi hesaplaniyor
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
	d1 = dot_pd(cyl.dir, vec3_sub(vec3_mult(ray.dir, a[0]),
				vec3_sub(cyl.pos, ray.origin)));
	d2 = dot_pd(cyl.dir, vec3_sub(vec3_mult(ray.dir, a[1]),
				vec3_sub(cyl.pos, ray.origin)));
	if (!((d1 >= 0 && d1 <= cyl.height && a[0] > EPSILON)
			|| (d2 >= 0 && d2 <= cyl.height && a[0] > EPSILON)))
		return (INFINITY);
	calc_normal(a, cyl, d1, d2);
	return (a[0]);
}
