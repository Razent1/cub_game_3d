/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_generator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:45:04 by ilya              #+#    #+#             */
/*   Updated: 2021/04/21 12:45:04 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_list_clear(t_list **begin_list)
{
	t_list	*to_free;

	if (!begin_list || !*begin_list)
		return ;
	while (*begin_list)
	{
		to_free = *begin_list;
		*begin_list = (*begin_list)->next;
		free(to_free);
	}
	*begin_list = NULL;
}

void	generate_info(t_list **head, int size, t_pars *pars)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *head;
	pars->info = (char **)ft_calloc(size + 1, sizeof(char *));
	while (tmp)
	{
		pars->info[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	pars->size_i = size;
	ft_list_clear(head);
}

void	generate_map(t_list **head, int size, t_pars *pars)
{
	int		i;
	t_list	*tmp;

	pars->map = ft_calloc(size + 1, sizeof(char *));
	tmp = *head;
	i = 0;
	while (tmp)
	{
		pars->map[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	ft_list_clear(head);
}

int	fill_map_arr(t_pars *pars, int fd, t_list *head)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup(line)));
		free(line);
	}
	ft_lstadd_back(&head, ft_lstnew(ft_strdup(line)));
	free(line);
	generate_map(&head, ft_lstsize(head), pars);
	return (fd);
}
