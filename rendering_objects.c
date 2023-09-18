/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shechong <shechong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:54:06 by shechong          #+#    #+#             */
/*   Updated: 2023/09/14 11:23:38 by shechong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int	draw_fov(t_enemy *enemy, t_display *display, t_data *char_array)
{
	t_xy		pos;
	t_grid_d	grid;

	grid = *(display->grid_display);
	draw_rect(char_array, (t_xy){100, 60}, (t_xy){0, 0}, 0xFFFF0000);
	pos = (t_xy){30, 0};
	draw_line(char_array, iso_map(pos),
		iso_map(move_in_dir(pos, enemy->c_ang + 20, 15)), 0x30eeff);
	draw_line(char_array, iso_map(pos),
		iso_map(move_in_dir(pos, enemy->c_ang -20, 15)), 0x30eeff);
	mlx_put_image_to_window(display->mlx, display->mlx_win, char_array->img,
		iso_map((t_xy){enemy->pos.x * 21, enemy->pos.y * 21}).x
		+ grid.offset_x - 14,
		iso_map((t_xy){enemy->pos.x * 21, enemy->pos.y * 21}).y
		+ grid.offset_y - 50);
	return (1);
}

int	render_sentry(t_display *display, t_enemy *enemy)
{
	t_grid_d	grid;

	grid = *(display->grid_display);
	enemy->current_pos = bounce((t_xy){enemy->pos.x * grid.space_x,
			enemy->pos.y * grid.space_y}, enemy->current_pos, 2);
	mlx_put_image_to_window(display->mlx, display->mlx_win,
		enemy->animator->frames[enemy->animator->current_frame]->img,
		iso_map(enemy->current_pos).x + grid.offset_x
		+ center(display->sprites[1], g_frame(enemy, 1)),
		iso_map(enemy->current_pos).y + grid.offset_y -32);
	return (1);
}

int	render_player(t_world *world, t_display *display)
{
	t_player	*player;
	t_grid_d	grid;
	void		*img;

	grid = *(display->grid_display);
	player = world->player;
	world->player->mapped_pos = iso_map((t_xy){player->pos.x * grid.space_x,
			player->pos.y * grid.space_y});
	img = player->animator.frames[player->animator.current_frame];
	render_tile(display, img, player->pos, (t_xy){12, -44});
	return (1);
}