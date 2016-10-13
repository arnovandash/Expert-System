/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_system.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:55:21 by rojones           #+#    #+#             */
/*   Updated: 2016/10/13 13:26:47 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EX_SYSTEM_H
# define EX_SYSTEM_H

# include <libc.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>

typedef struct	s_rule
{
	char	*condition;
	char	*conclusion;
}				t_rule;

int		g_num_rules;
int		g_facts[26];
int		g_default[26];
int		g_short;
t_rule	*g_rules;
char	*g_prove;

int		ft_and(int t1, int t2);
int		ft_or(int t1, int t2);
int		ft_xor(int t1, int t2);
int		ft_negate(int t);
int		ft_eval_condition(char *condition, int *solving);
void	ft_read_file(char *file);
void	ft_read_info(char *file);
char	*ft_strnew(size_t size);
int		ft_solve_for(char fact, int *solving);
void	ft_validate_rule(int rulenum, int line_no);
#endif
