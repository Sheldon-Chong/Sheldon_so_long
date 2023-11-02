/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shechong <shechong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:52:14 by shechong          #+#    #+#             */
/*   Updated: 2023/10/25 11:22:58 by shechong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	free_world_display(t_world *world, t_display *display)
{
	int	i;

	free(world->player);
	i = -1;
	while (world->grid[++i])
		free(world->grid[i]);
	free(world->grid[i]);
	free(world->grid);
	i = -1;
	while (world->tgrid[++i])
		free(world->tgrid[i]);
	free(world->tgrid[i]);
	free(world->tgrid);

	free(display->camera);
	mlx_destroy_image(display->mlx, display->sprites[1]);
	mlx_destroy_image(display->mlx, display->sprites[2]);
	mlx_destroy_image(display->mlx, display->sprites[3]);
	mlx_destroy_image(display->mlx, display->sprites[4]);
	free(display->sprites);
	free(display->grid_display);
}

void	free_ojects(t_world *world, t_display *display)
{
	t_object	*next;
	t_object	*current;

	current = world->enemies;
	while (current)
	{
		next = current->next;
		free(((t_enemy *)(current->data))->timers);
		free(((t_enemy *)(current->data))->timers->data);
		free(current->data);
		free(current);
		current = next;
	}
	free(current);
	current = world->coins;
	while (current)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	free(current);
	current = display->animations;
}

void	img_destroy(void *mlx, t_data *img)
{
	mlx_destroy_image(mlx, img->img);
	free(img);
}

void	free_obj_list(t_object *object)
{
	t_object	*temp;

	while (temp)
	{
		temp = object->next;
		free(object);
		object = temp;
	}
}

void	free_animations(t_world *world, t_display *display)
{
	t_object	*current;
	t_object	*next;

	img_destroy(display->mlx,
		((t_animator *)(display->anim_spritesheet->data))->frames[0]);
	img_destroy(display->mlx,
		((t_animator *)(display->anim_spritesheet->data))->frames[1]);
	img_destroy(display->mlx,
		((t_animator *)(display->anim_spritesheet->next->data))->frames[0]);
	img_destroy(display->mlx,
		((t_animator *)(display->anim_spritesheet->next->data))->frames[1]);
	img_destroy(display->mlx,
		((t_animator *)(display->animations->next->next->data))->frames[0]);
	img_destroy(display->mlx,
		((t_animator *)(display->animations->next->next->data))->frames[1]);
	free(((t_animator *)(display->anim_spritesheet->data))->frames);
	free(((t_animator *)(display->anim_spritesheet->data)));
	free(((t_animator *)(display->animations->next->next->data))->frames);
	free(((t_animator *)(display->anim_spritesheet->next->data))->frames);
	free(((t_animator *)(display->anim_spritesheet->next->data)));
	free_obj_list(display->anim_spritesheet);
	free_obj_list(display->animations);
}

int	endgame(t_world *world, t_display *display)
{
	free_ojects(world, display);
	free_animations(world, display);
	free_world_display(world, display);
	free(world);
	exit(0);
}
