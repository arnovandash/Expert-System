/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_system.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:54:18 by rojones           #+#    #+#             */
/*   Updated: 2016/09/27 08:39:10 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>

int main (int ac, char **av)
{
	int		facts[26];
	t_rule	*rules;
	
	if (ac != 2)
	{
		puts("Please specify one and only one input file!");
		return (0)
	}
	bzero(facts, 26);
	ft_read_file(av[1], rules);
}
