/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file_extras.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnovan- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 16:33:06 by arnovan-          #+#    #+#             */
/*   Updated: 2016/10/14 17:29:57 by arnovan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_system.h"

void		init_file_struct(t_file *f)
{
	f->re = 0;
	f->line = NULL;
	f->line_no = 1;
	f->n = 0;
	f->s = 0;
}

int			ft_strlen_n(char *st)
{
	int	i;
	int	re;

	i = 0;
	re = 0;
	while (st[i] != '\0' && st[i] != '#')
	{
		if (isspace(st[i]) == 0)
			re++;
		i++;
	}
	return (re);
}

void		ft_drop_spaces(char *line) 
{
	char	*re;
	int		i;
	int		j;

	i = 0;
	j = 0;
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

int			ft_strlen_rule(char *st)
{
	int	i;
	int	re;

	i = 0;
	re = 0;
	while (st[i] != '\0' && st[i] != '#')
	{
		if (isspace(st[i]) == 0)
			re++;
		i++;
	}
	return (re);
}


