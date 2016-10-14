/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_system.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:55:21 by rojones           #+#    #+#             */
/*   Updated: 2016/10/14 18:14:08 by arnovan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EX_SYSTEM_H
# define EX_SYSTEM_H

# include <libc.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>


# define M_FACT1 "\x1B[31mERROR: Multiple facts not seperated by an "
# define M_FACT2 "operator %s at index %d\n\x1B[0m"
# define M_OPS1 "\x1B[31mERROR: Multiple operators not seperated "
# define M_OPS2 "by a fact\x1B[0m"
# define T_OPEN1 "\x1B[31mERROR: Condition ends with an open term. Add fact "
# define T_OPEN2 "after the last operator\x1B[0m"
# define S_UNKNWN "\x1B[31mERROR: Symbol[ \'%c\' ] not recognised\n\x1B[0m"

typedef struct	s_val
{
	int		i;
	int		f;
	int		op;
	int		brace;
}				t_val;

typedef struct	s_file
{
	FILE	*fp;
	int		re;
	char	*line;
	int		line_no;
	size_t	n;
	int		s;
}				t_file;

typedef struct	s_rule
{
	char	*condition;
	char	*conclusion;
}				t_rule;

int		g_num_rules;
int		g_rule_no;
int		g_facts[26];
int		g_default[26];
int		g_short;
t_rule	*g_rules;
char	*g_prove;


void	init_file_struct(t_file *f);
int		ft_and(int t1, int t2);
int		ft_or(int t1, int t2);
int		ft_xor(int t1, int t2);
int		ft_negate(int t);
void	get_con(char *line, int i, int rule_no);
void	get_rule(char *line, int i, int *rule_no);
int		ft_getnum_rules(char *file, t_file *f);
int		ft_eval_cond(char *condition, int *solving);
void	ft_read_file(char *file);
void	ft_read_info(char *file, t_file *f);
char	*ft_strnew(size_t size);
int		ft_solve_for(char fact, int *solving);
void	ft_validate_rule(int rulenum, int line_no);
int		ft_strlen_n(char *st);
void	ft_drop_spaces(char *line);
int		ft_strlen_rule(char *st);
#endif
