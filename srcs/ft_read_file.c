/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 08:29:51 by rojones           #+#    #+#             */
/*   Updated: 2016/10/11 15:04:23 by arnovan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_system.h"

void 	get_con(char *line, int i, int rule_no)
{
	int k = 0;
	g_rules[rule_no].conclusion = (char *)(malloc(sizeof(line)));
	while (line[i] != '#' && line[i] != '\t')
	{
		if (isspace(line[i]))
			i++;
		if (line[i] == '=' || line[i] == '<' || line[i] == '>')
			i++;
		else
			g_rules[rule_no].conclusion[k++] = line[i++];
	}
	g_rules[rule_no].conclusion[k] = '\0';
}

void 	get_rule(char *line, int i, int rule_no)
{
	int k = 0;
	g_rules[rule_no].condition = (char *)(malloc(sizeof(line)));
	while (line[i] != '=' && line[i] != '<')
	{
		if (isspace(line[i]))
			i++;
		else if (line[i] == '!' && line[i + 1] == '!')
			i+= 2;
		else
			g_rules[rule_no].condition[k++] = line[i++];
	}
	g_rules[rule_no].condition[k] = '\0';
	get_con(line, i, rule_no);
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

void	ft_read_info(char *file)
{
	FILE 	*fp;
	char	*line = NULL;
	size_t	n = 0;
	int		rule_no = 0;

	fp = fopen(file, "r");
	if (fp != NULL)
	{
		while (getline(&line, &n, fp) != -1)
		{
			int i = 0;
			if (isspace(line[i]) || line[i] == '#' || line[i] == '\n')
				i++;
			else if (line[0] == '=')
				while (isalpha(line[++i]))
					g_facts[(line[i] - 'A')] = 1;
			else if (line[i] != '#' && line[i] != '=')
				if (line[i] != '?' && line[i] != '\n')
					get_rule(line, i, rule_no++);
			free(line);
			line = NULL;
		}
		fclose(fp);
	}
}

void	ft_read_file(char *file)
{
	puts ("read file called");
	g_num_rules = ft_getnum_rules(file);
	g_rules = (t_rule*)(malloc(g_num_rules * sizeof(t_rule)));
	printf("num rules %d\n",g_num_rules);
	ft_read_info(file);

	for (int f = 0; f < 9; f++)
	{
		printf("g_rules[%i]: ", f);
		printf("%s\n", g_rules[f].condition);
	}
	for (int f = 0; f < 9; f++)
	{
		printf("g_conclusion[%i]: ", f);
		printf("%s\n", g_rules[f].conclusion);
	}
}
