/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_system.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:54:18 by rojones           #+#    #+#             */
/*   Updated: 2016/10/12 17:33:40 by rojones          ###   ########.fr       */
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

int	i = 0;
while (g_prove[i] != '\0')
{
	printf("Array g_prove contains %c at [%d]\n",g_prove[i], i);
	i++;
}

i = 0;
while (g_prove[i] != '\0')
{
	int rules_used[g_num_rules];

	bzero(rules_used, g_num_rules);
	printf("result of %c is %d\n",g_prove[i], ft_solve_for(g_prove[i], rules_used, 0));
	i++;
}
/*	printf("result G %d\n", ft_solve_for('G'));
	printf("result V %d\n", ft_solve_for('V'));
	printf("result X %d\n", ft_solve_for('X'));*/
}
