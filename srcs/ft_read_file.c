/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 08:29:51 by rojones           #+#    #+#             */
/*   Updated: 2016/09/27 15:41:59 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_system.h"
#include <string.h>

int		ft_getnum_rules(char *file)
{
	FILE 	*fp;
	int		re = 0;
	char	*line = NULL;
	size_t	n = 0;

	fp = fopen(file, "r");
	if (fp != NULL)
	{
		while (getline(&line, &n, fp) != -1)
		{
			int i = 0;
			while(isspace(line[i]) && line[i] != '\n')
				i++;
			if (line[i] != '#' && line[i] != '=' && line[i] != '?' && line[i] != '\n')
				re++;
			free(line);
			line = NULL;
		}
	}
	return (re);
}

void	ft_read_file(char *file, t_rule *rules)
{
	puts ("read file called");
	int		num_rules;
	rules = NULL;

	num_rules = ft_getnum_rules(file);
	printf("num rules %d\n",num_rules);
}
