/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashley <aashley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:57:10 by aashley           #+#    #+#             */
/*   Updated: 2021/04/20 21:47:55 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list			*list;

	if (!lst)
		return (NULL);
	list = lst;
	while (list->next)
		list = list->next;
	return (list);
}
