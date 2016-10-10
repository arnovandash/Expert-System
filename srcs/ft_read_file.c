/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 08:29:51 by rojones           #+#    #+#             */
/*   Updated: 2016/10/10 17:21:35 by arnovan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_system.h"

int		ft_isop(char c)
{
	if (c == '+' || c == '|')
		return (1);
	return (0);
}

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
			if (line[i] != '#' && line[i] != '=')
				if (line[i] != '?' && line[i] != '\n')
					re++;
		}
		free(line);
		line = NULL;
		fclose(fp);
	}
	return (re);
}

void		ft_read_info(char *file)
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
	//		int rules_idx = 0;
			int i = 0;
			if (isspace(line[i]))
				while(isspace(line[i]) && line[i] != '\n')
					i++;
			if (line[i] == '#')
				while (line[i] != '\n')
					i++;
			else if (line[0] == '=')	
			{
				while (isalpha(line[++i]))
					g_facts[(line[i] - 'A')] = 1;
			
				/*
				   printf("gfacts A %i\n", g_facts[0]);
				   printf("gfacts B %i\n", g_facts[1]);
				   printf("gfacts G %i\n", g_facts[6]);
				   printf("gfacts C %i\n", g_facts[2]);
				   */
			}
			else if (line[i] != '#' && line[i] != '=' && line[i] != '?' && line[i] != '\n')
			{
				while (line[i] != '#' && line[i] != '\t')
				{
						if (isspace(line[i]))
							i++;
					printf("sizeof line%lu", sizeof(line));
					printf("%c", line[i]);
					i++;
				}
				printf("\n");
				re++;
			}
			free(line);
			line = NULL;
		}
		fclose(fp);
	}
}

void	ft_read_file(char *file)
{
	puts ("read file called");
	int		num_rules;
	//	rules = NULL;

	num_rules = ft_getnum_rules(file);
	g_rules = (t_rule*)(malloc(num_rules * sizeof(t_rule)));
	printf("num rules %d\n",num_rules);
	ft_read_info(file);
}
