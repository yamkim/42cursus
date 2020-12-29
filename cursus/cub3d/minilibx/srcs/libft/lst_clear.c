/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 07:26:24 by yekim             #+#    #+#             */
/*   Updated: 2020/12/29 07:26:38 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lst_clear(t_lst **lst)
{
	if (lst == 0)
		return ;
	if (*lst == NULL)
		return ;
	lst_clear(&((*lst)->next));
	free(*lst);
	*lst = NULL;
}
