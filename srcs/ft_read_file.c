/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 08:29:51 by rojones           #+#    #+#             */
/*   Updated: 2016/10/13 12:09:58 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_system.h"

static int ft_strlen_n(char *st)
{
	int i = 0;
	int re = 0;

	while (st[i] != '\0' && st[i] != '#')
	{
		if (isspace(st[i]) == 0)
			re++;
		i++;
	}
	return (re);
}

static void ft_drop_spaces(char *line) 
{
	char *re;
	int i = 0;
	int j = 0;


	re = line;
	while(line[i] != '\0')
	{
		if (isspace(line[i]))
			i++;
		else
			re[j++] = line[i++];
	}
	re[j] = '\0';
}

static int ft_strlen_rule(char *st)
{
	int i = 0;
	int re = 0;	
	while (st[i] != '\0' && st[i] != '#')
	{
		if (isspace(st[i]) == 0)
			re++;
		i++;
	}
	return (re);
}

void 	get_con(char *line, int i, int rule_no)
{
	int k = 0;
	while ((line[i] == '<' || line[i] == '=' || line[i] == '>' ||
				isspace(line[i])) && line[i] != '\0' && line[i] != '#')
		i++;
	g_rules[rule_no].conclusion = (char *)(malloc(ft_strlen_n(&line[i])));
	while (line[i] != '#' && line[i] != '\0')
	{
		if (isspace(line[i]))
			i++;
		else if (line[i] == '!')
		{
			int num = 0;
			while ((line[i] == '!' || isspace(line[i])) && line[i] != '\0')
			{
				if (line[i] == '!')
					num++;
				i++;
			}
			if (num % 2 == 1)
				g_rules[rule_no].conclusion[k++] = '!';
		}
		else 
			g_rules[rule_no].conclusion[k++] = line[i++];
	}
	g_rules[rule_no].conclusion[k] = '\0';
}

void 	get_rule(char *line, int i, int *rule_no)
{
	int k = 0;
	int by = 0;

	g_rules[*rule_no].condition = (char *)(malloc(ft_strlen_rule(&line[i])));
	while (line[i] != '=' && line[i] != '<' && line[i] != '\0')
	{
		if (isspace(line[i]))
			i++;
		else if (line[i] == '!')
		{
			int num = 0;
			while ((line[i] == '!' || isspace(line[i])) && line[i] != '\0')
			{
				if (line[i] == '!')
					num++;
				i++;
			}
			if (num % 2 == 1)
				g_rules[*rule_no].condition[k++] = '!';
		}
		else 
			g_rules[*rule_no].condition[k++] = line[i++];
	}
	if (line[i] == '<')
		by = 1;
	g_rules[*rule_no].condition[k] = '\0';
	get_con(line, i, *rule_no);
	if(by == 1)
	{
		g_rules[*rule_no + 1].condition = g_rules[*rule_no].conclusion;
		g_rules[*rule_no + 1].conclusion = g_rules[*rule_no].condition;
		(*rule_no)++;
	}
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
			ft_drop_spaces(line);
			if (line[i] != '#' && line[i] != '=' && line[i] != '?' && line[i] != '\0')
			{
				char *temp = strstr(line, "<=>");
				if (temp)
				{
					puts("if and only if found");
					if (strchr(line, '#') == NULL)
						re++;
					else if ((long int)temp < (long int)(strchr(line, '#')))
						re++;
				}
				re++;
			}
			if (line[i] == '=' && line[i + 1] == '>')
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
	int		s = 0;
	int		line_no = 1;

	fp = fopen(file, "r");
	if (fp != NULL)
	{
		while (getline(&line, &n, fp) != -1)
		{
			int i = 0;
			*(strrchr(line,'\n'))='\0';
			ft_drop_spaces(line);
			if (line[i] != '#' && line[i] != '\0')
			{
				if (line[i] == '=' && line[i + 1] != '>')
				{
					while (isupper(line[++i]))
						g_default[(line[i] - 'A')] = 1;
				}
				else if (line[i] == '?')
				{
					g_prove = (char*)(malloc(ft_strlen_n(&line[i])));
					i++;
					while(line[i] != '\0' && line[i] != '#')
					{
						if (isupper(line[i]))
							g_prove[s++]=line[i];
						i++;
					}
					g_prove[s]='\0';
				}
				else
				{
					get_rule(line, i, &rule_no);
					ft_validate_rule(rule_no, line_no);
					rule_no++;
				}
			}
			line_no++;
		}
		free(line);
		line = NULL;
	}
	fclose(fp);
}

void	ft_read_file(char *file)
{
	puts ("read file called");
	g_num_rules = ft_getnum_rules(file);
	g_rules = (t_rule*)(malloc(g_num_rules * sizeof(t_rule)));
	printf("num rules %d\n",g_num_rules);
	ft_read_info(file);

	puts("\nrule base");
	for (int f = 0; f < g_num_rules; f++)
	{
		printf("rules[%i]: %s => %s \n", f, g_rules[f].condition, g_rules[f].conclusion);
	}
	puts("\nresults");
}
