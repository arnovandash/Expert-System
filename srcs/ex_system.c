/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_system.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:54:18 by rojones           #+#    #+#             */
/*   Updated: 2016/10/10 17:21:52 by arnovan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_system.h"

int main (int ac, char **av)
{
	if (ac != 2)
	{
		puts("Please specify one and only one input file!");
		return (0);
	}
	g_num_rules = 1;
	bzero(g_facts, 26);

	/*
	puts("facts defalted");
	//test!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	g_facts[0] = 1;
	g_facts[1] = 1;
	g_rules = (t_rule*)(malloc(2 * sizeof(t_rule)));
	g_rules[0].conclusion = "C";
	g_rules[0].condition = "A+B";
	puts ("assigned facts");
	printf("result %d\n", ft_eval_condition(strdup(av[1])));
	*/
	ft_read_file(av[1]);
}
