/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 09:23:35 by yekim             #+#    #+#             */
/*   Updated: 2020/12/26 18:40:48 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int key, t_loop *lv)
{
	if (key == KEY_ESC)
		finish_program(lv);
	else if (key == KEY_W)
		lv->player->key |= (1 << KEY_W);
	else if (key == KEY_S)
		lv->player->key |= (1 << KEY_S);
	else if (key == KEY_A)
		lv->player->key |= (1 << KEY_A);
	else if (key == KEY_D)
		lv->player->key |= (1 << KEY_D);
	else if (key == KEY_H)
		lv->player->key |= (1 << KEY_H);
	else if (key == KEY_G)
		lv->player->key |= (1 << KEY_G);
	else if (key == KEY_F)
		open_door_trigger(lv->disp, lv->player);
	return (0);
}

int		key_release(int key, t_loop *lv)
{
	if (key == KEY_ESC)
		finish_program(lv);
	else if (key == KEY_W)
		lv->player->key &= ~(1 << KEY_W);
	else if (key == KEY_S)
		lv->player->key &= ~(1 << KEY_S);
	else if (key == KEY_A)
		lv->player->key &= ~(1 << KEY_A);
	else if (key == KEY_D)
		lv->player->key &= ~(1 << KEY_D);
	else if (key == KEY_H)
		lv->player->key &= ~(1 << KEY_H);
	else if (key == KEY_G)
		lv->player->key &= ~(1 << KEY_G);
	return (0);
}

void	key_update(t_loop *lv)
{
	if (lv->player->key & (1 << KEY_W))
		move_forward(lv->player, lv->disp->map);
	if (lv->player->key & (1 << KEY_S))
		move_backward(lv->player, lv->disp->map);
	if (lv->player->key & (1 << KEY_A))
		turn_left(lv->player);
	if (lv->player->key & (1 << KEY_D))
		turn_right(lv->player);
	set_zaxis_motion(lv->disp, lv->player);
}
