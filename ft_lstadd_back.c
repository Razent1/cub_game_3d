/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashley <aashley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:11:46 by aashley           #+#    #+#             */
/*   Updated: 2021/04/20 21:46:11 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*list;

	if (lst && new)
	{
		list = *lst;
		if (list == NULL)
		{
			*lst = new;
			new->next = NULL;
		}
		else
		{
			list = ft_lstlast(*lst);
			list->next = new;
			new->next = NULL;
		}
	}
}
