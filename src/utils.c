/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:54:43 by mbaypara          #+#    #+#             */
/*   Updated: 2025/03/01 22:27:15 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	func_swap(void *a, void *b)
{
	void	*tmp;

	tmp = a;
	a = b;
	b = tmp;
}

int quadratic_solver(t_vector3 point, double *a, double *b)
{
	double discriminant;  // Denklem discriminant’ını (b² - 4ac) saklamak için değişken
	double q;             // Sayısal kararlılık için ara hesaplama değişkeni

	// Diskriminant’ı hesapla: b² - 4ac (point.y = b, point.x = a, point.z = c)
	discriminant = point.y * point.y - 4 * point.x * point.z;

	// Eğer discriminant negatifse, gerçek kök yok (kesişim yok)
	if (discriminant < 0)
		return (0);

	// Eğer discriminant sıfırsa, tek kök var (çözüm teğet)
	else if (discriminant == 0)
	{
		// Tek kök formülü: t = -b / (2a)
		*a = -0.5 * point.y / point.x;
		*b = -0.5 * point.y / point.x;  // İki kök aynı olduğu için *b’ye de atanır
	}
	// Eğer discriminant pozitifse, iki farklı kök var
	else
	{
		// Sayısal kararlılık için q hesaplanır: b’nin işaretine göre farklı formül
		if (point.y > 0)
			q = -0.5 * (point.y + sqrt(discriminant));  // b pozitifse: q = -½(b + √D)
		else
			q = -0.5 * (point.y - sqrt(discriminant));  // b negatifse: q = -½(b - √D)

		// Kökleri hesapla: t1 = q / a, t2 = c / q
		*a = q / point.x;    // Birinci kök (t1)
		*b = point.z / q;    // İkinci kök (t2)
	}

	// Kökleri sırala: *a her zaman küçük kök olsun
	if (*a > *b)
		func_swap(a, b);  // Eğer *a > *b ise yer değiştir

	// Kesişim var, kökler bulundu, başarıyla tamamlandı
	return (1);
}

void	error_exit(char *message, int error_code)
{
	t_window	*win;

	win = getwindow();
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	if (win->mlx)
	{
		if (win->win)
		{
			mlx_destroy_window(win->mlx, win->win);
			if (win->frame->img)
				mlx_destroy_image(win->mlx, win->frame->img);
		}
		mlx_destroy_display(win->mlx);
	}
	clear_garbage();
	exit(error_code);
}

t_vector3	str_to_vect(const char *str)
{
	char		**tab;
	t_vector3	vect;

	tab = ft_split(str, ',');
	vect.x = ft_atof(tab[0]);
	vect.y = ft_atof(tab[1]);
	vect.z = ft_atof(tab[2]);
	return (vect);
}

t_color	str_to_rgb(const char *str)
{
	char	**tab;
	t_color	rgb;

	tab = ft_split(str, ',');
	rgb.r = ft_atoi(tab[0]);
	rgb.g = ft_atoi(tab[1]);
	rgb.b = ft_atoi(tab[2]);
	return (rgb);
}
