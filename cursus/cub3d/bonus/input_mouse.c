/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 14:44:33 by yekim             #+#    #+#             */
/*   Updated: 2020/12/30 18:22:21 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	mouse_press(int button, int x, int y, t_loop *lv)
{
	(void)x;
	(void)y;
	if (button)
		lv->player->mouse = 1;
	return (0);
}

int	mouse_release(int button, int x, int y, t_loop *lv)
{
	(void)button;
	(void)x;
	(void)y;
	if (lv->player->mouse)
		lv->player->mouse = 0;
	return (0);
}

int	mouse_move(int x, int y, t_loop *lv)
{
	(void)lv;
	(void)y;
	if (lv->player->mouse)
	{
		if (x > (lv->disp->w / 2) && x <= lv->disp->w)
			turn_right(lv->player);
		else if (x < (lv->disp->w / 2) && x >= 0)
			turn_left(lv->player);
	}
	return (0);
}
