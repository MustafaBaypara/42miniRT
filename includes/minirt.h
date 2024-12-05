/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:13:02 by mbaypara          #+#    #+#             */
/*   Updated: 2024/12/05 14:47:42 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "utils.h"
# include "libft.h"

typedef struct s_scene
{
	t_size		size;
	t_color		ambient;
	t_list		*cameras;
	t_list		*lights;
	t_list		*objects;
}	t_scene;









#endif