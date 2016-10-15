/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_system.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:54:18 by rojones           #+#    #+#             */
/*   Updated: 2016/10/15 09:48:53 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_system.h"

int main (int ac, char **av)
{
	int		i = 0;
	char	*file;

	file = NULL;
	g_short = 0;
	if (ac == 1)
	{
		puts ("expecting './ex_sys [-s | -i] knowladgebase_file'");
	}
	while (++i < ac)
	{
		if (strcmp(av[i], "-s") == 0)
			g_short = 1;
		else if (strcmp(av[i], "-i") == 0)
			g_infer = 1;
		else if (file == NULL)
			file = av[i];
		else
		{
			puts("Please specify one and only one input file!");
			return (0);
		}
	}
	g_num_rules = 1;
	bzero(g_default, 26);
	i = -1;
	while (++i < 26)
		g_facts[i]= -1;
	ft_read_file(file);
	i = 0;
	while (g_prove[i] != '\0')
	{
		int solving[26];
		bzero(solving, 26);
		solving[g_prove[i] -'A'] = 1;
		printf("\x1B[32mSolved for %c - Result: %d\n\n\x1B[0m"
				,g_prove[i], ft_solve_for(g_prove[i], solving));
		i++;
	}
}
