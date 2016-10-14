/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 08:29:51 by rojones           #+#    #+#             */
/*   Updated: 2016/10/14 18:14:06 by arnovan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_system.h"

void		get_con(char *line, int i, int rule_no)
{
	int k;
	int num;

	k = 0;
	while ((line[i] == '<' || line[i] == '=' || line[i] == '>' ||
				isspace(line[i])) && line[i] != '\0' && line[i] != '#')
		i++;
	g_rules[rule_no].conclusion = (char *)(malloc(ft_strlen_n(&line[i])));
	while (line[i] != '#' && line[i] != '\0')
	{
		if (line[i] == '!')
		{
			num = 0;
			while ((line[i] == '!' || isspace(line[i])) && line[i] != '\0')
				if (line[i++] == '!')
					num++;
			if (num % 2 == 1)
				g_rules[rule_no].conclusion[k++] = '!';
		}
		else 
			g_rules[rule_no].conclusion[k++] = line[i++];
	}
	g_rules[rule_no].conclusion[k] = '\0';
}

void 		get_rule(char *line, int i, int *rule_no)
{
	int k;
	int by;

	k = 0;
	by = 0;
	g_rules[*rule_no].condition = (char *)(malloc(ft_strlen_rule(&line[i])));
	while (line[i] != '=' && line[i] != '<' && line[i] != '\0')
	{
		if (isspace(line[i]))
			i++;
		else if (line[i] == '!')
		{
			int num = 0;
			while ((line[i] == '!' || isspace(line[i])) && line[i] != '\0')
				if (line[i++] == '!')
					num++;
			if (num % 2 == 1)
				g_rules[*rule_no].condition[k++] = '!';
		}
		else 
			g_rules[*rule_no].condition[k++] = line[i++];
	}
	by = (line[i] == '<') ? 1 : 0;
	g_rules[*rule_no].condition[k] = '\0';
	get_con(line, i, *rule_no);
	if(by == 1)
	{
		g_rules[*rule_no + 1].condition = g_rules[*rule_no].conclusion;
		g_rules[*rule_no + 1].conclusion = g_rules[*rule_no].condition;
		(*rule_no)++;
	}
}

int			ft_getnum_rules(char *file, t_file *f)
{
	int i;

	f->fp = fopen(file, "r");
	if (f->fp != NULL)
	{
		while (getline(&f->line, &f->n, f->fp) != -1)
		{
			i = 0;
			ft_drop_spaces(f->line);
			if (f->line[i] != '#' && f->line[i] != '=' &&
					f->line[i] != '?' && f->line[i] != '\0')
			{
				char *temp = strstr(f->line, "<=>");
				if (temp)
				{
					if (strchr(f->line, '#') == NULL)
						f->re++;
					else if ((long int)temp < (long int)(strchr(f->line, '#')))
						f->re++;
				}
				f->re++;
			}
			if (f->line[i] == '=' && f->line[i + 1] == '>')
				f->re++;
		}
		free(f->line);
		f->line = NULL;
		fclose(f->fp);
	}
	return (f->re);
}

void		ft_read_info(char *file, t_file *f)
{
	int		i;

	f->fp = fopen(file, "r");
	if (f->fp != NULL)
	{
		while (getline(&f->line, &f->n, f->fp) != -1)
		{
			i = 0;
			*(strrchr(f->line,'\n'))='\0';
			ft_drop_spaces(f->line);
			if (f->line[i] != '#' && f->line[i] != '\0')
			{
				if (f->line[i] == '=' && f->line[i + 1] != '>')
				{
					while (isupper(f->line[++i]))
						g_default[(f->line[i] - 'A')] = 1;
				}
				else if (f->line[i] == '?')
				{
					g_prove = (char*)(malloc(ft_strlen_n(&f->line[i++])));
					while(f->line[i] != '\0' && f->line[i] != '#')
					{
						if (isupper(f->line[i]))
							g_prove[f->s++]=f->line[i];
						i++;
					}
					g_prove[f->s]='\0';
				}
				else
				{
					get_rule(f->line, i, &g_rule_no);
					ft_validate_rule(g_rule_no, f->line_no);
					g_rule_no++;
				}
			}
			f->line_no++;
		}
		free(f->line);
		f->line = NULL;
	}
	fclose(f->fp);
}

void		ft_read_file(char *file)
{
	int		i;
	t_file	f;

	i = -1;
	puts ("Reading file...");
	init_file_struct(&f);
	g_num_rules = ft_getnum_rules(file, &f);
	g_rules = (t_rule*)(malloc(g_num_rules * sizeof(t_rule)));
	printf("Number of rules: %d\n\n",g_num_rules);
	init_file_struct(&f);
	ft_read_info(file, &f);

	puts("\nRule base:");
	while (++i < g_num_rules)
		printf("Rule[%02i]: %s => %s \n",
				i, g_rules[i].condition, g_rules[i].conclusion);
	puts("\nResults:");
}
