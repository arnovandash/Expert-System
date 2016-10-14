/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_system.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:55:21 by rojones           #+#    #+#             */
/*   Updated: 2016/10/14 14:43:21 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EX_SYSTEM_H
# define EX_SYSTEM_H

# include <libc.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>

# define C_RED \e[3m
# define OR_WARNING "\x1B[31mWarning OR type operand in conclusion, result is \
undefined\x1B[0m\n"
# define RULE_USED "Used rule [ \"%s => %s\" ] to solve %c - Result: %d\n"\
, g_rules[sv->i].condition, g_rules[sv->i].conclusion, fact, re
# define CONTRADIC_WARNING "\x1B[31mWarning contradicting results for %c - \
Previous Result: %d, Current Result: %d\x1B[0m\n", fact, sv->final, re
# define CONDITION_NOT_MET "\x1B[33mcondition [%s] %d not met fact[%c] not \
changed\n\x1B[0m", g_rules[sv->i].condition, re, fact

typedef struct	s_rule
{
	char	*condition;
	char	*conclusion;
}				t_rule;

typedef struct	s_solve
{
	int		i;
	int		pos;
	int		final;
}				t_solve;

typedef struct	s_eval
{
	int     neg1;
	int     neg2;
	int     t1;
	int     t2;
	int     op;
	char    *ncon;
}				t_eval;

typedef struct	s_eval_brack
{
	int		st;
	int		end;
	int		brace;
	char	*left;
	char	*right;
	char	*temp;
}				t_eval_brack;

int				g_num_rules;
int				g_facts[26];
int				g_default[26];
int				g_short;
t_rule			*g_rules;
char			*g_prove;

int				ft_eval_brackets(char *condition, int *solving);
int				ft_and(int t1, int t2);
int				ft_or(int t1, int t2);
int				ft_xor(int t1, int t2);
int				ft_negate(int t);
int				ft_eval_cond(char *condition, int *solving);
void			ft_read_file(char *file);
void			ft_read_info(char *file);
char			*ft_strnew(size_t size);
int				ft_solve_for(char fact, int *solving);
void			ft_validate_rule(int rulenum, int line_no);
#endif
