/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 09:08:12 by yekim             #+#    #+#             */
/*   Updated: 2020/12/24 10:05:23 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_animate_tex_range(const int tex_nbr)
{
	return (tex_nbr >= CONFIG_A0 && tex_nbr <= CONFIG_A4);
}

void	control_animation_idx(t_spr *spr)
{
	if (spr->ani.upflag)
	{
		if (spr->ani.idx + 1 > MAX_ANI_IDX)
		{
			spr->ani.idx -= 1;
			spr->ani.upflag = 0;
		}
		else
			spr->ani.idx += 1;
	}
	else
	{
		if (spr->ani.idx - 1 < MIN_ANI_IDX)
		{
			spr->ani.idx += 1;
			spr->ani.upflag = 1;
		}
		else
			spr->ani.idx -= 1;
	}
}

void	animate_sprite(t_spr *spr)
{
	if (spr->tex_nbr != TEXTURE_ATTACK)
		return ;
	spr->clk.end = clock();
	if (spr->clk.end - spr->clk.beg >= 500000)
	{
		control_animation_idx(spr);
		spr->tex = &(spr->ani.tex[spr->ani.idx]);
		spr->clk.beg = spr->clk.end;
	}
}
