/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:09:52 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/12 18:59:01 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (lst)
	{
		if (*lst)
		{
			last_node = ft_lstlast(*lst);
			last_node->next = new;
		}
		else
		{
			*lst = new;
		}
	}
}
