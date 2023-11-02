/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shechong <shechong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:46:09 by shechong          #+#    #+#             */
/*   Updated: 2023/11/02 19:24:21 by shechong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_xy	iso_map(t_xy pos)
{
	return ((t_xy){(pos.x - pos.y) * 1.4, (pos.x + pos.y) / 1.4});
}
