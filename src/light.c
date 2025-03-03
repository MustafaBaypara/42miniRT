/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:48:23 by mbaypara          #+#    #+#             */
/*   Updated: 2025/03/03 18:43:31 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_ray	to_light(t_impact *imp, t_light *light)
{
	t_ray	to_light;

	to_light = new_ray(imp->point, vec3_sub(light->position, imp->point)); // carpismadan isiga dogru ray
	to_light.origin = vec3_add(to_light.origin,
			vec3_mult(to_light.dir, EPSILON)); // baslangic noktasina epsilon eklenir
	to_light.dir = vec3_norm(to_light.dir); // normalize edilir
	return (to_light);
}

static double	dot_light_func(t_impact *imp, t_light *light, t_ray to_light)
{
	double	dot_light;

	// dot pd normal vektor ile isik yonu acisi yuzeyin onundeyse pozitif yoksa 0
	dot_light = get_maxf(dot_pd(imp->normal, to_light.dir), 0) // max(0, n.l)
		/ (distance(imp->point, light->position) // kesisim ile isik arasindaki mesafe
			* distance(imp->point, light->position)); // mesafenin karesi
	return (dot_light);
}

static void	do_somethings(t_scene *sc, t_color *color, t_color *diffuse)
{
	*diffuse = *mult_color_d(*diffuse, ALBEDO); // difuz rengi albedo ile carp olcekle
	*color = *mult_color(*add_color(*sc->al_color, *diffuse), *color); // ortam rengi ile difuz rengi topla ve ana renge carp
	min_color(color); // 255 den buyukse 255 yap
}

t_color	*lighting(t_scene *sc, t_impact *imp, t_color *color)
{
	t_list		*lights;
	t_light		*light;
	t_impact	*imp_objs;
	t_lighting	*l;

	l = (t_lighting *)ft_malloc(sizeof(t_lighting));
	l->diffuse = *int_color(0, 0, 0);
	lights = sc->lights;
	while (lights->next)
	{
		l->obstacle = NULL;
		light = (t_light *)lights->content;
		l->ray_to_light = to_light(imp, light); // yonu carpismadan isiga dogru olan isin
		imp_objs = check_objects(l->ray_to_light, sc, &l->obstacle); // isin ile diger objelerin kesisimi
		if (imp_objs->distance > distance(imp->point, light->position)) // golge kontrolu hesaplamasi
		{
			l->dot_light = dot_light_func(imp, light, l->ray_to_light); // isik varsa difuz hesaplama
			l->color_l = *mult_color_d(light->color, l->dot_light); // isik rengi ile difuz carpimi katkiyi verir
			l->diffuse = *add_color(l->diffuse, l->color_l); // katkiyi diffuz rengine ekle
		}
		lights = lights->next; // diger isiklar icin
	}
	do_somethings(sc, color, &l->diffuse); // devam fonskiyonu isigi ve renkleri karistirir
	return (NULL);
}
